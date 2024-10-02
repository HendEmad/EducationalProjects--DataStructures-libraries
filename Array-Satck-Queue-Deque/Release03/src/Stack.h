// src/Stack.h
#ifndef STACK_H
#define STACK_H

#include "Array.h"

class Stack : public Array {
public:
    Stack(int init_capacity = 10);
    void add_element(int element) override;
    int remove_element();
    int peek();
    void print() const override;
    void process_elements(const function<void(int)>& process_fn) override;
};

#endif // STACK_H