#include "Release03/LinearDS/headers/Deque.h"
#include <functional>

template <typename T>
Deque<T>::Deque(IList<T>* list_type) : list (list_type) {}

template <typename T>
void Deque<T>::push_front(T data) {
    list -> push_front(data);
}

template <typename T>
void Deque<T>::push_back(T data) {
    list ->pushBack(data);
}

template <typename T>
void Deque<T>::pop_front() {
    list ->popFront();
}

template <typename T>
void Deque<T>::pop_back() {
    list ->popBack();
}

template <typename T>
T Deque<T>::front() {
    list ->front();
}

template <typename T>
T Deque<T>::back() {
    list ->back();
}

template <typename T>
bool Deque<T>::empty() const {
    list ->isEmpty();
}

template <typename T>
void Deque<T>::clear() {
    list ->clear();
}

template <typename T>
void Deque<T>::display() const {
    list ->display();
}

template <typename T>
void Deque<T>::process(const std::function <void(T&)>& func) {
    list ->process(func);
}

template <typename T>
Deque<T>::~Deque() {
    list ->clear();
}