
#ifndef __FIFO__
# define __FIFO__

#include <iostream>

namespace std
{
template <class T> class fifo
{

typedef struct s_list {
    T content;
    struct s_list *next;
} t_list;

public:
    fifo();
    ~fifo();

    bool push(T elem);
    T pop();
    size_t size();

private:
    struct s_list *m_firstElem = nullptr;
    struct s_list *m_lastElem = nullptr;
    size_t m_size = 0;
    std::mutex m_mutex;
};

template <class T> fifo<T>::fifo() {}

template <class T> fifo<T>::~fifo() {
    t_list *tmp;

    while (m_firstElem) {
        tmp = m_firstElem->next;
        free(m_firstElem);
        m_firstElem = tmp;
    }
}

template <class T> bool fifo<T>::push(T elem) {
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

template <class T> T fifo<T>::pop() {
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

template <class T> size_t fifo<T>::size() {
    return m_size;
}
};
#endif
