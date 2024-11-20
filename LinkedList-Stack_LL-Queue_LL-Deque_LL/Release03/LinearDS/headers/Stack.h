#ifndef STACK_H
#define STACK_H

#include "Release02/LinearDS/headers/IDataStructure.h"
#include "Release02/List/headers/IList.h"
#include <functional>

template <typename T>
class Stack : public IDataStructure<T> {
private:
    IList<T>* list;

public:
    explicit Stack(IList<T>* list_type) {}
    void push(T data);
    void pop();
    T top();
    bool empty() const override;
    void clear() override;
    void display() const override;
    void process(const std::function <void(T&)>& func);
    ~Stack();
};

#endif // STACK_H