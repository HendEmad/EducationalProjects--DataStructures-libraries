#include "Array.h"
#include "Stack.h"
using namespace std;

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