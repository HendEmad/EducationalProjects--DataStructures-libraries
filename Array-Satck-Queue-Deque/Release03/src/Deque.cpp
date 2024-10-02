// src/Deque.cpp
#include "Deque.h"

Deque::Deque(int init_capacity, int front, int rear) : Array(init_capacity), front(0), rear(0) {}

void Deque::print() const {
    if(is_empty()) {
        cout << "Deque is already empty!\n";
        return;
    }
    cout << "Deque content (front to rear): [";
    for(int i = 0; i < size; i++) {
        cout << arr_data[(front + i) % capacity] << " ";
    }
    cout << "]\n";
}

void Deque::add_element(int element) {
    return add_element(element, deque_operations::FRONT);
}

void Deque::add_element(int element, deque_operations op) {
    if(size == capacity) {
        resize_array(true, front, rear);
        front = 0;
        rear = size;
    }
    // add_front()
    if(op == deque_operations::FRONT) {
        front = (front - 1 + capacity) % capacity;
        arr_data[front] = element;
    }
    // add_rear() 
    else {
        arr_data[rear] = element;
        rear = (rear + 1) % capacity;
    }
    size++;
}

int Deque::remove_element() {
    return remove_element(deque_operations::FRONT);
}

int Deque::remove_element (deque_operations op) {
    if(is_empty())
        throw out_of_range("Deque is already empty");
    
    int value;
    if(op == deque_operations::FRONT) {
        value = arr_data[front];
        front = (front + 1) % capacity;
    }
    else {
        rear = (rear - 1 + capacity) % capacity;
        value = arr_data[rear];
    }
    size--;
    shrink_array(true, front, rear);
    return value;
}

int Deque::get_front() {
    if(is_empty())
        throw out_of_range("Deque is already empty!\n");
        
    return arr_data[front];
}

int Deque::get_rear() {
    if(is_empty())
        throw out_of_range("Deque is already empty!\n");
        
    return arr_data[(rear - 1 + capacity) % capacity];
}

int Deque::get_front_idx() {
    return front;
}

void Deque::process_elements(const function<void(int)>& process_fn) {
    // int element = remove_element(deque_operations::FRONT);
    for(int i = 0; i < size; i++) {
        cout << "The element of index " << i << endl;
        int element = arr_data[(front + i) % capacity];
        process_fn(element);
    }
}