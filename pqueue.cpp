#include "pqueue.h"


Pqueue::Pqueue(){
    m_head = NULL;
}

void Pqueue::enqueue(Cust* cust, int prio){
    if(!m_head || m_head->m_prio > prio){
        m_head = new Node(cust, prio, m_head);
        return;
    }
    Node* ptr = m_head;
    while(ptr->m_next && ptr->m_next->m_prio <= prio)
        ptr = ptr->m_next;
    ptr->m_next = new Node(cust, prio, ptr->m_next);
}

Cust* Pqueue::dequeue(){
    Node* ptr = m_head;
    Cust* guy = ptr->m_cust;
    m_head = m_head->m_next;
    delete ptr;
    return guy;
}

bool Pqueue::empty(){
    if(!m_head)
        return true;
    else 
        return false;
}

Pqueue::~Pqueue(){
    Node* ptr;
    while(m_head){
        ptr = m_head;
        m_head = m_head->m_next;
        delete ptr;
    }
}
