#include <iostream>
#include <memory>
#include <functional>
using namespace std;

const int SHRINK_THRESHOLD = 4;  // for shrinking threshold

// --------------------Base data structure--------------------------
struct Array {
    unique_ptr<int[]> arr_data;  // The array will have exclusive ownership
    int capacity;
    int size;

    bool is_empty() const {
        return size == 0;
    }

    void print() const {
        if (is_empty()) {
            cout << "Array is empty\n";
            return;
        }
        cout << "Array content: [";
        for (int i = 0; i < size; i++) {
            cout << arr_data[i] << " ";
        }
        cout << "]\n";
    }
};

// --------------------Array--------------------------
void init_array(Array& arr, int init_capacity = 10) {
    arr.arr_data = make_unique<int[]>(init_capacity);  // Initialize the unique_ptr correctly
    arr.capacity = init_capacity;
    arr.size = 0;
}

void resize_array(Array& arr, bool is_circular = false, int front = 0, int rear = 0) {
    auto new_arr_data = make_unique<int[]>(arr.capacity * 2);
    
    if (is_circular) {
        // Copy in circular manner from front to rear
        for (int i = 0; i < arr.size; i++) {
            new_arr_data[i] = arr.arr_data[(front + i) % arr.capacity];
        }
    } else {
        // Copy sequentially for non-circular arrays
        for (int i = 0; i < arr.size; i++) {
            new_arr_data[i] = arr.arr_data[i];
        }
    }

    arr.arr_data = move(new_arr_data);  // Move ownership to new array
    arr.capacity *= 2;
}

void shrink_array(Array& arr, bool is_circular = false, int front = 0, int rear = 0) {
    if (arr.size < arr.capacity / SHRINK_THRESHOLD) {
        // unique_ptr<int> new_arr_data
        auto new_arr_data = make_unique<int[]>(arr.capacity / 2);
        if(is_circular) {
            for(int i = 0; i < arr.size; i++) {
                new_arr_data[i] = arr.arr_data[(front + i) % arr.capacity];
            }
        }
        else{
            for(int i = 0; i < arr.size; i++) {
                new_arr_data[i] = arr.arr_data[i];
            }
        }
        
        arr.arr_data = move(new_arr_data);  // Move ownership
        arr.capacity /= 2;
        front = 0;
        rear = arr.size;
    }
}

void add_element(Array& arr, int element) {
    if (arr.size == arr.capacity) {
        resize_array(arr);
    }
    if(arr.arr_data)
        arr.arr_data[arr.size++] = element;  // Increment size after assigning
}

int remove_element(Array& arr) {
    if (arr.is_empty()) {
        throw out_of_range("Array is empty!\n");
    }
    return arr.arr_data[--arr.size];
}

void process_elements(Array& arr, const function<void(int)>& process_fn) {
    for(int i = 0; i < arr.size; i++) {
        int element = arr.arr_data[i];
        process_fn(element);
    }
}

// --------------------Stack--------------------------
struct Stack {
    Array arr;

    void print() const {
        if (arr.is_empty()) {
            cout << "Stack is empty!\n";
            return;
        }
        cout << "Stack content (top to bottom): [";
        for (int i = arr.size - 1; i >= 0; i--) {
            cout << arr.arr_data[i] << " ";
        }
        cout << "]\n";
    }
};

void init_stack(Stack& stack, int init_capacity = 10) {
    init_array(stack.arr, init_capacity);  // Initialize array for the stack
}

void push(Stack& stack, int element) {
    add_element(stack.arr, element);  // Reuse array's add_element
}

int pop(Stack& stack) {
    if (stack.arr.is_empty()) {
        throw out_of_range("Stack is empty!\n");
    }
    int value = stack.arr.arr_data[stack.arr.size - 1];  // Access last element
    stack.arr.size--;  // Decrement size after accessing
    shrink_array(stack.arr);  // Optionally shrink the array
    return value;
}

int peek(const Stack& stack) {
    if (stack.arr.is_empty()) {
        throw out_of_range("Stack is empty!\n");
    }
    return stack.arr.arr_data[stack.arr.size - 1];  // Peek at the last element
}

void process_elements(Stack& stack, const function<void(int)>& process_fn) {
    while(!stack.arr.is_empty()) {
        int element = pop(stack);
        process_fn(element);
    }
} 

// --------------------Queue--------------------------
struct Queue {
    Array arr;
    int front;
    int rear;

    void print() const {
        if(arr.is_empty()) {
            cout << "Queue is empty!\n";
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
    if(queue.arr.size == queue.arr.capacity){
        resize_array(queue.arr, true, queue.front, queue.rear);
        queue.front = 0;
        queue.rear = queue.arr.size;
    }
    queue.arr.arr_data[queue.rear] = element;
    queue.rear = (queue.rear + 1) % queue.arr.capacity;
    queue.arr.size++;
}

int remove_element(Queue& queue) {  
    if(queue.arr.is_empty())
        throw out_of_range("Queue is empty!\n");
    int value = queue.arr.arr_data[queue.front];
    queue.front = (queue.front + 1) % queue.arr.capacity;
    queue.arr.size --;
    shrink_array(queue.arr, true, queue.front, queue.rear);
    return value;
}

// function to process elements of the queue using a function pointer or lambda function
// to adhere open/closed principle
void process_elements(Queue& queue, const function<void(int)>& process_fn) {
        // (front + i) % arr.capacity
    for(int i = 0; i < queue.arr.size; i++) {
        int element = queue.arr.arr_data[(queue.front + i) % queue.arr.capacity];
        // cout << "element in processing is: " << element << endl;
        // queue.front = (queue.front + i) % queue.arr.capacity;
        process_fn(element);
    }
}

int get_front(const Queue& queue) {
    if(queue.arr.is_empty())
        throw out_of_range("Queue is already empty!\n");
    return queue.arr.arr_data[queue.front];
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
    shrink_array(deque.arr);
    return value;
}

int remove_rear(Deque& deque) {
    if(deque.arr.is_empty())
        throw out_of_range("Deque is empty!\n");
    deque.rear = (deque.rear - 1 + deque.arr.capacity) % deque.arr.capacity;
    int value = deque.arr.arr_data[deque.rear];
    deque.arr.size --;
    shrink_array(deque.arr);
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

void process_elements(Deque& deque, const function<void(int)>& process_fn) {
    while(!deque.arr.is_empty()) {
        int element = remove_front(deque);
        process_fn(element);
    }
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

        cout << arr.size << endl;  // 4
        cout << arr.capacity << endl;  // 6
        arr.print();

        process_elements(arr, [](int x) {cout << "Array element " << x << " is in processing..." << endl;});
    }

    {
        cout << "\n----------Stack testing...------------------\n";
        Stack stack;
        init_stack(stack);
        push(stack, 10); 
        push(stack, 20);  
        push(stack, 30);
        cout << stack.arr.size << endl << stack.arr.capacity << endl;
        stack.print();  // [30  20  10]
        cout << pop(stack) << endl;  // 30
        stack.print();  // [20  10]
        cout << peek(stack) << endl;  // 20
        stack.print();  // [20  10]
        process_elements(stack, [](int x) {cout << "Stack element " << x << " is in processing..." << endl;});
    }

    {
        cout << "\n----------Queue testing...------------------\n";
        Queue queue;
        init_queue(queue, 2);
        // cout << queue.arr.capacity << endl;  // 2
        add_element(queue, 10);
        // cout << queue.arr.capacity << endl;  // 2
        add_element(queue, 20);
        // cout << queue.arr.capacity << endl;  // 2
        add_element(queue, 30);
        // cout << queue.arr.capacity << endl;  // 4
        queue.print();  // [10  20  30]
        remove_element(queue);
        queue.print();  // [20  30]
        cout << get_front(queue) << endl;  // 20
        process_elements(queue, [](int x) {cout << "Queue element " << x << " is in processing..." << endl;});
    }

    {
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
        process_elements(deque, [](int x) {cout << "Deque element " << x << " is in processing..." << endl;});
    }
}