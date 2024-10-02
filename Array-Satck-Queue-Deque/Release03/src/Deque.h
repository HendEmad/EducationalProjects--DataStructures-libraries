// src/Deque.h
#ifndef DEQUE_H
#define DEQUE_H

#include "Array.h"

enum class deque_operations {FRONT, REAR};

class Deque : public Array {
    int front, rear;
    
public:
    Deque(int init_capacity = 10, int front = 0, int rear = 0);
    void add_element(int element) override;  // overriding
    int remove_element() override;  // overriding
    void add_element(int element, deque_operations op);  // overloading
    int remove_element(deque_operations op);  // overloading
    int get_rear();
    void print() const override;
    int get_front();
    void process_elements(const function<void(int)>& process_fn) override;
    int get_front_idx();
};

#endif // DEQUE_H