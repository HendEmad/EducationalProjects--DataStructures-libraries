#ifndef CIRCULAR_LIST_H
#define CIRCULAR_LIST_H
#include "IList.h"

template <typename T>
class CircularList : public IList<T> {
public:
    struct CircularNode {
        T data;
        CircularNode* next;

        CircularNode(T value) : data(value), next(nullptr) {
            std::cout << "CircularNode created with data: " << value << std::endl;
        }
    };

    CircularNode* head;
    CircularNode* tail;
    size_t size;

public:
    CircularList();
    ~CircularList();
    CircularList(const CircularList& other);
    CircularList(CircularList&& other) noexcept; 
    CircularList& operator=(const CircularList& other);
    CircularList& operator=(CircularList&& other) noexcept;

    void pushFront(T data) override;
    void pushBack(T data) override;
    void popFront() override;
    void popBack() override;
    void insert(size_t index, T data) override;
    void erase(size_t index) override;
    void clear() override;
    void display() const override;
    void process(const std::function<void(T&)>& func) override;
    CircularNode* getFront() const {return head;}
    size_t getSize() const override {return size;}
};

#include "CircularList.cpp"
#endif //CIRCULAR_LIST_H