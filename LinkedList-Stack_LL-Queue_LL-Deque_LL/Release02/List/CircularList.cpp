#include "CircularList.h"

template <typename T>
CircularList<T>::CircularList() : head(nullptr), tail(nullptr), size(0) {}

template <typename T>
CircularList<T>::~CircularList() {
    clear();
}

template <typename T>
CircularList<T>::CircularList(const CircularList& other) : head(nullptr), tail(nullptr), size(0) {
    if (!other.head) return;

    auto current = other.head;
    do {
        pushBack(current->data);
        current = current->next;
    } while (current != other.head);
}

template <typename T>
CircularList<T>::CircularList(CircularList&& other) noexcept
    : head(other.head), tail(other.tail), size(other.size) {
    other.head = nullptr;
    other.tail = nullptr;
    other.size = 0;
}

template <typename T>
CircularList<T>& CircularList<T>::operator=(const CircularList& other) {
    if (this != &other) {
        clear();
        CircularNode* current = other.head;
        do {
            pushBack(current->data);
            current = current->next;
        } while (current != other.head);
    }
    return *this;
}

template <typename T>
CircularList<T>& CircularList<T>::operator=(CircularList&& other) noexcept {
    if (this != &other) {
        clear();
        head = other.head;
        tail = other.tail;
        size = other.size;

        other.head = nullptr;
        other.tail = nullptr;
        other.size = 0;
    }
    return *this;
}

template <typename T>
void CircularList<T>::pushFront(T data) {
    CircularNode* newNode = new CircularNode(data);
    if (!head) {
        newNode->next = newNode; // Circular link to itself
        head = newNode;
        tail = newNode;
    } else {
        newNode->next = head;
        head = newNode;
        tail->next = head;
    }
    ++size;
}

template <typename T>
void CircularList<T>::pushBack(T data) {
    CircularNode* newNode = new CircularNode(data);
    if (!head) {
        newNode->next = newNode; // Circular link to itself
        head = newNode;
        tail = newNode;
    } else {
        newNode->next = head;
        tail->next = newNode;
        tail = newNode;
    }
    ++size;
}

template <typename T>
void CircularList<T>::popFront() {
    if (!head) return;

    if (head == tail) {
        delete head;
        head = nullptr;
        tail = nullptr;
    } else {
        CircularNode* temp = head;
        head = head ->next;
        tail ->next = head;
        delete temp;
    }
    --size;
}

template <typename T>
void CircularList<T>::popBack() {
    if (!head) return;

    if (head == tail) {
        delete head;
        head = nullptr;
        tail = nullptr;
    } else {
        CircularNode* current = head;
        while (current->next != tail) {
            current = current->next;
        }
        delete tail;
        tail = current;
        tail ->next = head;
    }
    --size;
}

template <typename T>
void CircularList<T>::insert(size_t index, T data) {
    if (index > size) throw std::out_of_range("Index out of bounds");
    if (index == 0) {
        pushFront(data);
        return;
    }
    if (index == size) {
        pushBack(data);
        return;
    }

    CircularNode* current = head;
    for (size_t i = 0; i < index - 1; ++i) {
        current = current->next;
    }

    CircularNode* newNode = new CircularNode(data);
    newNode->next = current->next;
    current->next = newNode;
    ++size;
}

template <typename T>
void CircularList<T>::erase(size_t index) {
    if (index >= size) throw std::out_of_range("Index out of bounds");
    if (index == 0) {
        popFront();
        return;
    }
    if (index == size - 1) {
        popBack();
        return;
    }

    CircularNode* current = head;
    for (size_t i = 0; i < index - 1; ++i) {
        current = current->next;
    }
    CircularNode* temp = head;
    current ->next = temp ->next;
    delete temp;
    --size;
}

template <typename T>
void CircularList<T>::clear() {
    while (size > 0) {
        popFront();
    }
}

template <typename T>
void CircularList<T>::display() const {
    if (!head) {
        std::cout << "NULL\n";
        return;
    }
    CircularNode* current = head;
    do {
        std::cout << current->data << " -> ";
        current = current->next;
    } while (current != head);
    std::cout << "(circular back to head)\n";
}

template <typename T>
void CircularList<T>::process(const std::function<void(T&)>& func) {
    if (!head) return;

    CircularNode* current = head;
    do {
        func(current->data);
        current = current->next;
    } while (current != head);
}