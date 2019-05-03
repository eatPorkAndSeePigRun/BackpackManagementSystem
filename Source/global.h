//
// Created by seepigrun on 19-5-3.
//

#ifndef BAG_GLOBAL_H
#define BAG_GLOBAL_H

#include <unordered_map>
#include <string>
#include <tuple>
#include <vector>

using namespace std;


namespace gb {

    // 整个时空内全局唯一的id
    int uuid = 0;

    unordered_map<string, tuple<string, bool> > item_data = {
            // 标识， 名字， 是否可以叠加
            {"1", {"小李飞刀", false}},
            {"2", {"关刀",   false}},
            {"3", {"金币",   true}},
            {"A", {"A",    false}},
            {"B", {"B",    false}},
            {"C", {"C",    false}},
            {"D", {"D",    false}},
    };

    unordered_map<string, vector<string> > item_combine = {
            // 第一个是合成的目标物品、后面依次是合成的材料
            {"A", {"D", "B", "C"}},
            {"B", {"D", "A", "C"}},
            {"C", {"D", "A", "B"}}
    };
}


#endif //BAG_GLOBAL_H
