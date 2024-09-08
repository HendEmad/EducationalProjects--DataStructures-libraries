#include <iostream>
using namespace std;

struct Array {
    int* arr_data;
    int capacity;
    int size;
};

// --------------------Array--------------------------
void init_array(Array& arr, int init_capacity = 10) {
    arr.arr_data = new int[arr.capacity];
    arr.capacity = init_capacity;
    arr.size = 0;
}

void resize_array(Array& arr) {
    int* new_arr_data = new int [arr.capacity * 2];
    for(int i = 0; i < arr.size; i++) {
        new_arr_data[i] = arr.arr_data[i];
    }
    delete[] arr.arr_data;
    arr.arr_data = new_arr_data;
}

void add_element(Array& arr, int element) {
    if(arr.size == arr.capacity)
        resize_array(arr);
    arr.arr_data[arr.size++] = element;
}

int remove_element(Array& arr) {
    if(arr.size == 0)
        throw out_of_range("Array is already empty!\n");
    return arr.arr_data[arr.size--];
}

void free_array(Array& arr) {
    delete[] arr.arr_data;
}

// --------------------Stack--------------------------
struct Stack {
    Array arr;
};

void init_stack (Stack& stack, int init_capacity = 10) {
    init_array(stack.arr, init_capacity);
}

void push(Stack& stack, int element) {
    add_element(stack.arr, element);
}

int pop(Stack& stack) {
    return remove_element(stack.arr);
}

int peek(const Stack& stack) {
    if(stack.arr.size == 0)
        throw out_of_range("Stack is already empty!\n");
    return stack.arr.arr_data[stack.arr.size - 1];
}

void free_stack(Stack& stack) {
    free_array(stack.arr);
}

// --------------------Queue--------------------------
struct Queue {
    Array arr;
    int front;
    int rear;
};

void init_queue(Queue& queue, int init_capacity) {
    init_array(queue.arr, init_capacity);
    queue.front = 0;
    queue.rear = 0;
}

void add_element(Queue& queue, int element) {
    if(queue.arr.size == queue.arr.capacity)
        resize_array(queue.arr);
    queue.arr.arr_data[queue.rear] = element;
    queue.rear = (queue.rear + 1) % queue.arr.capacity;
    queue.arr.size++;
}

int remove_element(Queue& queue) {  
    if(queue.arr.size == 0)
        throw out_of_range("Queue is already empty!\n");
    int value = queue.arr.arr_data[queue.front];
    queue.front = (queue.front + 1) % queue.arr.capacity;
    queue.arr.size --;
    return value;
}

int get_front(const Queue& queue) {
    if(queue.arr.size == 0)
        throw out_of_range("Queue is already empty!\n");
    return queue.arr.arr_data[queue.front];
}

void free_queue(Queue& queue) {
    free_array(queue.arr);
}