// src/Stack.h
#ifndef STACK_H
#define STACK_H

#include "Array.h"
#include "AbstractDS.h"
#include <functional>
#include <utility>
#include <stdexcept>
using namespace std;

class Stack : public AbstractDS{
    Array array;
public:
    Stack(int init_capacity = 10);
    void add_element(int element) override;
    int remove_element() override;
    int peek();

    // Variadic emplace function
    template <typename... Args>  // template to accept multiple parameters
    void emplace(Args&&... args);  // accepts lvalues and rvalues
    
    void swap(Stack& other) noexcept;
    void print() override;
    void process_elements(const function <void(int)>& process_fn) override;
    void search(int element, int front = -1) override;
};

#endif // STACK_H