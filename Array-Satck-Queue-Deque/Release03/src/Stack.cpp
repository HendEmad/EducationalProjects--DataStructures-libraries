#include "Array.h"
#include "Stack.h"
using namespace std;

Stack::Stack(int init_capacity) : Array(init_capacity) {}

void Stack::add_element(int element) {
    Array::add_element(element); 
}

void Stack::print() const {
    Array::print();
}

int Stack::remove_element(){
    if (is_empty()) 
        throw out_of_range("Stack is empty!\n");
    
    int value = arr_data[size - 1];  
    size--;  
    shrink_array();  
    return value;
}

int Stack::peek() {
    if (is_empty()) 
        throw out_of_range("Stack is empty!\n");

    return arr_data[size - 1]; 
}

void Stack::process_elements(const function<void(int)>& process_fn) {
    while(!is_empty()) {
        int element = Stack::remove_element();
        process_fn(element);
    }
}
