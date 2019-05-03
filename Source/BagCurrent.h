//
// Created by seepigrun on 19-5-1.
//

#ifndef BAG_BAGCURRENT_H
#define BAG_BAGCURRENT_H

#include <list>
#include <string>
#include <algorithm>
#include "Item.h"

using namespace std;


static const int bag_current_size = 8;

class BagCurrent {
public:
    BagCurrent() = default;

    bool AddItem(const Item &item) {
        if (items_.size() < bag_current_size) {
            items_.push_back(item);

            // 题目五,判断是否可以合成
            if (gb::item_combine.find(item.item_id_) == gb::item_combine.end())
                return true;

            // 判断是否有合成的材料
            auto combine = gb::item_combine[item.item_id_];
            unordered_map<string, Item> m;
            for (const auto &i : items_)
                m[i.item_id_] = i;
            auto has_material = true;
            for (auto i = 1; i < combine.size(); ++i) {
                if (m.find(combine[i]) == m.end()) {
                    has_material = false;
                    break;
                }
            }

            // 没有合成的材料，直接返回
            if (!has_material)
                return true;

            // 合成的过程
            items_.pop_back();
            for (auto it = items_.begin(); it != items_.end();) {
                if (find_if(combine.begin() + 1, combine.end(), it->item_id_) != combine.end()) {
                    it = items_.erase(it);
                } else {
                    ++it;
                }
            }
            items_.emplace_back(combine[0]);
            return true;
        }
        return false;
    }

    bool DelItem() {
        // 题目一，淘汰最久未使用的道具
        if (!items_.empty()) {
            items_.sort([](const Item &i1, const Item &i2) {
                return i1.access_time_ < i2.access_time_;
            });
            items_.pop_back();
            return true;
        }
        return false;
    }

public:
    list<Item> items_;
};

#endif //BAG_BAGCURRENT_H
