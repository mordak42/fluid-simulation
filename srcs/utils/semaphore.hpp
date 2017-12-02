
#ifndef __SEMAPHORE_HPP__
# define __SEMAPHORE_HPP__

#include <iostream>
#include <mutex>
#include <condition_variable>

namespace std
{
class semaphore
{
public:
    semaphore(uint32_t initialCount);
    ~semaphore();

    void notify();
    void wait();
    bool try_wait();

private:
    std::mutex m_mutex;
    std::condition_variable m_condition;
    uint32_t m_count;
};
}

#endif
