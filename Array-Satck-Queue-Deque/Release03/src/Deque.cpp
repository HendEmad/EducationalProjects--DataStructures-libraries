// src/Deque.cpp
#include "Deque.h"
using namespace std;

Deque::Deque(int init_capacity) : array(init_capacity), front(0), rear(0) {}

void Deque::add_element(int element, deque_operations op) {
    if(array.get_size() == array.get_capacity()) {
        array.resize_array(true, front, rear);
        front = 0; 
        rear = array.get_size();
    }
    // add_front
    if(op == deque_operations::FRONT) {
        front = (front - 1 + array.get_capacity()) % array.get_capacity();
        array.get_arr_data()[front] = element;
    }
    // add_rear
    else {
        array.get_arr_data()[rear] = element;
        rear = (rear + 1) % array.get_capacity();
    }
    array.increase_size_1();
}

void Deque::add_element(int element) {
    return add_element(element, deque_operations::FRONT);
}

int Deque::remove_element(deque_operations op) {
    if(array.is_empty())
        throw out_of_range("Deque is empty\n");
    
    int value;
    if(op == deque_operations::FRONT) {
        value = array.get_arr_data()[front];
        front = (front + 1) % array.get_capacity();
    }
    else {
        rear = (rear - 1 + array.get_capacity()) % array.get_capacity();
        value = array.get_arr_data()[rear];
    }
    array.decrease_size_1();
    array.shrink_array(true, front, rear);
    return value;
}

int Deque::remove_element() {
    return remove_element(deque_operations::FRONT);
}

void Deque::print() {
    if(array.is_empty()) {
        cout << "Deque is already empty!\n";
        return;
    }
    cout << "Deque content (front to rear): [";
    for(int i = 0; i < array.get_size(); i++) {
        cout << array.get_arr_data()[(front + i) % array.get_capacity()] << " ";
    }
    cout << "]\n";   
}

int Deque::get_front() {
    if(array.is_empty()) 
        throw out_of_range ("Deque is empty\n");
    
    return array.get_arr_data()[front];
}

int Deque::get_rear() {
    if(array.is_empty()) 
        throw out_of_range ("Deque is empty\n");
    
    return array.get_arr_data()[(rear - 1 + array.get_capacity()) % array.get_capacity()];   
}

void Deque::process_elements(const function<void(int)>& process_fn) {
    for(int i = 0; i < array.get_size(); i++) {
        cout << "The element of index " << i << endl;
        int element = array.get_arr_data()[(front + i) % array.get_capacity()];
        process_fn(element);
    }
}

int Deque::get_front_idx() const {
    return front;
}

void Deque::search(int element, int front) {
    int idx = -1;
    for (int i = 0; i < array.get_size() && !array.is_empty(); i++) {  
        // int index = i;  
        int index = (this->front + i) % array.get_capacity();
        // int normalized_index = i;

        cout << "Checking index: " << i << " with value: " << array.get_arr_data()[index] << endl;
        if (array.get_arr_data()[index] == element) {
            // idx = normalized_index;  
            idx = i;    
            break;
        }        
    }

    array.is_found(element, idx);    
}