#ifndef SPIN_LOCK_HPP
#define SPIN_LOCK_HPP

namespace synchronization {

class spin_lock {
public:
    void acquire();
    void release();

private:
    volatile bool locked = false;
    int cpu_id = -1;
};

} // namespace synchronization

#endif
