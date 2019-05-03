//
// Created by seepigrun on 19-5-3.
//
#include <string>
#include <mutex>
#include "Bag.h"
#include "BagCurrent.h"
#include "global.h"
#include "Item.h"
#include "guard.h"
#include "Avatar.h"

using namespace std;


bool Avatar::AddItem(const string &item_id, int amount) {
    Guard lock(m);
    // 判断item_id是否有效，是否在item_data里
    if (gb::item_data.find(item_id) == gb::item_data.end())
        return false;

    // 生成物品
    gb::uuid = NextItemUuid();
    auto item = Item(item_id);

    // 拾取物品
    if (bag_current_.AddItem(item))
        return true;
    else
        return bag_.AddItem(item);
}

bool Avatar::DeleteItem(int item_uuid) {
    Guard lock(m);
    auto ans = false;

    // 先删除身上的
    auto it = find_if(bag_current_.items_.begin(), bag_current_.items_.end(),
                      [item_uuid](const Item &item) {
                          return item.uuid_ == item_uuid;
                      });
    if (it != bag_current_.items_.end()) {
        bag_current_.items_.erase(it);
        ans = true;
    }

    // 再删除背包的
    Item temp = Item("");
    if (bag_.DelItem(item_uuid, temp))
        ans = true;

    return ans;
}

bool Avatar::UseItem(int item_uuid) {
    Guard lock(m);
    // 先查看身上是否有物品，有使用返回
    auto it = find_if(bag_current_.items_.begin(), bag_current_.items_.end(),
                      [item_uuid](const Item &item) {
                          return item.uuid_ == item_uuid;
                      });
    if (it != bag_current_.items_.end()) {
        if (it->Use())
            return true;
        bag_current_.items_.erase(it);
    }
    // 若身上没有则继续看背包是否有，有使用返回
    Item item = Item("");
    if (MoveItemCurrent(item_uuid, item)) {
        if (item.Use())
            return true;
        bag_.DelItem(item_uuid, item);
    }
    // 身上，背包都没有
    return false;
}

bool Avatar::MoveItemCurrent(int item_uuid, Item &item) {
    Guard lock(m);
    // 先从背包内拿出该物品，没有则返回
    if (!bag_.DelItem(item_uuid, item))
        return false;
    // 添加到身上，若身上满了，则删除最久未使用再添加
    if (!bag_current_.AddItem(item)) {
        bag_current_.DelItem(); // 删除最久未使用
        if (!bag_current_.AddItem(item))
            return false;
    }
    return true;
}
