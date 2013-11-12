#ifndef PQUEUE_H
#define PQUEUE_H
#include "cust.h"

class Pqueue{
public:
    Pqueue();
    ~Pqueue();
    void enqueue(Cust* cust, int prio);
    Cust* dequeue();
    bool empty();
    int get_prio() {return m_head->m_prio;}

private:
class Node{
public:
    Node(Cust* cust, int prio, Node* next){
        m_cust = cust;
        m_prio = prio;
        m_next = next;
    }
    Cust* m_cust;
    Node* m_next;
    int m_prio;
};

Node* m_head;
};

#endif
