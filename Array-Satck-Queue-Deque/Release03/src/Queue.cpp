#include "Queue.h"

Queue::Queue(int init_capacity, int front, int rear) : front(0), rear(0) {}

void Queue::add_element(int element) {
    if(size == capacity){
        resize_array(true, front, rear);
        front = 0;
        rear = size;
    }
    arr_data[rear] = element;
    rear = (rear + 1) % capacity;
    size++;
}

int Queue::remove_element() {
    if(is_empty())
        throw out_of_range("Queue is empty!\n");

    int value = arr_data[front];
    
    for(int i = 1; i < size; i++) {
        int next_index = (front + i) % capacity;
        int prev_index = (front + i - 1) % capacity;
        arr_data[prev_index] = arr_data[next_index];
    }

    rear = (rear - 1 + capacity) % capacity;
    size--;

    shrink_array(true, front, rear);

    return value;
}

void Queue::process_elements(const function<void(int)>& process_fn) {
    for(int i = 0; i < size; i++) {
        int element = arr_data[(front + i) % capacity];
        process_fn(element);
    }
}

int Queue::get_front() {
    if(is_empty())
        throw out_of_range("Queue is already empty!\n");
    
    return arr_data[front];
}

void Queue::print() const {
    if(is_empty()) {
        cout << "Queue is empty!\n";
        return;
    }
    cout << "Queue content (front to rear): [";
    for(int i = 0; i < size; i++) {
        cout << arr_data[(front + i) % capacity] << " ";
    }
    cout << "]\n";
}