#include <iostream>
#include <mutex>
#include <condition_variable>

namespace std
{
class semaphore
{
public:
    semaphore(unsigned long initialCount);
    ~semaphore();

    void notify();
    void wait();
    bool try_wait();

private:
    std::mutex m_mutex;
    std::condition_variable m_condition;
    unsigned long m_count = 0;                                                  // Default Initialized as locked.
};
}
