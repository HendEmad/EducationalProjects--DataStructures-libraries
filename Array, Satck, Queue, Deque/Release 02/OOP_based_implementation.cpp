#include <iostream>
#include <memory>
#include <functional>
using namespace std;

const int SHRINK_THRESHOLD = 4;  // for shrinking threshold

// --------------------Array--------------------------
class Array {
protected:
    unique_ptr<int[]> arr_data;  // The array will have exclusive ownership
    int capacity;
    int size;

    void resize_array(bool is_circular = false, int front = 0, int rear = 0);
    void shrink_array(bool is_circular = false, int front = 0, int rear = 0);

public:
    int get_size() const;
    int get_capacity() const;
    bool is_empty() const;
    virtual void print() const = 0;
    virtual void add_element(int element);
    virtual int remove_element();
    virtual void process_elements(const function<void(int)>& process_fn) = 0;
    Array(int init_capacity = 10, int size = 0);
};

Array::Array(int init_capacity, int size) : capacity(init_capacity) , size(0) {
    arr_data = make_unique<int[]> (init_capacity);
}

// A function to resize the data structure if the size is greater than the capacity
void Array::resize_array(bool is_circular, int front, int rear) {
    auto new_arr_data = make_unique<int[]>(capacity * 2);
        
    if (is_circular) {
        for (int i = 0; i < size; i++) {
            new_arr_data[i] = arr_data[(front + i) % capacity];
        }
    } else {
        for (int i = 0; i < size; i++) {
            new_arr_data[i] = arr_data[i];
        }
    }

    arr_data = move(new_arr_data);  
    capacity *= 2;
}

// A function to shrink the data structure by half if its size less than 1/4 its capacity
void Array::shrink_array(bool is_circular, int front, int rear) {
    if (size < capacity / SHRINK_THRESHOLD) {
        auto new_arr_data = make_unique<int[]>(capacity / 2);
        if(is_circular) {
            for(int i = 0; i < size; i++) {
                new_arr_data[i] = arr_data[(front + i) % capacity];
            }
        }
        else{
            for(int i = 0; i < size; i++) {
                new_arr_data[i] = arr_data[i];
            }
        }
            
        arr_data = move(new_arr_data);  
        capacity /= 2;
        front = 0;
        rear = size;
    }
}

int Array::get_size() const {
    return size;
}

int Array::get_capacity() const {
    return capacity;
}

bool Array::is_empty() const {
    return size == 0;
}

void Array::print() const {
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

void Array::add_element(int element) {
    if (size == capacity) 
            resize_array();

    if(arr_data)
        arr_data[size++] = element;
}

int Array::remove_element() {
    if (is_empty()) 
        throw out_of_range("Array is empty!\n");
    
    return arr_data[--size];   
}

// A function if we need to perform operations on the data structure elements, by passing a function.
void Array::process_elements(const function<void(int)>& process_fn) {
    for(int i = 0; i < size; i++) {
        int element = arr_data[i];
        process_fn(element);
    }
}

// --------------------Stack--------------------------
class Stack : public Array {
public:
    Stack(int init_capacity = 10);
    void add_element(int element) override;
    int remove_element();
    int peek();
    void print() const override;
    void process_elements(const function<void(int)>& process_fn) override;
};

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

// --------------------Queue--------------------------
class Queue : public Array {
    int front, rear;
public:
    void print() const override;
    Queue(int init_capacity = 10, int front = 0, int rear = 0);
    void add_element(int element) override;
    int remove_element() override;
    int get_front();
    void process_elements(const function<void(int)>& provess_fn) override;
};

Queue::Queue(int init_capacity, int front, int rear) : front(0), rear(0) {}

void Queue::add_element(int element) {
    if(size == capacity){
        resize_array(true, front, rear);
        front = 0;
        rear = size;
    }
    arr_data[rear] = element;
    rear = (rear + 1) % capacity;
    size++;
}

int Queue::remove_element() {
    if(is_empty())
        throw out_of_range("Queue is empty!\n");
    
    int value = arr_data[front];
    front = (front + 1) % capacity;
    size --;
    shrink_array(true, front, rear);
    return value;
}

void Queue::process_elements(const function<void(int)>& process_fn) {
    for(int i = 0; i < size; i++) {
        int element = arr_data[(front + i) % capacity];
        process_fn(element);
    }
}

int Queue::get_front() {
    if(is_empty())
        throw out_of_range("Queue is already empty!\n");
    
    return arr_data[front];
}

void Queue::print() const {
    if(is_empty()) {
        cout << "Queue is empty!\n";
        return;
    }
    cout << "Queue content (front to rear): [";
    for(int i = 0; i < size; i++) {
        cout << arr_data[(front + i) % capacity] << " ";
    }
    cout << "]\n";
}

// --------------------deque--------------------------
enum class deque_operations {FRONT, REAR};

class Deque : public Array {
    int front, rear;
public:
    Deque(int init_capacity = 10, int front = 0, int rear = 0);
    void add_element(int element) override;  // overriding
    int remove_element() override;  // overriding
    void add_element(int element, deque_operations op);  // overloading
    int remove_element(deque_operations op);  // overloading
    int get_rear();
    void print() const override;
    int get_front();
    void process_elements(const function<void(int)>& process_fn) override;
};

Deque::Deque(int init_capacity, int front, int rear) : Array(init_capacity), front(0), rear(0) {}

void Deque::print() const {
    if(is_empty()) {
        cout << "Deque is already empty!\n";
        return;
    }
    cout << "Deque content (front to rear): [";
    for(int i = 0; i < size; i++) {
        cout << arr_data[(front + i) % capacity] << " ";
    }
    cout << "]\n";
}

void Deque::add_element(int element) {
    return add_element(element, deque_operations::FRONT);
}

void Deque::add_element(int element, deque_operations op) {
    if(size == capacity) {
        resize_array(true, front, rear);
        front = 0;
        rear = size;
    }
    // add_front()
    if(op == deque_operations::FRONT) {
        front = (front - 1 + capacity) % capacity;
        arr_data[front] = element;
    }
    // add_rear() 
    else {
        arr_data[rear] = element;
        rear = (rear + 1) % capacity;
    }
    size++;
}

int Deque::remove_element() {
    return remove_element(deque_operations::FRONT);
}

int Deque::remove_element (deque_operations op) {
    if(is_empty())
        throw out_of_range("Deque is already empty");
    
    int value;
    if(op == deque_operations::FRONT) {
        value = arr_data[front];
        front = (front + 1) % capacity;
    }
    else {
        rear = (rear - 1 + capacity) % capacity;
        value = arr_data[rear];
    }
    size--;
    shrink_array(true, front, rear);
    return value;
}

int Deque::get_front() {
    if(is_empty())
        throw out_of_range("Deque is already empty!\n");
        
    return arr_data[front];
}

int Deque::get_rear() {
    if(is_empty())
        throw out_of_range("Deque is already empty!\n");
        
    return arr_data[(rear - 1 + capacity) % capacity];
}

void Deque::process_elements(const function<void(int)>& process_fn) {
    while(!is_empty()) {
        int element = remove_element(deque_operations::FRONT);
        process_fn(element);
    }
}

int main() {
    // --------------------Stack Testing--------------------------
    unique_ptr<Array> stack = make_unique<Stack> ();
    cout << "Size: " << stack ->get_size() << ", and capacity: " << stack ->get_capacity() << endl;
    stack ->add_element(10);
    stack ->add_element(20);
    stack ->add_element(30);
    stack ->print();
    stack ->remove_element();
    stack ->print();
    Stack* s_ptr = dynamic_cast<Stack*> (stack.get());
    if(s_ptr) cout << s_ptr ->peek() << endl;
    stack->process_elements([](int x){cout << "Stack element " << x << " is in processing..." << endl;});

    // --------------------Queue testing--------------------------
    unique_ptr<Array> queue = make_unique<Queue> (2);
    queue ->add_element(10);
    queue ->add_element(20);
    queue ->add_element(30);
    queue ->print();
    queue ->remove_element();
    queue ->print();
    
    Queue* q_ptr = dynamic_cast<Queue*>(queue.get());
    if(q_ptr) cout << q_ptr ->get_front() << endl;
    queue ->process_elements([](int x) {cout << "Queue element " << x << " is in processing..." << endl;});

    // --------------------Deque testing--------------------------
    unique_ptr<Array> deque = make_unique<Deque> (2);
    Deque* d_ptr = dynamic_cast<Deque*> (deque.get());
    if(d_ptr) {
        d_ptr ->add_element(10, deque_operations::FRONT);
        d_ptr ->add_element(20, deque_operations::FRONT);
        d_ptr ->add_element(30, deque_operations::REAR);
        d_ptr ->add_element(40, deque_operations::REAR);
    }
    deque ->print();
    if(d_ptr) {
        d_ptr ->remove_element(deque_operations::FRONT);
        d_ptr ->remove_element(deque_operations::REAR);
    }
    deque ->print();
    if(d_ptr) {
        cout << d_ptr ->get_front() << endl;
        cout << d_ptr ->get_rear() << endl;
    }
    deque ->process_elements([](int x) {cout << "Deque element " << x << " is in processing..." << endl;});
}