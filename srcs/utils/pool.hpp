
#ifndef __POOL_HPP__
# define __POOL_HPP__

#include <iostream>
#include <queue>
#include <mutex>
#include <array>

#include "utils/semaphore.hpp"
#include "utils/fifo.hpp"

namespace lib
{
template <class T> class Pool
{
public:
    Pool(uint32_t nbItems);
    ~Pool();

    bool init();

    T *popOutdatedItem(void);
    T *popRenderedItem(void);
    void pushOutdatedItem(T *item);
    void pushRenderedItem(T *item);
    void sendToken();

private:
    Fifo<T *> m_actives;
    Fifo<T *> m_inactives;

    Semaphore m_availabilitySem;
    uint32_t m_nbItems;
    std::vector<T *> m_refVector;
    bool m_ready = false;
};

template <class T> Pool<T>::Pool(uint32_t nbItems) :
                            m_availabilitySem(nbItems),
                            m_nbItems(nbItems)
{
        std::cout << "Pool initialisation" << std::endl;
}

template <class T> Pool<T>::~Pool() {
    m_ready = false;

    for (size_t i = 0; i < m_nbItems; i++)
        delete m_refVector[i];

    std::cout << "Pool terminated" << std::endl;
}

/* TODO Out of memory case:
* It's difficult to reproduce in OSX, but we have to manage this exception
* imperatively */

template <class T> bool Pool<T>::init() {
    if (m_ready == true) {
        std::cerr << __func__ << " : Pool already initialized" << std::endl;
        return false;
    }
    try {
        m_refVector.resize(m_nbItems);
        for (unsigned long i = 0; i < m_nbItems; i++) {
                T *tmp = new T();
                m_refVector[i] = tmp;
                m_inactives.push(tmp);
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
template <class T> T *Pool<T>::popOutdatedItem(void) {
    if (m_ready == false) {
        std::cerr << __func__ << " : Pool not initialized" << std::endl;
        return nullptr;
    }
    m_availabilitySem.wait();
    T *output = m_inactives.pop();
    return output;
}

template <class T> void Pool<T>::pushRenderedItem(T *item) {
    if (m_ready == false) {
        std::cerr << __func__ << " : Pool not initialized" << std::endl;
        return;
    }
    m_actives.push(item);
}

/* Consumer side */
template <class T> T *Pool<T>::popRenderedItem(void) {
    if (m_ready == false) {
        std::cerr << __func__ << " : Pool not initialized" << std::endl;
        return nullptr;
    }
    if (m_actives.size() == 0)
        return nullptr;
    T *output = m_actives.pop();
    return output;
}

template <class T> void Pool<T>::pushOutdatedItem(T *item) {
    if (m_ready == false) {
        std::cerr << __func__ << " : Pool not initialized" << std::endl;
        return;
    }
    m_inactives.push(item);
    m_availabilitySem.notify();
}

/* Exception side, send a artificial token */
template <class T> void Pool<T>::sendToken() {
    if (m_ready == false) {
        std::cerr << __func__ << " : Pool not initialized" << std::endl;
        return;
    }
    m_availabilitySem.notify();
}

}
#endif
