// src/Queue.cpp
#include "Queue.h"
using namespace std;

Queue::Queue(int init_capacity) : array(init_capacity), front(0), rear(0) {}

void Queue::add_element(int element){
    if(array.get_size() == array.get_capacity()) {
        array.resize_array(true, front, rear);
        front = 0;
        rear = array.get_size();
    }
    array.get_arr_data()[rear] = element;
    rear = (rear + 1) % array.get_capacity();
    array.increase_size_1();
}

int Queue::remove_element() {
    if(array.is_empty())
        throw out_of_range("Queue is empty\n");
    
    int value = array.get_arr_data()[front];

    for(int i = 1; i < array.get_size(); i++) {
        int next_index = (front + i) % array.get_capacity();
        int prev_index = (front + i - 1) % array.get_capacity();
        array.get_arr_data()[prev_index] = array.get_arr_data()[next_index];
    }

    rear = (rear - 1 + array.get_capacity()) % array.get_capacity();
    array.decrease_size_1();
    array.shrink_array(true, front, rear);
    return value;
}

void Queue::process_elements(const function<void(int)>& process_fn) {
    for(int i = 0; i < array.get_size(); i++) {
        int element = array.get_arr_data()[(front + i) % array.get_capacity()];
        process_fn(element);
    }
}

int Queue::get_front() {
    if(array.is_empty()) 
        throw out_of_range("Queue is empty\n");
    
    return array.get_arr_data()[front];
}

void Queue::print() {
    if(array.is_empty()) {
        cout << "Queue is empty\n";
        return;
    }
    cout << "Queue content (from front to rear): [";
    for(int i = 0; i < array.get_size(); i++) {
        cout << array.get_arr_data()[(front + i) % array.get_capacity()] << " ";
    }
    cout << "]\n";
}

void Queue::search(int element, int front) {
    int idx = -1;
    for(int i = 0; i < array.get_size(); i++) {
        int index = (front + i) % array.get_capacity();

        cout << "Checking index: " << index << " with value: " << array.get_arr_data()[index] << endl;
        if(array.get_arr_data()[index] == element) {
            idx = index;
            break;
        }
    }
    array.is_found(element, idx);
}

int Queue::get_front_idx() {
    return front;
}