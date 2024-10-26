// src/Array.h
#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <memory>
#include <functional>

enum class data_structures { ARRAY, STACK, QUEUE, DEQUE };

const int SHRINK_THRESHOLD = 4;  

class Array {
private:
    std::unique_ptr<int[]> arr_data;  
    int capacity;
    int size;

public:
    void resize_array(bool is_circular = false, int front = 0, int rear = 0);
    void shrink_array(bool is_circular = false, int front = 0, int rear = 0);
    void is_found(int element, int index);
    int get_size() const;
    int get_capacity() const;
    bool is_empty() const;
    void print();
    void add_element(int element);
    int remove_element();
    void process_elements(const std::function<void(int)>& process_fn);
    Array(int init_capacity = 10);
    void search(int element, int front = -1);
    int get_element(int index) const;
    int* get_arr_data();
    int decrease_size_1();
    int increase_size_1();
    int* begin();  // begin() --> pointer
    const int* cbegin() const;  // cbegin()  --> pointer 
    int* end();
    const int* cend() const;
};

#endif // ARRAY_H
