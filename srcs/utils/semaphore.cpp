
#include "semaphore.hpp"

using namespace lib;

Semaphore::Semaphore(uint32_t initialCount) : m_count(initialCount) {}

Semaphore::~Semaphore() {};

void Semaphore::notify() {
    std::unique_lock<decltype(m_mutex)> lock(m_mutex);
    ++m_count;
    m_condition.notify_one();
}

void Semaphore::wait() {
    std::unique_lock<decltype(m_mutex)> lock(m_mutex);
    if (!m_count)
        m_condition.wait(lock);
    --m_count;
}

bool Semaphore::try_wait() {
    std::unique_lock<decltype(m_mutex)> lock(m_mutex);
    if (m_count) {
        --m_count;
        return true;
    }
    return false;
}
