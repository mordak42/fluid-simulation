
#include "pool.hpp"

using namespace mod1;

Pool::Pool(unsigned long nbFrames) :
        m_availabilitySem(nbFrames),
        m_nbFrames(nbFrames) {
    std::cout << "Pool initialisation" << std::endl;
}

Pool::~Pool() {
    m_ready = false;

    size_t tmp;

    tmp = m_actives.size();
    for (size_t i = 0; i < tmp; i++)
        m_actives.pop();

    tmp = m_inactives.size();
    for (size_t i = 0; i < tmp; i++)
        m_inactives.pop();

    std::cout << "Pool terminated" << std::endl;
}

/* TODO Out of memory case:
* It's difficult to reproduce in OSX, but we have to manage this exeption
* imperatively */

bool Pool::init() {
    if (m_ready == true) {
        std::cerr << __func__ << " : Pool already initialized" << std::endl;
        return false;
    }
    try {
        for (unsigned long i = 0; i < m_nbFrames; i++) {
            std::cout << "loop" << std::endl;
            m_inactives.emplace();
        }
        m_ready = true;
        std::cout << "Pool is ready" << std::endl;
        return true;
    }
    catch (const std::bad_alloc &) {
        std::cerr << __func__ << " : Out of memory" << std::endl;
        return false;
    }
}

/* Productor side */
ImgData *Pool::popOutdatedFrame(void) {
    if (m_ready == false) {
        std::cerr << __func__ << " : Pool not initialized" << std::endl;
        return nullptr;
    }
    m_availabilitySem.wait();
    std::lock_guard<std::mutex>lock(m_mutex);
    ImgData *output = &m_inactives.front();
    m_inactives.pop();
    return output;
}

void Pool::pushRenderedFrame(ImgData *frame) {
    if (m_ready == false) {
        std::cerr << __func__ << " : Pool not initialized" << std::endl;
        return;
    }
    std::lock_guard<std::mutex>lock(m_mutex);
    m_actives.push(*frame);
    (void)frame;
}

/* Consumer side */
ImgData *Pool::popRenderedFrame(void) {
    if (m_ready == false) {
        std::cerr << __func__ << " : Pool not initialized" << std::endl;
        return nullptr;
    }
    std::lock_guard<std::mutex>lock(m_mutex);
    if (m_actives.size() == 0)
        return nullptr;
    ImgData *output = &m_actives.front();
    m_actives.pop();
    return output;
}

void Pool::pushOutdatedFrame(ImgData *frame) {
    if (m_ready == false) {
        std::cerr << __func__ << " : Pool not initialized" << std::endl;
        return;
    }
    std::lock_guard<std::mutex>lock(m_mutex);
    m_inactives.push(*frame);
    m_availabilitySem.notify();
}
