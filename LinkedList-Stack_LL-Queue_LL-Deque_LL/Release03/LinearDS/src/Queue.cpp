#include "Release03/LinearDS/headers/Queue.h"
#include <functional>

template <typename T>
Queue<T>::Queue(IList<T>* list_type) : list(list_type) {}

template <typename T>
void Queue<T>::enqueue(T data) {
    list ->pushFront(data);
}

template <typename T>
void Queue<T>::dequeue() {
    list -> popBack();
}

template <typename T>
T Queue<T>::front() {
    list ->front();
}

template <typename T>
bool Queue<T>::empty() const {
    list ->isEmpty();
}

template <typename T>
void Queue<T>::clear() {
    list ->clear();
}

template <typename T>
void Queue<T>::display() const {
    list ->display();
}

template <typename T>
void Queue<T>::process (const std::function<void(T&)>& func) {
    list ->process(func);
}

template <typename T>
Queue<T>::~Queue() {
    list ->clear();
}