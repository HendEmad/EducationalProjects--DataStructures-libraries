#ifndef QUEUE_H
#define QUEUE_H

#include "Release03/LinearDS/headers/IDataStructure.h"
#include "Release03/List/headers/IList.h"
#include <functional>

template <typename T>
class Queue : public IDataStructure<T> {
private:
    IList<T>* list;

public:
    explicit Queue(IList<T>* list_type) {}
    void enqueue(T data);
    void dequeue();
    T front();
    bool empty() const override;
    void clear() override;
    void display() const override;
    void process(const std::function <void(T&)>& func);
    ~Queue();
};

#endif // QUEUE_H