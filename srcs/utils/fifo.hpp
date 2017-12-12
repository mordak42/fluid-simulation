
#ifndef __FIFO__
# define __FIFO__

#include <iostream>

namespace lib
{
template <class T> class Fifo
{

typedef struct s_list {
    T content;
    struct s_list *next;
} t_list;

public:
    Fifo();
    ~Fifo();

    bool push(T elem);
    T pop();
    T getLastPushedElem();
    size_t size();

private:
    struct s_list *m_firstElem = nullptr;
    struct s_list *m_lastElem = nullptr;
    size_t m_size = 0;
    std::mutex m_mutex;
};

template <class T> Fifo<T>::Fifo() {}

template <class T> Fifo<T>::~Fifo() {
    t_list *tmp;

    while (m_firstElem) {
        tmp = m_firstElem->next;
        free(m_firstElem);
        m_firstElem = tmp;
    }
}

template <class T> bool Fifo<T>::push(T elem) {
    std::lock_guard<std::mutex>lock(m_mutex);
    t_list *newElem = (t_list *)malloc(sizeof(t_list));
    if (newElem == nullptr)
        return false;
    newElem->content = elem;
    newElem->next = nullptr;
    m_size++;
    if (m_lastElem == nullptr) {
        m_lastElem = newElem;
        m_firstElem = newElem;
    }
    else {
        m_lastElem->next = newElem;
        m_lastElem = newElem;
    }
    return true;
}

template <class T> T Fifo<T>::pop() {
    std::lock_guard<std::mutex>lock(m_mutex);
    if (m_firstElem == nullptr)
        return nullptr;
    T output;
    output = m_firstElem->content;
    t_list *tmp = m_firstElem->next;
    free(m_firstElem);
    m_size--;
    if (m_size == 0) {
        m_firstElem = nullptr;
        m_lastElem = nullptr;
    }
    else
        m_firstElem = tmp;
    return output;
}

template <class T> T Fifo<T>::getLastPushedElem() {
    std::lock_guard<std::mutex>lock(m_mutex);
    if (m_firstElem == nullptr)
        return nullptr;
    return m_lastElem->content;
}

template <class T> size_t Fifo<T>::size() {
    return m_size;
}
};
#endif
