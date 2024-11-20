#include <iostream>
#include "ForwardList.h"

// construcor
template <typename T>
ForwardList<T>::ForwardList() : head(nullptr), size(0) {}

// Destructor
template <typename T>
ForwardList<T>::~ForwardList() {
    clear();
}

// Copy constructor
template <typename T>
ForwardList<T>::ForwardList(const ForwardList& other) : head(nullptr), size(0) {
    ForwardNode* curr = other.head.get();
    ForwardList* tail = nullptr;
    while(curr) {
        auto newNode = std::make_unique<ForwardNode> (curr -> data);
        if(!head) {
            head = std::move(newNode);
            tail = head.get();
        }
        else {
            tail -> next = std::move(newNode);
            tail = tail -> next.get();
        }

        curr = curr ->next.get();
    }
    size = other.size;
}

// Copy assignment operator
template <typename T>
ForwardList<T>& ForwardList<T>::operator= (const ForwardList& other) {
    if(this == &other) {
        return *this;
    }
    clear();
    ForwardNode* curr = other.head.get();
    ForwardNode* tail = nullptr;
    while(curr) {
        auto newNode = std::make_unique<ForwardNode> (curr -> data);
        if(!head) {
            head = std::move(newNode);
            tail = head.get();
        }
        else {
            tail -> next = std::move(newNode);
            tail = tail -> next.get();
        }

        curr = curr ->next.get();
    }
    size = other.size;

    return *this;
}

// Move cosntructor
template <typename T>
ForwardList<T>::ForwardList(ForwardList&& other) noexcept : 
                            head(std::move(other.head)), 
                            size(other.size) {
    other.size = 0;
}

// Move assignment operator
template <typename T>
ForwardList<T>& ForwardList<T>::operator= (ForwardList&& other) noexcept {
    if(this == &other) {
        return *this;
    }
    head = std::move(other.head);
    size = other.size;
    other.size = 0;
    return *this;
}

// A function to add a node to the front of the forward list
template <typename T>
void ForwardList<T>::pushFront(T data) {
    auto newNode = std::make_unique<ForwardNode> (data);
    newNode -> next = std::move(head);
    head = move(newNode);
    size ++;
}

// A function to delete a node from the forward list front side
template <typename T>
void ForwardList<T>::popFront() {
    if(head) {
        head = std::move(head ->next);
        size --;
    }
}

// A function to add a node to the back of the forward list
template <typename T>
void ForwardList<T>::pushBack(T data) {
    auto newNode = std::make_unique <ForwardNode>(data);
    if(!head) {
        head = std::move(newNode);
    }
    else {
        ForwardNode* curr = head.get();
        while(curr -> next) {
            curr = curr ->next.get();
        }
        curr ->next = std::move(newNode);
    }
    size++;
}

// A function to delete a node from the back side of the list
template <typename T>
void ForwardList<T>::popBack() {
    if(!head) {  // empty list
        return;
    }

    if(!head ->next) {  // one node
        head.reset();
    }
    else {
        ForwardNode* curr = head.get();
        while(curr ->next && curr ->next ->next) {
            curr = curr -> next.get();
        }
        curr ->next.reset();
    }
    size--;
}

// A function to add element data to a particular index
template <typename T>
void ForwardList<T>::insert(size_t index, T data) {
    if(index < 0 || index > size) {
        throw std::out_of_range("Index out of bouns");
    }

    if(index == 0) {
        pushFront(data);
        return;
    }

    ForwardNode* curr = head.get();
    for(size_t i = 0; i < index - 1; i++) {
        curr = curr ->next.get();
    }

    auto newNode = std::make_unique<ForwardNode>(data);
    newNode ->next = std::move(curr ->next);
    curr ->next = std::move(newNode);

    size++;
}

// A function to delete an element of a node at a particular index
template <typename T>
void ForwardList<T>::erase(size_t index) {
    if(index < 0 || index > size) {
        throw std::out_of_range("Index out of bounds");
    }

    if(index == 0) {
        popFront();
        return;
    }

    ForwardNode* curr = head.get();
    for(size_t i = 0; i < index - 1; i++) {
        curr = curr ->next.get();
    }

    curr ->next = std::move(curr ->next ->next);

    size--;
}

// A function to clear the whole forward list nodes
template <typename T> 
void ForwardList<T>::clear() {
    head.reset();
    size = 0;
}

// A function to print all the data of the forward list
template <typename T>
void ForwardList<T>::display() const {
    ForwardNode* curr = head.get();
    while(curr) {
        std::cout << curr ->data << " -> ";
        curr = curr ->next.get();
    }
    std::cout << "Null\n";
}

// A function to enable the usage of lambda functions or high order functions
template <typename T>
void ForwardList<T>::process(const std::function<void(T&)>& func) {
    ForwardNode* curr = head.get();
    while (curr) {
        func(curr->data);
        curr = curr->next.get();
    }
}

// A function to get the front of the list
template <typename T>
typename ForwardList<T>::ForwardNode* ForwardList<T>::getFront() const {
    return head.get();
}