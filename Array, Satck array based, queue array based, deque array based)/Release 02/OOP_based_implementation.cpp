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

    void resize_array(bool is_circular = false, int front = 0, int rear = 0) {
        auto new_arr_data = make_unique<int[]>(capacity * 2);
        
        if (is_circular) {
            // Copy in circular manner from front to rear
            for (int i = 0; i < size; i++) {
                new_arr_data[i] = arr_data[(front + i) % capacity];
            }
        } else {
            // Copy sequentially for non-circular arrays
            for (int i = 0; i < size; i++) {
                new_arr_data[i] = arr_data[i];
            }
        }

        arr_data = move(new_arr_data);  // Move ownership to new array
        capacity *= 2;
    }

    void shrink_array(bool is_circular = false, int front = 0, int rear = 0) {
        if (size < capacity / SHRINK_THRESHOLD) {
            // unique_ptr<int> new_arr_data
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
            
            arr_data = move(new_arr_data);  // Move ownership
            capacity /= 2;
            front = 0;
            rear = size;
        }
    }
public:
    Array(int init_capacity = 10) : capacity(init_capacity), size(0) {
        arr_data = make_unique<int[]> (init_capacity);
    }

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

    void add_element(int element) {
        if (size == capacity) {
            resize_array();
        }
        if(arr_data)
            arr_data[size++] = element;  // Increment size after assigning
    }

        int remove_element() {
        if (is_empty()) {
            throw out_of_range("Array is empty!\n");
        }
        return arr_data[--size];
    }

    void process_elements(const function<void(int)>& process_fn) {
        for(int i = 0; i < size; i++) {
            int element = arr_data[i];
            process_fn(element);
        }
    }
};

// --------------------Stack--------------------------
class Stack : public Array {
public:
    Stack(int init_capacity = 10) : Array(init_capacity) {}

        void push(int element) {
        add_element(element);  // Reuse array's add_element
    }

    int pop() {
        if (is_empty()) {
            throw out_of_range("Stack is empty!\n");
        }
        int value = arr_data[size - 1];  // Access last element
        size--;  // Decrement size after accessing
        shrink_array();  // Optionally shrink the array
        return value;
    }

    int peek() {
        if (is_empty()) {
            throw out_of_range("Stack is empty!\n");
        }
        return arr_data[size - 1];  // Peek at the last element
    }

    void process_elements(const function<void(int)>& process_fn) {
        while(!is_empty()) {
            int element = pop();
            process_fn(element);
        }
    } 
};

// --------------------Queue--------------------------
class Queue : public Array {
    int front, rear;
public:
    Queue(int init_capacity = 10) : Array(init_capacity), front(0), rear(0) {}

    void print() const {
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

    void add_element(int element) {
        if(size == capacity){
            resize_array(true, front, rear);
            front = 0;
            rear = size;
        }
        arr_data[rear] = element;
        rear = (rear + 1) % capacity;
        size++;
    }

    int remove_element() {  
        if(is_empty())
            throw out_of_range("Queue is empty!\n");
        int value = arr_data[front];
        front = (front + 1) % capacity;
        size --;
        shrink_array(true, front, rear);
        return value;
    }

    void process_elements(const function<void(int)>& process_fn) {
        for(int i = 0; i < size; i++) {
            int element = arr_data[(front + i) % capacity];
            process_fn(element);
        }
    }

    int get_front() {
        if(is_empty())
            throw out_of_range("Queue is already empty!\n");
        return arr_data[front];
    }
};

// --------------------Deque--------------------------
class Deque : public Array {
    int front, rear;

public:
    Deque(int init_capacity = 10) : Array(init_capacity), front(0), rear(0) {}

    void print() const {
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

    void add_front(int element) {
        if(size == capacity)
            resize_array();
        front = (front - 1 + capacity) % capacity;
        arr_data[front] = element;
        size ++;
    }

    void add_rear(int element) {
        if(size == capacity)
            resize_array();
        arr_data[rear] = element;
        rear = (rear + 1) % capacity;
        size ++;
    }

    int remove_front() {
        if(is_empty())
            throw out_of_range("Deque is already empty!\n");
        int value = arr_data[front];
        front = (front + 1) % capacity;
        size --;
        shrink_array();
        return value;
    }

    int remove_rear() {
        if(is_empty())
            throw out_of_range("Deque is empty!\n");
        rear = (rear - 1 + capacity) % capacity;
        int value = arr_data[rear];
        size --;
        shrink_array();
        return value;
    }

    int get_front() {
        if(is_empty())
            throw out_of_range("Deque is already empty!\n");
        return arr_data[front];
    }

    int get_rear() {
        if(is_empty())
            throw out_of_range("Deque is already empty!\n");
        return arr_data[(rear - 1 + capacity) % capacity];
    }

    void process_elements(const function<void(int)>& process_fn) {
        while(!is_empty()) {
            int element = remove_front();
            process_fn(element);
        }
    }
};

int main() {
    unique_ptr<Array> stack = make_unique<Stack> ();
    unique_ptr<Array> queue = make_unique<Queue> ();
    unique_ptr<Array> deque = make_unique<Deque> ();
}