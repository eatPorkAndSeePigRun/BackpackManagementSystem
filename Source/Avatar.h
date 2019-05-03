//
// Created by seepigrun on 19-5-1.
//

#ifndef BAG_AVATAR_H
#define BAG_AVATAR_H

#include <string>
#include <mutex>
#include "Bag.h"
#include "BagCurrent.h"

using namespace std;


static recursive_mutex m;

class Avatar {
public:
    explicit Avatar(int uuid) : uuid_(uuid), next_item_uuid_(1) {
        bag_ = Bag();
        bag_current_ = BagCurrent();
    }

    bool AddItem(const string &item_id, int amount);

    bool DeleteItem(int item_uuid);

    bool UseItem(int item_uuid);

    bool MoveItemCurrent(int item_uuid, Item &item);

private:
    int NextItemUuid() {
        ++next_item_uuid_;
        return next_item_uuid_;
    }

    int uuid_;
    Bag bag_;                   // 背包
    BagCurrent bag_current_;    // 身上
    int next_item_uuid_;
};

#endif //BAG_AVATAR_H
