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




















/*
template <class T>
class Stack
{
    typedef struct stackitem
    {
        T Item;                 // On utilise le type T comme
        struct stackitem *Next; // si c'était un type normal.
    } StackItem;

    StackItem *Tete;

public:         // Les fonctions de la pile :
    Stack(void);
    Stack(const Stack<T> &);
                 // La classe est référencée en indiquant
                 // son type entre < et > ("Stack<T>").
                 // Ici, ce n'est pas une nécessité
                 // cependant.
    ~Stack(void);
    Stack<T> &operator=(const Stack<T> &);
    void push(T);
    T pop(void);
    bool is_empty(void) const;
    void flush(void);
};

template <class T>
Stack<T>::Stack(void) // La classe est référencée en indiquant
                      // son type entre < et > ("Stack<T>").
                      // C'est impératif en dehors de la
                      // déclaration de la classe.
{
    Tete = NULL;
    return;
}

template <class T>
Stack<T>::Stack(const Stack<T> &Init)
{
    Tete = NULL;
    StackItem *tmp1 = Init.Tete, *tmp2 = NULL;
    while (tmp1!=NULL)
    {
        if (tmp2==NULL)
        {
            Tete= new StackItem;
            tmp2 = Tete;
        }
        else
        {
            tmp2->Next = new StackItem;
            tmp2 = tmp2->Next;
        }
        tmp2->Item = tmp1->Item;
        tmp1 = tmp1->Next;
    }
    if (tmp2!=NULL) tmp2->Next = NULL;
    return;
}

template <class T>
Stack<T>::~Stack(void)
{
    flush();
    return;
}

template <class T>
Stack<T> &Stack<T>::operator=(const Stack<T> &Init)
{
    flush();
    StackItem *tmp1 = Init.Tete, *tmp2 = NULL;

    while (tmp1!=NULL)
    {
        if (tmp2==NULL)
        {
            Tete = new StackItem;
            tmp2 = Tete;
        }
        else
        {
            tmp2->Next = new StackItem;
            tmp2 = tmp2->Next;
        }
        tmp2->Item = tmp1->Item;
        tmp1 = tmp1->Next;
    }
    if (tmp2!=NULL) tmp2->Next = NULL;
    return *this;
}

template <class T>
void Stack<T>::push(T Item)
{
    StackItem *tmp = new StackItem;
    tmp->Item = Item;
    tmp->Next = Tete;
    Tete = tmp;
    return;
}

template <class T>
T Stack<T>::pop(void)
{
    T tmp;
    StackItem *ptmp = Tete;

    if (Tete!=NULL)
    {
        tmp = Tete->Item;
        Tete = Tete->Next;
        delete ptmp;
    }
    return tmp;
}

template <class T>
bool Stack<T>::is_empty(void) const
{
    return (Tete==NULL);
}

template <class T>
void Stack<T>::flush(void)
{
    while (Tete!=NULL) pop();
    return;
}


}
*/
