#include "semaphore.hpp"

using namespace std;

semaphore::semaphore(unsigned long initialCount) : m_count(initialCount) {}

semaphore::~semaphore() {};

void semaphore::notify() {
    std::unique_lock<decltype(m_mutex)> lock(m_mutex);
    ++m_count;
    m_condition.notify_one();
}

void semaphore::wait() {
    std::unique_lock<decltype(m_mutex)> lock(m_mutex);
    while (!m_count)                                                            // Handle spurious wake-ups.
        m_condition.wait(lock);
    --m_count;
}

bool semaphore::try_wait() {
    std::unique_lock<decltype(m_mutex)> lock(m_mutex);
    if (m_count) {
        --m_count;
        return true;
    }
    return false;
}
