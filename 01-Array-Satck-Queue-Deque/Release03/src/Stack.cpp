#include "Array.h"
#include "Stack.h"
#include <utility>

Stack::Stack(int init_capacity) : array(init_capacity){}

void Stack::add_element(int element) {
    array.add_element(element);
}

int Stack::remove_element() {
    return array.remove_element();
}

int Stack::peek() {
    if(array.is_empty())
        throw out_of_range("stack is empty\n");
    
    return array.get_element(array.get_size() - 1);
}

template <typename... Args>
void Stack::emplace(Args&&... args) {
    // Assuming T is the type you want to construct and add to the stack
    if (array.get_size() >= array.get_capacity()) {
        array.resize_array(array.get_capacity() * 2); // Resize if necessary
    }

    // Construct the new element in place in the array
    array.add_element(T(std::forward<Args>(args)...));
}

// A function to swap the internal arrays of the stacks.
void Stack::swap(Stack& other) noexcept {
    std::swap(this->array, other.array); // Swap the internal arrays
}

void Stack::print() {
    array.print();
}

void Stack::process_elements(const function<void(int)>& process_fn) {
    while(!array.is_empty()) {
        int element = remove_element();
        process_fn(element);
    }
}

void Stack::search(int element, int front) {
    int idx;
    for(int i = array.get_size() - 1; i >= 0; i--) {
        if(array.get_arr_data()[i] == element) {
            idx = i;
            break;
        }
    }
    array.is_found(element, idx);
}