#ifndef FORWARDLIST_H
#define FORWARDLIST_H

#include "IList.h"
#include <iostream>
#include <functional>
#include <memory>

template<typename T>
class ForwardList : public IList<T> {
private:
    struct ForwardNode {
        T data;
        std::unique_ptr<ForwardNode> next;
        ForwardNode(T value) : data(value), next(nullptr) {}
    };
    std::unique_ptr<ForwardNode> head;
    size_t size;

public:
    ForwardList();
    ~ForwardList();
    ForwardList(const ForwardList& other);  // copy cosntructor
    ForwardList& operator=(const ForwardList& other);  // copy assignemnt operator
    ForwardList(ForwardList&& other) noexcept;  // move constructor
    ForwardList& operator=(ForwardList&& other) noexcept;  // move assignment operator

    void pushFront(T data) override;
    void pushBack(T data) override;
    void popFront() override;
    void popBack() override;
    void insert(size_t index, T data) override;
    void erase (size_t idnex) override;
    void clear() override;
    void display() const override;
    void process(const std::function<void(T&)>& func) override;
    ForwardNode* getFront() const;
    size_t getSize() const override { return size; }
};

#include "ForwardList.cpp"
#endif // FORWARDLIST_H