#ifndef DEQUE_H
#define DEQUE_H

#include "Release03/LinearDS/headers/IDataStructure.h"
#include "Release03/List/headers/IList.h"
#include <functional>

template <typename T>
class Deque : public IDataStructure<T> {
private:
    IList<T>* list;

public:
    explicit Deque(IList<T>* list_type) {}
    void push_front(T data);
    void push_back(T data);
    void pop_front();
    void pop_back();
    T front();
    T back();
    bool empty() const override;
    void clear() override;
    void display() const override;
    void process(const std::function <void(T&)>& func);
    ~Deque();
};

#endif // QUEUE_H