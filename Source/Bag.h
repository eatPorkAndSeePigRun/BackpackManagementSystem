//
// Created by seepigrun on 19-5-1.
//

#ifndef BAG_BAG_H
#define BAG_BAG_H

#include <list>
#include <string>
#include <algorithm>
#include <bits/unique_ptr.h>
#include "Item.h"

using namespace std;


class Bag {
public:
    Bag() = default;

    bool AddItem(const Item &item) {
        items_.push_back(item);
        return true;
    }

    bool DelItem(int item_uuid, Item &ans) {
        auto it = find_if(items_.begin(), items_.end(),
                          [item_uuid](const Item &item) {
                              return item.uuid_ == item_uuid;
                          });
        if (it == items_.end()) {
            return false;
        } else {
            ans = *it;
            items_.erase(it);
            return true;
        }
    }

public:
    list<Item> items_;
};

#endif //BAG_BAG_H
