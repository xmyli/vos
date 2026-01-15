#ifndef SLEEP_LOCK_HPP
#define SLEEP_LOCK_HPP

#include "spin_lock.hpp"

namespace synchronization {

class sleep_lock {
public:
    void acquire();
    void release();

private:
    bool locked = false;
    spin_lock lock;
};

} // namespace synchronization

#endif
