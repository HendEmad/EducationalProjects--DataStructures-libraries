// src/main.cpp
#include "Stack.h"
#include "Queue.h"
#include "Deque.h"
using namespace std;

int main() {
    // --------------------Stack Testing--------------------------
    cout << "--------------------Stack Testing--------------------------\n";
    unique_ptr<Array> stack = make_unique<Stack> ();
    cout << "Size: " << stack ->get_size() << ", and capacity: " << stack ->get_capacity() << endl;
    stack ->add_element(10);
    stack ->add_element(20);
    stack ->add_element(30);
    stack ->print();
    stack ->remove_element();
    stack ->print();
    Stack* s_ptr = dynamic_cast<Stack*> (stack.get());
    if(s_ptr) cout << s_ptr ->peek() << endl;
    stack->process_elements([](int x){cout << "Stack element " << x << " is in processing..." << endl;});
    cout << "Searching function testing: \n";
    stack ->search(10, data_structures::STACK);

    // --------------------Queue testing--------------------------
    cout << "\n--------------------Queue Testing--------------------------\n";
    unique_ptr<Array> queue = make_unique<Queue> (2);
    queue ->add_element(10);
    queue ->add_element(20);
    queue ->add_element(30);
    queue ->print();
    queue ->remove_element();
    queue ->print();
    
    Queue* q_ptr = dynamic_cast<Queue*>(queue.get());
    if(q_ptr) cout << q_ptr ->get_front() << endl;
    queue ->process_elements([](int x) {cout << "Queue element " << x << " is in processing..." << endl;});
    cout << "Searching function testing: \n";
    queue ->search(30, data_structures::QUEUE, q_ptr->get_front());

    // --------------------Deque testing--------------------------
    cout << "\n--------------------Deque Testing--------------------------\n";
    unique_ptr<Array> deque = make_unique<Deque> (2);
    Deque* d_ptr = dynamic_cast<Deque*> (deque.get());
    if(d_ptr) {
        d_ptr ->add_element(10, deque_operations::FRONT);
        d_ptr ->add_element(20, deque_operations::FRONT);
        d_ptr ->add_element(30, deque_operations::REAR);
        d_ptr ->add_element(40, deque_operations::REAR);
    }  // 20 10 30
    deque ->add_element(10);  
    deque ->print();
    if(d_ptr) {
        d_ptr ->remove_element(deque_operations::FRONT);
        d_ptr ->remove_element(deque_operations::REAR);
    }
    cout << d_ptr ->get_front_idx() << endl;
    cout << d_ptr ->get_size() << endl;
    deque ->print();
    if(d_ptr) {
        cout << d_ptr ->get_front() << endl;
        cout << d_ptr ->get_rear() << endl;
    }
    deque ->process_elements([](int x) {cout << "Deque element " << x << " is in processing..." << endl;});
    cout << "Searching function testing: \n";
    deque ->search(30, data_structures::DEQUE, d_ptr ->get_front());
}