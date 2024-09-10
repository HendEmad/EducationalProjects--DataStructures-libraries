#include <iostream>
using namespace std;

// --------------------Base data structure--------------------------
struct Array {
    int* arr_data;
    int capacity;
    int size;
    
    bool is_empty() const{
        return size == 0;
    }

    void print() const {
        if(is_empty()) {
            cout << "Array is empty\n";
            return;
        }
        cout << "Array content: [";
        for(int i = 0; i < size; i++) {
            cout << arr_data[i] << " ";
        }
        cout << "]\n";
    }
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
    arr.capacity *= 2;
}

void add_element(Array& arr, int element) {
    if(arr.size == arr.capacity)
        resize_array(arr);
    arr.arr_data[arr.size++] = element;
}

int remove_element(Array& arr) {
    if(arr.is_empty())
        throw out_of_range("Array is already empty!\n");
    return arr.arr_data[--arr.size];
}

void free_array(Array& arr) {
    delete[] arr.arr_data;
    arr.size = 0;
    arr.capacity = 0;
}

// --------------------Stack--------------------------
struct Stack {
    Array arr;

    void print() const {
        if(arr.is_empty()) { 
            cout << "Stack is already empty!\n";
            return;
        }
        cout << "Stack content (top to bottom): [";
        for(int i = arr.size - 1; i >= 0; i--) 
            cout << arr.arr_data[i] << " ";
        
        cout << "]\n";
    }
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
    if(stack.arr.is_empty())
        throw out_of_range("Stack is already empty!\n");
    return stack.arr.arr_data[stack.arr.size - 1];
}

void free_stack(Stack& stack) {
    free_array(stack.arr);
    stack.arr.size = 0;
    stack.arr.capacity = 0;
}

// --------------------Queue--------------------------
struct Queue {
    Array arr;
    int front;
    int rear;

    void print() const {
        if(arr.is_empty()) {
            cout << "Queue is already empty!\n";
            return;
        }
        cout << "Queue content (front to rear): [";
        for(int i = 0; i < arr.size; i++) {
            cout << arr.arr_data[(front + i) % arr.capacity] << " ";
        }
        cout << "]\n";
    }
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
    if(queue.arr.is_empty())
        throw out_of_range("Queue is already empty!\n");
    int value = queue.arr.arr_data[queue.front];
    queue.front = (queue.front + 1) % queue.arr.capacity;
    queue.arr.size --;
    return value;
}

int get_front(const Queue& queue) {
    if(queue.arr.is_empty())
        throw out_of_range("Queue is already empty!\n");
    return queue.arr.arr_data[queue.front];
}

void free_queue(Queue& queue) {
    free_array(queue.arr);
    queue.arr.size = 0;
    queue.arr.capacity = 0;
}

// --------------------Deque--------------------------
struct Deque {
    Array arr;
    int front;
    int rear;

    void print() const {
        if(arr.is_empty()) {
            cout << "Deque is already empty!\n";
            return;
        }
        cout << "Deque content (front to rear): [";
        for(int i = 0; i < arr.size; i++) {
            cout << arr.arr_data[(front + i) % arr.capacity] << " ";
        }
        cout << "]\n";
    }
};

void init_deque(Deque& deque, int init_capacity) {
    init_array(deque.arr);
    deque.front = 0;
    deque.rear = 0;
}

void add_front(Deque& deque, int element) {
    if(deque.arr.size == deque.arr.capacity)
        resize_array(deque.arr);
    deque.front = (deque.front - 1 + deque.arr.capacity) % deque.arr.capacity;
    deque.arr.arr_data[deque.front] = element;
    deque.arr.size ++;
}

void add_rear(Deque& deque, int element) {
    if(deque.arr.size == deque.arr.capacity)
        resize_array(deque.arr);
    deque.arr.arr_data[deque.rear] = element;
    deque.rear = (deque.rear + 1) % deque.arr.capacity;
    deque.arr.size ++;
}

int remove_front(Deque& deque) {
    if(deque.arr.is_empty())
        throw out_of_range("Deque is already empty!\n");
    int value = deque.arr.arr_data[deque.front];
    deque.front = (deque.front + 1) % deque.arr.capacity;
    deque.arr.size --;
    return value;
}

int remove_rear(Deque& deque) {
    if(deque.arr.is_empty())
        throw out_of_range("Deque is already empty!\n");
    int value = deque.arr.arr_data[deque.rear];
    deque.rear = (deque.rear - 1 + deque.arr.capacity) % deque.arr.capacity;
    deque.arr.size --;
    return value;
}

int get_front(const Deque& deque) {
    if(deque.arr.is_empty())
        throw out_of_range("Deque is already empty!\n");
    return deque.arr.arr_data[deque.front];
}

int get_rear(Deque& deque) {
    if(deque.arr.is_empty())
        throw out_of_range("Deque is already empty!\n");
    return deque.arr.arr_data[(deque.rear - 1 + deque.arr.capacity) % deque.arr.capacity];
}

void free_deque(Deque& deque) {
    free_array(deque.arr);
    deque.arr.size = 0;
    deque.arr.capacity = 0;
}

int main() {
    {
        cout << "\n----------Array testing...------------------\n";
        Array arr;
        init_array(arr, 3);
        cout << arr.size << endl;  // 0
        cout << arr.capacity << endl;  // 3
        resize_array(arr);
        cout << arr.size << endl;  // 0
        cout << arr.capacity << endl;  // 6 
        add_element(arr, 5);
        add_element(arr, 6);
        add_element(arr, 7);
        add_element(arr, 8);
        add_element(arr, 9);
        add_element(arr, 10);
        cout << arr.size << endl;  // 6
        cout << arr.capacity << endl;  // 6
        arr.print();  // [5 6 7 8 9 10 ]

        remove_element(arr);
        remove_element(arr);
        cout << arr.size << endl;  // 4
        arr.print();  // [5 6 7 8 ]

        free_array(arr);
        cout << arr.size << endl;  // 4
        cout << arr.capacity << endl;  // 6
        arr.print();
    }

    cout << "\n----------Stack testing...------------------\n";
    Stack stack;
    push(stack, 10); 
    push(stack, 20);  
    push(stack, 30);
    stack.print();  // [30  20  10]
    cout << pop(stack) << endl;  // 30
    stack.print();  // [20  10]
    cout << peek(stack) << endl;  // 20
    stack.print();  // [20  10]

    cout << "\n----------Queue testing...------------------\n";
    Queue queue;
    init_queue(queue, 10);
    add_element(queue, 10);
    add_element(queue, 20);
    add_element(queue, 30);
    queue.print();  // [10  20  30]
    remove_element(queue);
    queue.print();  // [20  30]
    cout << get_front(queue) << endl;  // 20

    cout << "\n----------Deque testing...------------------\n";
    Deque deque;
    init_deque(deque, 10);
    add_front(deque, 10);
    add_front(deque, 20);
    add_rear(deque, 30);
    add_rear(deque, 40);
    deque.print();  // [20  10  30  40]
    remove_front(deque);
    remove_rear(deque);
    deque.print();  // [10  30]
    cout << get_front(deque) << endl;  // 10
    cout << get_rear(deque) << endl;  // 30
}