#ifndef DOUBLY_LIST_H
#define DOUBLY_LIST_H

#include <memory>
#include <functional>
#include <stdexcept>
#include <iostream>
#include "IList.h"

template <typename T>
class DoublyList : public IList <T>{
private:
    struct DoublyNode {
        T data;
        std::unique_ptr<DoublyNode> next;
        DoublyNode* prev = nullptr;

        DoublyNode(T value) : data(value), next(nullptr), prev(nullptr) {}
    };

    std::unique_ptr<DoublyNode> head;  
    DoublyNode* tail;                  
    size_t size;                      

public:
    DoublyList();
    ~DoublyList();
    DoublyList(const DoublyList& other);
    DoublyList(DoublyList&& other) noexcept;
    DoublyList& operator=(const DoublyList& other);
    DoublyList& operator=(DoublyList&& other) noexcept;

    void pushFront(T data) override;
    void pushBack(T data) override;
    void popFront() override;
    void popBack() override;
    void insert(size_t index, T data) override;
    void erase(size_t index) override;
    void clear() override;
    void display() const override;
    void process(const std::function<void(T&)>& func) override;
    
    DoublyNode* getFront() const;
    size_t getSize() const override{ return size; }
};

#include "DoublyList.cpp"
#endif // DOUBLY_LIST_H
