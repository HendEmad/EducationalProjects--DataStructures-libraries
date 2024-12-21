#include <iostream>
#include "AbstractDS.h"
#include "Array.h"
#include "Stack.h"
#include "Queue.h"
#include "Deque.h"
using namespace std;

int main() {
    // -----------------Stack testing---------------------
    cout << "----------------------stack testing-------------------\n";
    unique_ptr<AbstractDS> stack = make_unique<Stack> (2); 
    stack->add_element(10);
    stack->add_element(20);
    stack->add_element(30);
    stack->add_element(40);
    stack->print();

    stack->remove_element();
    stack->print();

    stack->search(20);

    // -----------------Queue testing---------------------
    cout << "----------------------Queue testing-------------------\n";
    unique_ptr<AbstractDS> queue = make_unique<Queue> (2); 
    queue->add_element(10);
    queue->add_element(20);
    queue->add_element(30);
    queue->add_element(40);
    queue->print();

    queue->remove_element();
    queue->print();

    Queue* q_ptr = dynamic_cast<Queue*> (queue.get());
    if(q_ptr) cout << q_ptr -> get_front_idx() << endl;
    queue->search(20, q_ptr ->get_front_idx());

    // -----------------Deque testing---------------------
    cout << "----------------------Deque testing-------------------\n";
    unique_ptr<AbstractDS> deque = make_unique<Deque> (2); 
    Deque* d_ptr = dynamic_cast<Deque*> (deque.get());
    d_ptr->add_element(10, deque_operations::REAR);
    deque->add_element(20);
    d_ptr->add_element(30, deque_operations::REAR);
    deque->add_element(40);
    if(d_ptr) cout << d_ptr -> get_front_idx() << endl;
    deque->print();

    deque->remove_element();
    if(d_ptr) cout << d_ptr -> get_front_idx() << endl;
    deque->print();

    if(d_ptr) cout << d_ptr -> get_front_idx() << endl;
    deque->search(10, d_ptr ->get_front_idx());
}