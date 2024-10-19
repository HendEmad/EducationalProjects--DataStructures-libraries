// src/Array.cpp
#include "Array.h"
using namespace std;

Array::Array(int init_capacity) : capacity(init_capacity), size(0) {
    arr_data = make_unique<int[]>(init_capacity);
}

// A function to resize the data structure if the size is greater than the capacity
void Array::resize_array(bool is_circular, int front, int rear) {
    auto new_arr_data = make_unique<int[]>(capacity * 2);
        
    if (is_circular) {
        for (int i = 0; i < size; i++) {
            new_arr_data[i] = arr_data[(front + i) % capacity];
        }
    } else {
        for (int i = 0; i < size; i++) {
            new_arr_data[i] = arr_data[i];
        }
    }

    arr_data = move(new_arr_data);  
    capacity *= 2;
}

// A function to shrink the data structure by half if its size less than 1/4 its capacity
void Array::shrink_array(bool is_circular, int front, int rear) {
    if (size < capacity / SHRINK_THRESHOLD) {
        auto new_arr_data = make_unique<int[]>(capacity / 2);
        if(is_circular) {
            for(int i = 0; i < size; i++) {
                new_arr_data[i] = arr_data[(front + i) % capacity];
            }
        }
        else{
            for(int i = 0; i < size; i++) {
                new_arr_data[i] = arr_data[i];
            }
        }
            
        arr_data = move(new_arr_data);  
        capacity /= 2;
        front = 0;
        rear = size;
    }
}

int Array::decrease_size_1() {
    return size--;
}

int Array::increase_size_1() {
    return size++;
}

void Array::is_found(int element, int index) {
    if(index < 0)
        cout << "Element not found..\n";
    else
        cout << "The element " << element << " is found at index " << index << endl;
}

int Array::get_size() const {
    return size;
}

int Array::get_capacity() const {
    return capacity;
}

bool Array::is_empty() const {
    return size == 0;
}

void Array::print() {
    if (is_empty()) {
        cout << "Array is empty\n";
        return;
    }
    cout << "Array content: [";
    for (int i = 0; i < size; i++) {
        cout << arr_data[i] << " ";
    }
    cout << "]\n";
}

void Array::add_element(int element) {
    if (size == capacity) 
            resize_array();

    if(arr_data)
        arr_data[size++] = element;
}

int Array::remove_element() {
    if (is_empty()) 
        throw out_of_range("Array is empty!\n");
    
    int value = arr_data[size - 1];
    decrease_size_1();
    shrink_array();
    return value;  
}

// A function if we need to perform operations on the data structure elements, by passing a function.
void Array::process_elements(const function<void(int)>& process_fn) {
    for(int i = 0; i < size; i++) {
        int element = arr_data[i];
        process_fn(element);
    }
}

void Array::search(int element, int front) {
    int idx;
    for(int i = 0; i < size; i++) 
        if(arr_data[i] == element){
            idx = i;
            break;
        }
    is_found(element, idx);
}

int Array::get_element(int index) const {
    return arr_data[index];
}

int* Array::get_arr_data() {
    return arr_data.get();
}