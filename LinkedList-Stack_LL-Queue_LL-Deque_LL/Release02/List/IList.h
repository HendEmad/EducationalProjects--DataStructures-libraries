#ifndef ILIST_H
#define ILIST_H

#include <memory>
#include <functional>
#include <iostream>
#include <stdexcept>

template <typename T>
class IList {
public:
    virtual ~IList() = default;
    virtual void pushFront(T data) = 0;
    virtual void pushBack(T data) = 0;
    virtual void insert(size_t index, T data) = 0;
    virtual void erase(size_t index) = 0;
    virtual void popFront() = 0;
    virtual void popBack() = 0;
    virtual void clear() = 0;
    virtual void display() const = 0;
    virtual void process(const std::function<void(T&)>& func) = 0;
    virtual size_t getSize() const = 0;
};

#endif // ILIST_H