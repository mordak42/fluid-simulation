
#ifndef __SEMAPHORE_HPP__
# define __SEMAPHORE_HPP__

#include <iostream>
#include <mutex>
#include <condition_variable>

namespace lib
{
class Semaphore
{
public:
    Semaphore(int32_t initialCount);
    ~Semaphore();

    void notify();
    void wait();
    bool try_wait();

private:
    std::mutex m_mutex;
    std::condition_variable m_condition;
    int32_t m_count;
};
}

#endif
