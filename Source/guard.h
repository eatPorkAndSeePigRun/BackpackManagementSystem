//
// Created by seepigrun on 19-5-3.
//

#ifndef BAG_GUARD_H
#define BAG_GUARD_H

#include <mutex>

using namespace std;


class Guard {
public:
    explicit Guard(recursive_mutex &m) : m_(m) {
        m_.lock();
    }

    ~Guard() {
        m_.unlock();
    }

    Guard(const Guard &) = delete;

    void operator=(const Guard &) = delete;

private:
    recursive_mutex &m_;
};

#endif //BAG_GUARD_H
