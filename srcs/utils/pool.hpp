
#ifndef __POOL_HPP__
# define __POOL_HPP__

#include <iostream>
#include <queue>
#include <mutex>

#include "utils/semaphore.hpp"
#include "utils/fifo.hpp"

namespace std
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

private:
    std::fifo<T *> m_actives;
    std::fifo<T *> m_inactives;

    semaphore m_availabilitySem;
    uint32_t m_nbItems;
    bool m_ready = false;
};

template <class T> Pool<T>::Pool(uint32_t nbItems) :
                            m_availabilitySem(nbItems),
                            m_nbItems(nbItems)
{
        cout << "Pool initialisation" << endl;
}

template <class T> Pool<T>::~Pool() {
    m_ready = false;

    size_t tmp;

    tmp = m_actives.size();
    for (size_t i = 0; i < tmp; i++)
        free(m_actives.pop());

    tmp = m_inactives.size();
    for (size_t i = 0; i < tmp; i++)
        free(m_inactives.pop());

    std::cout << "Pool terminated" << std::endl;
}

/* TODO Out of memory case:
* It's difficult to reproduce in OSX, but we have to manage this exeption
* imperatively */

template <class T> bool Pool<T>::init() {
    if (m_ready == true) {
        std::cerr << __func__ << " : Pool already initialized" << std::endl;
        return false;
    }
    try {
        for (unsigned long i = 0; i < m_nbItems; i++) {
                T *tmp = new T();
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
        cerr << __func__ << " : Pool not initialized" << endl;
        return nullptr;
    }
    m_availabilitySem.wait();
    T *output = m_inactives.pop();
    return output;
}

template <class T> void Pool<T>::pushRenderedItem(T *item) {
    if (m_ready == false) {
        cerr << __func__ << " : Pool not initialized" << endl;
        return;
    }
    m_actives.push(item);
}

/* Consumer side */
template <class T> T *Pool<T>::popRenderedItem(void) {
    if (m_ready == false) {
        cerr << __func__ << " : Pool not initialized" << endl;
        return nullptr;
    }
    if (m_actives.size() == 0)
        return nullptr;
    T *output = m_actives.pop();
    return output;
}

template <class T> void Pool<T>::pushOutdatedItem(T *item) {
    if (m_ready == false) {
        cerr << __func__ << " : Pool not initialized" << endl;
        return;
    }
    m_inactives.push(item);
    m_availabilitySem.notify();
}
}
#endif
