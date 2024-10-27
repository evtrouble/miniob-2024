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

#include "storage/index/ivfflat_index.h"

RC IvfflatIndex::create(Table *table, VectorIndexNode &vector_index, const FieldMeta *field_meta)
{
    table_ = table;
    attr_offset_ = field_meta->offset();
    attr_length_ = field_meta->len();

    calculator_.init((VectorOperationExpr::Type)vector_index.distance, attr_length_);
    inited_ = true;
    lists_  = vector_index.lists;
    probes_ = vector_index.probes;
    centers_.resize(lists_);
    clusters_.resize(lists_);
    before_centers.resize(lists_);
    return RC::SUCCESS;
}

RC IvfflatIndex::insert_entry(const char *record, const RID *rid) 
{ 
    if(records_.count(*rid) != 0)return RC::INVALID_ARGUMENT;

    Value tmp;
    tmp.set_vector(record + attr_offset_, attr_length_);
    records_[*rid] = tmp;

    if(num < lists_){
        centers_[num] = std::move(tmp);
        clusters_[num].emplace_back(*rid);
        num++;
    } else {
        num++;
        k_means();
    }
    // for(auto& center : centers_){
    //     cout<<center.to_string()<<endl;
    // }
    return RC::SUCCESS; 
}

RC IvfflatIndex::delete_entry(const char *record, const RID *rid) 
{ 
    if(records_.count(*rid) == 0)return RC::SUCCESS;

    if(num == lists_){
        size_t id = 0;
        num--;
        records_.erase(*rid);
        for(auto& [rid, value] : records_){
            centers_[id] = value;
            clusters_[id].clear();
            clusters_[id].emplace_back(rid);
            id++;
        }
    } else if(num < lists_) {
        size_t id = get_id(records_[*rid]);
        records_.erase(*rid);
        num--;
        std::swap(clusters_[id], clusters_[num]);
        std::swap(centers_[id], centers_[num]);
    } else {
        num--;
        records_.erase(*rid);
        k_means();
    }
    // for(auto& center : centers_){
    //     cout<<center.to_string()<<endl;
    // }
    return RC::SUCCESS; 
}

RC IvfflatIndex::update_entry(const char *record, const RID *rid) 
{ 
    if(records_.count(*rid) == 0)return RC::SUCCESS;

    Value tmp;
    tmp.set_vector(record + attr_offset_, attr_length_);

    if(num <= lists_){
        size_t id = get_id(records_[*rid]);
        
        centers_[id] = tmp;
        clusters_[id][0] = *rid;
        records_[*rid] = std::move(tmp);
    } else {
        records_[*rid] = std::move(tmp);
        k_means();
    }
    // for(auto& center : centers_){
    //     cout<<center.to_string()<<endl;
    // }
    return RC::SUCCESS; 
}

void IvfflatIndex::k_means()
{
    while(true){
        before_centers = centers_;

        for(int i = 0; i < lists_; i++)clusters_[i].clear();

        for(auto& [rid, value] : records_){
            size_t id = get_id(value);
            clusters_[id].emplace_back(rid);
        }
        for(int i = 0; i < lists_; i++)
        {
            auto& cluster = clusters_[i];
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