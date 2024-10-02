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
        for (int i = 0; i < size; i++) 
            cout << arr_data[i] << " ";
        
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
    
    if (is_circular) 
        // Copy in circular manner from front to rear
        for (int i = 0; i < arr.size; i++) 
            new_arr_data[i] = arr.arr_data[(front + i) % arr.capacity];
        
    else 
        // Copy sequentially for non-circular arrays
        for (int i = 0; i < arr.size; i++) 
            new_arr_data[i] = arr.arr_data[i];

    arr.arr_data = move(new_arr_data);  // Move ownership to new array
    arr.capacity *= 2;
}

void shrink_array(Array& arr, bool is_circular = false, int front = 0, int rear = 0) {
    if (arr.size < arr.capacity / SHRINK_THRESHOLD) {
        // unique_ptr<int> new_arr_data
        auto new_arr_data = make_unique<int[]>(arr.capacity / 2);
        if(is_circular) 
            for(int i = 0; i < arr.size; i++) 
                new_arr_data[i] = arr.arr_data[(front + i) % arr.capacity];

        else
            for(int i = 0; i < arr.size; i++) 
                new_arr_data[i] = arr.arr_data[i];
            
        
        arr.arr_data = move(new_arr_data);  // Move ownership
        arr.capacity /= 2;
        front = 0;
        rear = arr.size;
    }
}

int is_found(int element, int index){
    if(index < 0) 
        return -1;       
    
    else 
        return index;
}

void search_array(Array& arr, int element) {
    int idx;
    for(int i = 0; i < arr.size; i++) 
        if(arr.arr_data[i] == element) 
            idx = i;

    is_found(element, idx);
}

enum class array_operations {FRONT, REAR, AT_INDEX};
void add_element(Array& arr, int element, array_operations op, int index = -1) {
    if (arr.size == arr.capacity) 
        resize_array(arr);

    if(arr.arr_data)
        if(op == array_operations::REAR)
            arr.arr_data[arr.size] = element;  // Increment size after assigning
        else if (op == array_operations::FRONT){
            for(int i = arr.size; i > 0; i--) 
                arr.arr_data[i] = arr.arr_data[i - 1];
            
            arr.arr_data[0] = element;
        }
        else if (op == array_operations::AT_INDEX) {
            if(index < 0 || index > arr.size) 
                throw out_of_range("Index is out of range");

            arr.arr_data[index] = element;
        }
        arr.size++;
}

int remove_element(Array& arr, array_operations op) {
    if (arr.is_empty()) 
        throw out_of_range("Array is empty!\n");

    int value;
    if(op == array_operations::REAR)
        value = arr.arr_data[arr.size - 1];
    else if (op == array_operations::FRONT) {
        value = arr.arr_data[0];
        for(int i = 1; i < arr.size; i++) 
            arr.arr_data[i - 1] = arr.arr_data[i];
    }
    arr.size--;
    shrink_array(arr);
    return value;
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
        for (int i = arr.size - 1; i >= 0; i--) 
            cout << arr.arr_data[i] << " ";
        
        cout << "]\n";
    }
};

void init_stack(Stack& stack, int init_capacity = 10) {
    init_array(stack.arr, init_capacity);  // Initialize array for the stack
}

void search_stack(const Stack& stack, int element) {
    int idx;
    for(int i = stack.arr.size - 1; i >= 0; i--) {
        if(stack.arr.arr_data[i] == element)
            idx = i;
    }
    
    is_found(element, idx);
}

void push(Stack& stack, int element) {
    add_element(stack.arr, element, array_operations::REAR);  // Reuse array's add_element
}

int pop(Stack& stack) {
    if (stack.arr.is_empty()) 
        throw out_of_range("Stack is empty!\n");
    
    int value = stack.arr.arr_data[stack.arr.size - 1];  // Access last element
    stack.arr.size--;  // Decrement size after accessing
    shrink_array(stack.arr);  // Optionally shrink the array
    return value;
}

int peek(const Stack& stack) {
    if (stack.arr.is_empty()) 
        throw out_of_range("Stack is empty!\n");
    
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
        for(int i = 0; i < arr.size; i++) 
            cout << arr.arr_data[(front + i) % arr.capacity] << " ";
        
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
    
    for(int i = 1; i < queue.arr.size; i++) {
        int next_index = (queue.front + i) % queue.arr.capacity;
        int prev_index = (queue.front + i - 1) % queue.arr.capacity;
        queue.arr.arr_data[prev_index] = queue.arr.arr_data[next_index];
    }

    queue.rear = (queue.rear - 1 + queue.arr.capacity) % queue.arr.capacity;
    queue.arr.size--;

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

void search_queue(const Queue& queue, int element, int front) {
    int idx;
    for (int i = 0; i < queue.arr.size; i++) {  
        int index = (front + i) % queue.arr.capacity;  
        
        cout << "Checking index: " << index << " with value: " << queue.arr.arr_data[index] << endl;
        if (queue.arr.arr_data[index] == element) {
            idx = index;  
        }
    }
    is_found(element, idx);
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
        for(int i = 0; i < arr.size; i++) 
            cout << arr.arr_data[(front + i) % arr.capacity] << " ";
        
        cout << "]\n";
    }
};

void init_deque(Deque& deque, int init_capacity) {
    init_array(deque.arr);
    deque.front = 0;
    deque.rear = 0;
}

enum class deque_operations {FRONT, REAR};

void add_element(Deque& deque, int element, deque_operations op) {
    if(deque.arr.size == deque.arr.capacity)
        resize_array(deque.arr);

    else {
        if(op == deque_operations::FRONT) {
            deque.front = (deque.front - 1 + deque.arr.capacity) % deque.arr.capacity;
            deque.arr.arr_data[deque.front] = element;
        }
        else {
            deque.arr.arr_data[deque.rear] = element;
            deque.rear = (deque.rear + 1) % deque.arr.capacity;
        }
        deque.arr.size ++;
    }
}

int remove_element(Deque& deque, deque_operations op) {
    int value;
    if(deque.arr.is_empty())
        throw out_of_range("Deque is empty!\n");
    else{
        if(op == deque_operations::FRONT) {
            value = deque.arr.arr_data[deque.front];
            deque.front = (deque.front + 1) % deque.arr.capacity;
        }
        else {
            deque.rear = (deque.rear - 1 + deque.arr.capacity) % deque.arr.capacity;
            value = deque.arr.arr_data[deque.rear];
        }
        deque.arr.size --;
        shrink_array(deque.arr);
    }
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
        int element = remove_element(deque, deque_operations::FRONT);
        process_fn(element);
    }
}

void search_deque(const Array& arr, int element, int front) {
    int idx;
    for (int i = 0; i < arr.size; i++) {  
        int index = (front + i) % arr.capacity;  
        int normalized_index = i;

        // cout << "Checking index: " << index << " with value: " << arr.arr_data[index] << endl;
        if (arr.arr_data[index] == element) {
            idx = normalized_index;              
        }
    }
    is_found(element, idx);
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
        add_element(arr, 5, array_operations::REAR);
        add_element(arr, 6, array_operations::REAR);
        add_element(arr, 7, array_operations::REAR);
        add_element(arr, 8, array_operations::REAR);
        add_element(arr, 9, array_operations::REAR);
        add_element(arr, 10, array_operations::REAR);
        arr.print();
        
        add_element(arr, 11, array_operations::FRONT);
        cout << arr.size << endl;  // 6
        cout << arr.capacity << endl;  // 6
        arr.print();  // [5 6 7 8 9 10 ]

        remove_element(arr, array_operations::REAR);
        remove_element(arr, array_operations::REAR);
        remove_element(arr, array_operations::FRONT);
        cout << arr.size << endl;  // 4
        arr.print();  // [5 6 7 8 ]

        cout << arr.size << endl;  // 4
        cout << arr.capacity << endl;  // 6
        arr.print();

        search_array(arr, 7);

        process_elements(arr, [](int x) {cout << "Array element " << x << " is in processing..." << endl;});
    }

    {
        cout << "\n----------Stack testing...------------------\n";
        Stack stack;
        init_stack(stack);
        push(stack, 10); 
        push(stack, 20);  
        push(stack, 30);
        cout << "Stack size: " << stack.arr.size << ", and its capacity: " << stack.arr.capacity << endl;
        stack.print();  // [30  20  10]
        cout << pop(stack) << endl;  // 30
        stack.print();  // [20  10]
        cout << peek(stack) << endl;  // 20
        stack.print();  // [20  10]

        search_stack(stack, 10);

        process_elements(stack, [](int x) {cout << "Stack element " << x << " is in processing..." << endl;});
    }

    {
        cout << "\n----------Queue testing...------------------\n";
        Queue queue;
        init_queue(queue, 2);
        add_element(queue, 10);
        add_element(queue, 20);
        
        cout << "capacity before resizing array: " << queue.arr.capacity << endl;  // 2
        add_element(queue, 30);
        cout << "capacity after resizing array: " << queue.arr.capacity << endl;  // 4
        queue.print();  // [10  20  30]
        
        remove_element(queue);
        queue.print();  // [20  30]

        cout << get_front(queue) << endl;  // 20
        
        search_queue(queue, 20, queue.front);

        process_elements(queue, [](int x) {cout << "Queue element " << x << " is in processing..." << endl;});
    }

    {
        cout << "\n----------Deque testing...------------------\n";
        Deque deque;
        init_deque(deque, 10);
        cout << deque.front << endl;  // 0
        add_element(deque, 10, deque_operations::FRONT);  // 10
        cout << deque.front << endl;  // 9
        add_element(deque, 20, deque_operations::FRONT);  // 20 10
        cout << deque.front << endl;  // 8
        add_element(deque, 30, deque_operations::REAR);  // 20 10 30
        cout << deque.front << endl;  // 8
        add_element(deque, 40, deque_operations::REAR);  // 20 10 30 40
        cout << deque.front << endl;  // 8
        deque.print();  // [20  10  30  40]
        cout << deque.front << endl;  // 8
        remove_element(deque, deque_operations::FRONT);  // 10 30 40
        cout << deque.front << endl;  // 9
        remove_element(deque, deque_operations::REAR);  // 10 30 
        cout << deque.front << endl;  // 9
        cout << deque.rear << endl;  // 1
        deque.print();  // [10  30]
        
        cout << deque.front << endl; // 9
        cout << get_front(deque) << endl;  // 10
        cout << deque.front << endl; // 9
        cout << deque.rear << endl;  // 1
        cout << get_rear(deque) << endl;  // 30
        cout << deque.front << endl;  // 9
        

        search_deque(deque.arr, 30, deque.front);

        process_elements(deque, [](int x) {cout << "Deque element " << x << " is in processing..." << endl;});
    }
}