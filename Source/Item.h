
//
// Created by seepigrun on 19-5-1.
//

#ifndef BAG_ITEM_H
#define BAG_ITEM_H

#include <utility>
#include <ctime>
#include <string>
#include <iostream>
#include "global.h"

using namespace std;


class Item {
public:
    explicit Item(string item_id) :
            uuid_(gb::uuid), item_id_(std::move(item_id)), amount_(1),
            use_times_(0), access_time_(time(nullptr)) {
    }

    bool Use() {
        access_time_ = time(nullptr);
        ++use_times_;

        auto item = gb::item_data[item_id_];
        if (get<1>(item)) {                 // 是否为消费类道具
            if (amount_ == 0) {
                return false;
            }
            --amount_;
        }
        cout << "使用" << get<0>(item) << endl;
        return true;
    }

public:
    int uuid_;
    string item_id_;
    int use_times_;
    int access_time_;   // 使用时间
    int amount_;
};

#endif //BAG_ITEM_H
