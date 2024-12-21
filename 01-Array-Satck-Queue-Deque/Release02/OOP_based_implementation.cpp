#include <iostream>
#include <memory>
#include <functional>
using namespace std;

const int SHRINK_THRESHOLD = 4;  // for shrinking threshold
enum class data_structures {ARRAY, STACK, QUEUE, DEQUE};

class AbstractDS {
public:
    virtual void add_element(int element) = 0;
    virtual int remove_element() = 0;
    virtual void print() const = 0;
    virtual void process_elements(const function<void(int)>& process_fn) = 0;
    virtual ~AbstractDS() = default;
    virtual void search(int element, int front = -1) = 0;
};

class Array{
protected:
    unique_ptr<int[]> arr_data;
    int capacity;
    int size;
public:
    Array(int init_capacity = 10);
    void resize_array(bool is_circular = false, int front = 0, int rear = 0);
    void shrink_array(bool is_circular = false, int front = 0, int rear = 0);
    void is_found(int element, int index);
    void search(int element, int front = -1);
    void process_elements(const function<void(int)>& process_fn);
    int remove_element();
    void add_element(int element);
    void print() const;
    int get_size() const;
    int get_capacity() const;
    bool is_empty() const;
    int get_element(int idnex) const;
    const auto get_arr_data() const;
    int decrease_size_1();
    int increase_size_1();
};

Array::Array(int init_capacity) : capacity(init_capacity), size(0) {
    arr_data = make_unique<int[]>(init_capacity);
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

int Array::decrease_size_1() {
    return size--;
}

int Array::increase_size_1() {
    return size++;
}

void Array::is_found(int element, int index) {
    if(index < 0)
        cout << "Element not found..\n";
    else
        cout << "The element " << element << " is found at index " << index << endl;
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
    
    int value = arr_data[size - 1];
    decrease_size_1();
    shrink_array();
    return value;  
}

// A function if we need to perform operations on the data structure elements, by passing a function.
void Array::process_elements(const function<void(int)>& process_fn) {
    for(int i = 0; i < size; i++) {
        int element = arr_data[i];
        process_fn(element);
    }
}

void Array::search(int element, int front) {
    int idx;
    for(int i = 0; i < size; i++) 
        if(arr_data[i] == element){
            idx = i;
            break;
        }
    is_found(element, idx);
}

int Array::get_element(int index) const {
    return arr_data[index];
}

const auto Array::get_arr_data() const {
    return arr_data.get();
}
//-----------------------------Stack--------------------
class Stack : public AbstractDS {
    Array array;
public:
    Stack(int init_capacity = 10);
    void add_element(int element) override;
    int remove_element() override;
    int peek();
    void print() const override;
    void process_elements(const function<void(int)>& process_fn) override;   
    void search(int element, int front = -1) override;
};

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

void Stack::print() const {
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

//--------------------------Queue---------------------------
class Queue : public AbstractDS {
    Array array;
    int front, rear;
public:
    Queue(int init_capacity = 10);
    void add_element(int element) override;
    int remove_element() override;
    int get_front() const;
    void process_elements(const function<void(int)>& process_fn) override;
    void print() const override;
    int get_front_idx();
    void search(int element, int front = -1) override;
};

Queue::Queue(int init_capacity) : array(init_capacity), front(0), rear(0) {}

void Queue::add_element(int element){
    if(array.get_size() == array.get_capacity()) {
        array.resize_array(true, front, rear);
        front = 0;
        rear = array.get_size();
    }
    array.get_arr_data()[rear] = element;
    rear = (rear + 1) % array.get_capacity();
    array.increase_size_1();
}

int Queue::remove_element() {
    if(array.is_empty())
        throw out_of_range("Queue is empty\n");
    
    int value = array.get_arr_data()[front];

    for(int i = 1; i < array.get_size(); i++) {
        int next_index = (front + i) % array.get_capacity();
        int prev_index = (front + i - 1) % array.get_capacity();
        array.get_arr_data()[prev_index] = array.get_arr_data()[next_index];
    }

    rear = (rear - 1 + array.get_capacity()) % array.get_capacity();
    array.decrease_size_1();
    array.shrink_array(true, front, rear);
    return value;
}

void Queue::process_elements(const function<void(int)>& process_fn) {
    for(int i = 0; i < array.get_size(); i++) {
        int element = array.get_arr_data()[(front + i) % array.get_capacity()];
        process_fn(element);
    }
}

int Queue::get_front() const{
    if(array.is_empty()) 
        throw out_of_range("Queue is empty\n");
    
    return array.get_arr_data()[front];
}

void Queue::print() const {
    if(array.is_empty()) {
        cout << "Queue is empty\n";
        return;
    }
    cout << "Queue content (from front to rear): [";
    for(int i = 0; i < array.get_size(); i++) {
        cout << array.get_arr_data()[(front + i) % array.get_capacity()] << " ";
    }
    cout << "]\n";
}

void Queue::search(int element, int front) {
    int idx = -1;
    for(int i = 0; i < array.get_size(); i++) {
        int index = (front + i) % array.get_capacity();

        cout << "Checking index: " << index << " with value: " << array.get_arr_data()[index] << endl;
        if(array.get_arr_data()[index] == element) {
            idx = index;
            break;
        }
    }
    array.is_found(element, idx);
}

int Queue::get_front_idx() {
    return front;
}

//-----------------------Deque-------------------------
enum class deque_operations {FRONT, REAR};

class Deque : public AbstractDS {
    Array array;
    int front, rear;
public:
    Deque(int init_capacity = 10);
    void add_element(int element) override;
    void add_element(int elemeent, deque_operations op);
    int remove_element() override;
    int remove_element(deque_operations op);
    void print() const override;
    int get_front() const;
    int get_rear() const;
    void process_elements(const function<void(int)>& process_fn) override;
    int get_front_idx() const;
    void search(int element, int front = -1) override;
};

Deque::Deque(int init_capacity) : array(init_capacity), front(0), rear(0) {}

void Deque::add_element(int element, deque_operations op) {
    if(array.get_size() == array.get_capacity()) {
        array.resize_array(true, front, rear);
        front = 0; 
        rear = array.get_size();
    }
    // add_front
    if(op == deque_operations::FRONT) {
        front = (front - 1 + array.get_capacity()) % array.get_capacity();
        array.get_arr_data()[front] = element;
    }
    // add_rear
    else {
        array.get_arr_data()[rear] = element;
        rear = (rear + 1) % array.get_capacity();
    }
    array.increase_size_1();
}

void Deque::add_element(int element) {
    return add_element(element, deque_operations::FRONT);
}

int Deque::remove_element(deque_operations op) {
    if(array.is_empty())
        throw out_of_range("Deque is empty\n");
    
    int value;
    if(op == deque_operations::FRONT) {
        value = array.get_arr_data()[front];
        front = (front + 1) % array.get_capacity();
    }
    else {
        rear = (rear - 1 + array.get_capacity()) % array.get_capacity();
        value = array.get_arr_data()[rear];
    }
    array.decrease_size_1();
    array.shrink_array(true, front, rear);
    return value;
}

int Deque::remove_element() {
    return remove_element(deque_operations::FRONT);
}

void Deque::print() const{
    if(array.is_empty()) {
        cout << "Deque is already empty!\n";
        return;
    }
    cout << "Deque content (front to rear): [";
    for(int i = 0; i < array.get_size(); i++) {
        cout << array.get_arr_data()[(front + i) % array.get_capacity()] << " ";
    }
    cout << "]\n";   
}

int Deque::get_front() const {
    if(array.is_empty()) 
        throw out_of_range ("Deque is empty\n");
    
    return array.get_arr_data()[front];
}

int Deque::get_rear() const {
    if(array.is_empty()) 
        throw out_of_range ("Deque is empty\n");
    
    return array.get_arr_data()[(rear - 1 + array.get_capacity()) % array.get_capacity()];   
}

void Deque::process_elements(const function<void(int)>& process_fn) {
    for(int i = 0; i < array.get_size(); i++) {
        cout << "The element of index " << i << endl;
        int element = array.get_arr_data()[(front + i) % array.get_capacity()];
        process_fn(element);
    }
}

int Deque::get_front_idx() const {
    return front;
}

void Deque::search(int element, int front) {
    int idx = -1;
    for (int i = 0; i < array.get_size() && !array.is_empty(); i++) {  
        // int index = i;  
        int index = (this->front + i) % array.get_capacity();
        // int normalized_index = i;

        cout << "Checking index: " << i << " with value: " << array.get_arr_data()[index] << endl;
        if (array.get_arr_data()[index] == element) {
            // idx = normalized_index;  
            idx = i;    
            break;
        }        
    }

    array.is_found(element, idx);    
}

int main() {
    // -----------------Stack testing---------------------
    cout << "----------------------stack testing-------------------\n";
    unique_ptr<AbstractDS> stack = make_unique<Stack> (2); 
    stack->add_element(10);
    stack->add_element(20);
    stack->add_element(30);
    stack->add_element(40);
    stack->print();

    stack->remove_element();
    stack->print();

    stack->search(20);

    // -----------------Queue testing---------------------
    cout << "----------------------Queue testing-------------------\n";
    unique_ptr<AbstractDS> queue = make_unique<Queue> (2); 
    queue->add_element(10);
    queue->add_element(20);
    queue->add_element(30);
    queue->add_element(40);
    queue->print();

    queue->remove_element();
    queue->print();

    Queue* q_ptr = dynamic_cast<Queue*> (queue.get());
    if(q_ptr) cout << q_ptr -> get_front_idx() << endl;
    queue->search(20, q_ptr ->get_front_idx());

    // -----------------Deque testing---------------------
    cout << "----------------------Deque testing-------------------\n";
    unique_ptr<AbstractDS> deque = make_unique<Deque> (2); 
    Deque* d_ptr = dynamic_cast<Deque*> (deque.get());
    d_ptr->add_element(10, deque_operations::REAR);
    deque->add_element(20);
    d_ptr->add_element(30, deque_operations::REAR);
    deque->add_element(40);
    if(d_ptr) cout << d_ptr -> get_front_idx() << endl;
    deque->print();

    deque->remove_element();
    if(d_ptr) cout << d_ptr -> get_front_idx() << endl;
    deque->print();

    if(d_ptr) cout << d_ptr -> get_front_idx() << endl;
    deque->search(10, d_ptr ->get_front_idx());
}