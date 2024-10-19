// src/Stack.h
#ifndef STACK_H
#define STACK_H

#include "Array.h"
#include "AbstractDS.h"
#include <functional>
using namespace std;

class Stack : public AbstractDS{
    Array array;
public:
    Stack(int init_capacity = 10);
    void add_element(int element) override;
    int remove_element() override;
    int peek();
    void print() override;
    void process_elements(const function <void(int)>& process_fn) override;
    void search(int element, int front = -1) override;
};

#endif // STACK_H