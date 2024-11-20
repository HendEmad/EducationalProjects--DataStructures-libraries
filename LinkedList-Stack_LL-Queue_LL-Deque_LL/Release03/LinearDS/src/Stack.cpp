#include "Release03/LinearDS/headers/Stack.h"
#include <functional>

template <typename T>
Stack<T>::Stack(IList<T>* list_type) : list(list_type) {}

template <typename T>
void Stack<T>::push(T data) {
    list -> pushBack(data);
}

template <typename T>
void Stack<T>::pop() {
    list -> popBack();
}

template <typename T>
T Stack<T>::top() {
    return list ->back();
}

template <typename T>
bool Stack<T>::empty() const {
    return list -> isEmpty();
}

template <typename T>
void Stack<T>::clear() {
    list ->clear();
}

template <typename T>
void Stack<T>::display() const {
    list ->display();
}

template <typename T>
void Stack<T>::process(const std::function <void(T&)>& func) {
    list ->process(func);
}

template <typename T>
Stack<T>::~Stack() {
    list -> clear();
}