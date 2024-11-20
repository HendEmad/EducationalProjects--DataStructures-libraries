#include "List/headers/DoublyList.h"

template <typename T>
DoublyList<T>::DoublyList() : head(nullptr), tail(nullptr), size(0) {}

template <typename T>
DoublyList<T>::~DoublyList() {
    clear();
}

template <typename T>
DoublyList<T>::DoublyList(const DoublyList& other) : head(nullptr), tail(nullptr), size(0) {
    DoublyNode* curr = other.head.get();
    while (curr) {
        pushBack(curr->data);
        curr = curr->next.get();
    }
}

template <typename T>
DoublyList<T>::DoublyList(DoublyList&& other) noexcept : head(std::move(other.head)), tail(other.tail), size(other.size) {
    other.tail = nullptr;
    other.size = 0;
}

template <typename T>
DoublyList<T>& DoublyList<T>::operator=(const DoublyList& other) {
    if (this != &other) {
        clear();
        DoublyNode* curr = other.head.get();
        while (curr) {
            pushBack(curr->data);
            curr = curr->next.get();
        }
    }
    return *this;
}

template <typename T>
DoublyList<T>& DoublyList<T>::operator=(DoublyList&& other) noexcept {
    if (this != &other) {
        clear();
        head = std::move(other.head);
        tail = other.tail;
        size = other.size;
        other.tail = nullptr;
        other.size = 0;
    }
    return *this;
}

template <typename T>
void DoublyList<T>::pushFront(T data) {
    auto newNode = std::make_unique<DoublyNode>(data);
    if (head) {
        newNode->next = std::move(head);
        newNode->next->prev = newNode.get();
    } else {
        tail = newNode.get();
    }
    head = std::move(newNode);
    size++;
}

template <typename T>
void DoublyList<T>::pushBack(T data) {
    auto newNode = std::make_unique<DoublyNode>(data);
    newNode->prev = tail;
    if (tail) {
        tail->next = std::move(newNode);
    } else {
        head = std::move(newNode);
    }
    tail = tail->next.get();
    size++;
}

template <typename T>
void DoublyList<T>::popFront() {
    if (head) {
        head = std::move(head->next);
        if (head) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        size--;
    }
}

template <typename T>
void DoublyList<T>::popBack() {
    if (tail) {
        if (tail->prev) {
            tail = tail->prev;
            tail->next.reset();
        } else {
            head.reset();
            tail = nullptr;
        }
        size--;
    }
}

template <typename T>
void DoublyList<T>::insert(size_t index, T data) {
    if (index > size) {
        throw std::out_of_range("Index out of bounds");
    }
    if (index == 0) {
        pushFront(data);
        return;
    }
    if (index == size) {
        pushBack(data);
        return;
    }

    auto newNode = std::make_unique<DoublyNode>(data);
    DoublyNode* curr = head.get();
    for (size_t i = 0; i < index - 1; i++) {
        curr = curr->next.get();
    }

    newNode->next = std::move(curr->next);
    newNode->prev = curr;
    if (newNode->next) {
        newNode->next->prev = newNode.get();
    }
    curr->next = std::move(newNode);
    size++;
}

template <typename T>
void DoublyList<T>::erase(size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of bounds");
    }

    DoublyNode* curr = head.get();
    for (size_t i = 0; i < index; ++i) {
        curr = curr->next.get();
    }

    if (curr->prev) {
        curr->prev->next = std::move(curr->next);
    }

    if (curr->next) {
        curr->next->prev = curr->prev;
    }

    if (curr == head.get()) {
        head = std::move(curr->next);
    }

    if (curr == tail) {
        tail = curr->prev;
    }

    size--;
    if (size == 0) {
        head = nullptr;
        tail = nullptr;
    }
}

template <typename T>
void DoublyList<T>::clear() {
    while (head) {
        head = std::move(head->next);
    }
    tail = nullptr;
    size = 0;
}

template <typename T>
void DoublyList<T>::display() const {
    DoublyNode* curr = head.get();
    while (curr) {
        std::cout << curr->data << " <-> ";
        curr = curr->next.get();
    }
    std::cout << "NULL\n";
}

template <typename T>
void DoublyList<T>::process(const std::function<void(T&)>& func) {
    DoublyNode* curr = head.get();
    while (curr) {
        func(curr->data);
        curr = curr->next.get();
    }
}

template <typename T>
T DoublyList<T>::front() const {
    if (!head) {
        throw std::runtime_error("List is empty");
    }
    return head->data;
}

template <typename T>
T DoublyList<T>::back() const {
    if (!tail) {
        throw std::runtime_error("List is empty");
    }
    return tail->data;
}