// src/ Array.h
#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <memory>
#include <functional>
using namespace std;

enum class data_structures {ARRAY, STACK, QUEUE, DEQUE};
const int SHRINK_THRESHOLD = 4;  // for shrinking threshold

class Array {
protected:
    unique_ptr<int[]> arr_data;  // The array will have exclusive ownership
    int capacity;
    int size;

    void resize_array(bool is_circular = false, int front = 0, int rear = 0);
    void shrink_array(bool is_circular = false, int front = 0, int rear = 0);
    void is_found(int element, int index);

public:
    int get_size() const;
    int get_capacity() const;
    bool is_empty() const;
    virtual void print() const = 0;
    virtual void add_element(int element) = 0;
    virtual int remove_element() = 0;
    virtual void process_elements(const function<void(int)>& process_fn) = 0;
    void search(int element, data_structures ds, int front = -1);
    Array(int init_capacity = 10, int size = 0);
};

#endif // ARRAY_H