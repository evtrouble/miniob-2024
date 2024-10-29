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

    clusters_.resize(lists_);
    before_centers.resize(lists_);

    index_meta_ = index_meta;
    field_metas_.emplace_back(*field_meta);
    return RC::SUCCESS;
}

RC IvfflatIndex::insert_entry(const char *record, const RID *rid) 
{ 
    Value tmp;
    tmp.set_vector(record + attr_offset_, calculator_.attr_length_);
    records_.emplace_back(*rid, move(tmp));

    changed = true;

    return RC::SUCCESS; 
}

RC IvfflatIndex::delete_entry(const char *record, const RID *rid) 
{ 
    auto iter = find_if(records_.begin(), records_.end(), [&](const auto& a){
        return a.first == *(rid);
    });
    records_.erase(iter);
    
    changed = true;
    return RC::SUCCESS; 
}

RC IvfflatIndex::update_entry(const char *record, const RID *rid) 
{ 
    Value tmp;
    tmp.set_vector(record + attr_offset_, calculator_.attr_length_);
    
    auto iter = find_if(records_.begin(), records_.end(), [&](const auto& a){
        return a.first == *(rid);
    });
    (*iter).second = move(tmp);
    changed = true;
    
    return RC::SUCCESS; 
}

void IvfflatIndex::k_means()
{
    if(records_.size() <= (size_t)lists_)return;
    k_meansplus();
    
    int loops = upper_limit;
    while(loops--){
        swap(before_centers, centers_);

        for(int i = 0; i < lists_; i++)clusters_[i].clear();

        for(size_t id = 0; id < records_.size(); id++){
            size_t temp = get_id(records_[id].second);
            clusters_[temp].emplace_back(id);
        }
        for(int i = 0; i < lists_; i++)
        {
            auto& cluster = clusters_[i];

            if(cluster.size() == 0)
            {
                centers_[i] = before_centers[i];
                continue;
            }
            
            Value sum = records_[cluster[0]].second;
            for(size_t j = 1; j < cluster.size(); j++)
            {
                Value::add(sum, records_[cluster[j]].second, sum);
            }
            vector<float>* temp = sum.get_vector();
            for(auto& val : *temp)val /= cluster.size();
            centers_[i] = std::move(sum);
        }

        bool ctl = true;
        for(int id = 0; id < lists_; id++)
        {
            if(abs(calculator_(before_centers[id], centers_[id])) > VECTOR_EPSILON)
            {
                ctl = false;
                break;
            }
        }
        if(ctl)break;   
    }
    changed = false;
}

vector<RID> IvfflatIndex::ann_search(const vector<float> &base_vector, size_t limit)
{
    if(records_.size() <= (size_t)lists_){
        std::priority_queue<pair<float, RID>> pq;
        Value base_value;
        base_value.set_vector(&base_vector);

        for(auto& [rid, value] : records_){
            float temp = calculator_(value, base_value); 
            if(pq.size() < (size_t)limit)pq.emplace(temp, rid);
            else if(pq.top().first > temp){
                pq.pop();
                pq.emplace(temp, rid);
            }
        }

        vector<RID> ret;
        ret.reserve(limit);
        while(!pq.empty()){
            ret.emplace_back(std::move(pq.top().second));
            pq.pop();
        }
        reverse(ret.begin(), ret.end());
        return ret;
    }
    if(changed)k_means();
    
    std::priority_queue<pair<float, int>> pq;
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
            float temp = calculator_(records_[cluster].second, value); 
            if(rid_pq.size() < (size_t)limit)rid_pq.emplace(temp, records_[cluster].first);
            else if(rid_pq.top().first > temp){
                rid_pq.pop();
                rid_pq.emplace(temp, records_[cluster].first);
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

void IvfflatIndex::k_meansplus()
{   
    vector<float> min_distance(records_.size(), INF);
    vector<bool> vis(records_.size());

    uniform_int_distribution<int> random_(0, records_.size() - 1);
    default_random_engine e_;
    int start = random_(e_);

    vis[start] = true;
    centers_[0] = records_[start].second;
    for(int i = 1; i < lists_; i++){
        float mmax = -INF;
        int next = 0;
        for(size_t id = 0; id < records_.size(); id++){
            if(vis[i])continue;
            auto &distance = min_distance[id];
            distance = std::min(distance, calculator_(centers_[i - 1], records_[id].second));
            if(distance > mmax){
                mmax = distance;
                next = id;
            }
        }
        centers_[i] = records_[next].second;
        vis[next] = true;
    }
}