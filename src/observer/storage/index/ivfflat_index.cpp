/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created on 2024/10/27.
//

#include <queue>
#include <random>

#include "storage/index/ivfflat_index.h"

using namespace std;

RC IvfflatIndex::create(Table *table, VectorIndexNode &vector_index, const FieldMeta *field_meta, const IndexMeta &index_meta)
{
    table_ = table;
    attr_offset_ = field_meta->offset();

    calculator_.init((VectorOperationExpr::Type)vector_index.distance, field_meta->len());
    inited_ = true;
    lists_  = vector_index.lists;
    probes_ = vector_index.probes;
    centers_.resize(lists_);

    vector<float> temp(field_meta->len() / sizeof(float));
    Value val;
    uniform_real_distribution<float> random_(-1e6, 1e6);
    default_random_engine e_;

    for(auto &center : centers_){
        for(auto &num : temp)num = random_(e_);
        val.set_vector(&temp);
        center = move(val);
    }
    clusters_.resize(lists_);
    before_centers.resize(lists_);

    index_meta_ = index_meta;
    field_metas_.emplace_back(*field_meta);
    return RC::SUCCESS;
}

RC IvfflatIndex::insert_entry(const char *record, const RID *rid) 
{ 
    if(records_.count(*rid) != 0)return RC::INVALID_ARGUMENT;

    changed = true;
    Value tmp;
    tmp.set_vector(record + attr_offset_, calculator_.attr_length_);
    records_[*rid] = move(tmp);

    return RC::SUCCESS; 
}

RC IvfflatIndex::delete_entry(const char *record, const RID *rid) 
{ 
    if(records_.count(*rid) == 0)return RC::SUCCESS;
    changed = true;
    records_.erase(*rid);
    return RC::SUCCESS; 
}

RC IvfflatIndex::update_entry(const char *record, const RID *rid) 
{ 
    if(records_.count(*rid) == 0)return RC::SUCCESS;
    changed = true;
    Value tmp;
    tmp.set_vector(record + attr_offset_, calculator_.attr_length_);
    records_[*rid] = move(tmp);
    return RC::SUCCESS; 
}

void IvfflatIndex::k_means()
{
    int loops = upper_limit;
    while(loops--){
        swap(before_centers, centers_);

        for(int i = 0; i < lists_; i++)clusters_[i].clear();

        for(auto& [rid, value] : records_){
            size_t id = get_id(value);
            clusters_[id].emplace_back(rid);
        }
        for(int i = 0; i < lists_; i++)
        {
            auto& cluster = clusters_[i];

            if(cluster.size() == 0)
            {
                centers_[i] = before_centers[i];
                continue;
            }
            
            Value sum = records_[cluster[0]];
            for(size_t j = 1; j < cluster.size(); j++)
            {
                Value::add(sum, records_[cluster[j]], sum);
            }
            vector<float>* temp = sum.get_vector();
            for(auto& val : *temp)val /= cluster.size();
            centers_[i] = std::move(sum);
        }

        bool ctl = false;
        for(int id = 0; id < lists_; id++)
        {
            ctl = ctl || (before_centers[id].compare(centers_[id]) != 0);
        }
        if(ctl)break;   
    }
}

vector<RID> IvfflatIndex::ann_search(const vector<float> &base_vector, size_t limit)
{
    if(changed)
        k_means();
    changed = false;
    std::priority_queue<pair<float,int>> pq;
    Value value;
    value.set_vector(&base_vector);

    for(int i = 0; i < lists_; i++){
        float temp = calculator_(centers_[i], value); 
        if(pq.size() < (size_t)probes_)pq.emplace(temp, i);
        else if(pq.top().first > temp){
            pq.pop();
            pq.emplace(temp, i);
        }
    }
    
    std::priority_queue<pair<float, RID>> rid_pq;
    while(!pq.empty()){
        int id = pq.top().second;
        pq.pop();
        for(auto& cluster : clusters_[id]){
            float temp = calculator_(records_[cluster], value); 
            if(rid_pq.size() < (size_t)limit)rid_pq.emplace(temp, cluster);
            else if(rid_pq.top().first > temp){
                rid_pq.pop();
                rid_pq.emplace(temp, cluster);
            }
        }
    }
    vector<RID> ret;
    ret.reserve(limit);
    while(!rid_pq.empty()){
        ret.emplace_back(std::move(rid_pq.top().second));
        rid_pq.pop();
    }
    reverse(ret.begin(), ret.end());
    return ret;
}