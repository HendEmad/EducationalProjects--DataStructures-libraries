#include <iostream>
#include <functional>
#include <memory>
#include <algorithm>
#include <utility>

// declarations
struct ForwardNode;
struct DoublyNode;
struct CircularNode;

// =============================================== //
// ForwardList - Singly Linked List Implementation
// =============================================== //
struct ForwardNode {
    int data;
    std::unique_ptr<ForwardNode> next;
    ForwardNode(int value) : data(value), next(nullptr) {}
};

struct ForwardList {
    std::unique_ptr<ForwardNode> head;
    size_t size;
};

// functions prototype
ForwardList* createForwardList();
void forwardListPushFront(ForwardList* list, int data);
void forwardListPopFront(ForwardList* list);
void forwardListClear(ForwardList* list);
void forwardListInsertAfter(ForwardList* list, ForwardNode* node, int data);
void forwardListRemoveAfter(ForwardList* list, ForwardNode* node);
void forwardListDisplay(const ForwardList* list);
void forwardListProcess(ForwardList* list, const std::function<void(int&)>& func);

// =============================================== //
// DoublyLinkedList - Doubly Linked List Implementation
// =============================================== //
struct DoublyNode {
    int data;
    std::unique_ptr<DoublyNode> next;
    DoublyNode* prev = nullptr;
    DoublyNode(int value): data(value), next(nullptr), prev(nullptr) {}
};

struct DoublyLinkedList {
    std::unique_ptr<DoublyNode> head;
    DoublyNode* tail;
    size_t size;
};

// functions prototype
DoublyLinkedList* createDoublyLinkedList();
void doublyListPushFront(DoublyLinkedList* list, int data);
void doublyListPushBack(DoublyLinkedList* list, int data);
void doublyListPopFront(DoublyLinkedList* list);
void doublyListPopBack(DoublyLinkedList* list);
void doublyListInsert(DoublyLinkedList* list, size_t index, int data);
void doublyListErase(DoublyLinkedList* list, size_t index);
void doublyListClear(DoublyLinkedList* list);
void doublyListDisplay(const DoublyLinkedList* list);
void doublyListProcess(DoublyLinkedList* list, const std::function<void(int&)>& func);

// =============================================== //
// CircularLinkedList - Circular Singly Linked List Implementation
// =============================================== //
struct CircularNode {
    int data;
    std::unique_ptr<CircularNode> next;
    CircularNode(int value): data(value), next(nullptr) {}
};

struct CircularLinkedList {
    std::unique_ptr<CircularNode> head;
    CircularNode* tail;
    size_t size;
};

// functions prototype
CircularLinkedList* createCircularLinkedList();
void circularListPushFront(CircularLinkedList* list, int data);
void circularListPushBack(CircularLinkedList* list, int data);
void circularListPopFront(CircularLinkedList* list);
void circularListPopBack(CircularLinkedList* list);
void circularListClear(CircularLinkedList* list);
void circularListDisplay(const CircularLinkedList* list);
void circularListProcess(CircularLinkedList* list, const std::function<void (int&)>& func);

// =============================================== //
// Implementations
// =============================================== //

// --------------------------------- ForwardList functions--------------------------------- 
// A function to create dynamic single LinkedList
ForwardList* createForwardList() {
    return new ForwardList{nullptr, 0};
}

// A function to add a node to the front of the forward list
void forwardListPushFront(ForwardList* list, int data) {
    auto newNode = std::make_unique<ForwardNode> (data);
    newNode -> next = std::move(list -> head);
    list -> head = move(newNode);
    list -> size ++;
}

// A function to delete a node from the forward list front side
void forwardListPopFront(ForwardList* list) {
    if(list -> head) {
        list ->head = std::move(list ->head ->next);
        list ->size --;
    }
}

// A function to clear the whole forward list nodes
void forwardListClear(ForwardList* list) {
    list ->head.reset();  // sets the unique pointer to nullptr
    list ->size = 0;
}

// A function to add a node after a particular node
void forwardListInsertAfter(ForwardList* list, ForwardNode* node, int data) {
    if(list == nullptr || node == nullptr) {
        std::cout << "Error: Invalid list or node\n";
        return;
    }

    auto newNode = std::make_unique<ForwardNode>(data);
    newNode -> next = std::move(node ->next);
    node ->next = std::move(newNode);    
}

// A function to delete a node after a particular node
void forwardListRemoveAfter(ForwardList* list, ForwardNode* node) {
    if(list == nullptr || node == nullptr) {
        std::cout << "Error: Invalid list or node, or no node to remove\n";
        return;
    }

    node -> next = std::move(node ->next ->next);
}

// A function to print all the data of the forward list
void forwardListDisplay(const ForwardList* list) {
    if(list == nullptr) {
        std::cout << "Error: Invalid list\n";
        return;
    }

    ForwardNode* curr = list ->head.get();
    while(curr) {
        std::cout << curr ->data << " -> ";
        curr = curr -> next.get();  // traversal requires row pointer while keeping the ownership to the unique pointer
    }
    std::cout << "Null\n";
}

// A function to enable the usage of lambda functions or high order functions
void forwardListProcess(ForwardList* list, const std::function<void(int&)>& func) {
    ForwardNode* curr = list ->head.get();
    while(curr) {
        func(curr ->data);
        curr = curr ->next.get();
    }
}

// --------------------------------- DoublyLinkedList functions--------------------------------- 
// A function to create dynamic doubly LinkedList
DoublyLinkedList* createDoublyLinkedList() {
    return new DoublyLinkedList{nullptr, nullptr, 0};
}

// A function to add a node to the front of the doubly list
void doublyListPushFront(DoublyLinkedList* list, int data) {
    auto newNode = std::make_unique<DoublyNode>(data);
    if(list -> head) {
        newNode -> next = std::move(list ->head);
        newNode ->next ->prev = newNode.get();
    }
    else {
        list ->tail = newNode.get();
    }
    list ->head = std::move(newNode);
    list ->size ++;
}

// A function to add a node to the back of the doubly list
void doublyListPushBack(DoublyLinkedList* list, int data) {
    auto newNode = std::make_unique<DoublyNode>(data);
    newNode ->prev = list ->tail;
    if(list ->tail) {
        list ->tail ->next = std::move(newNode);
    }
    else {
        list ->head = std::move(newNode);
    }
    list ->tail = list ->tail ->next.get();
    list ->size ++;
}

// A function to delete a node from the doubly list front side
void doublyListPopFront(DoublyLinkedList* list) {
    if(list ->head) {
        list ->head = std::move(list ->head ->next);
        if(list ->head) {
            list ->head ->prev = nullptr;
        }
        else {
            list ->tail = nullptr;
        }
        list ->size --;
    }
}

// A function to delete a node from the doubly list back side
void doublyListPopBack(DoublyLinkedList* list) {
    if(list ->tail) {
        if(list ->tail ->prev) {
            list ->tail = list ->tail ->prev;
            list ->tail ->next.reset();
        } 
        else {
            list ->head.reset();
            list ->tail = nullptr;
        }
        list ->size --;
    }
}

void debugNode(DoublyNode* node, const std::string& label) {
    if (node) {
        std::cout << label << ": data = " << node->data
                  << ", prev = " << (node->prev ? node->prev->data : -1)
                  << ", next = " << (node->next ? node->next->data : -1) << "\n";
    } else {
        std::cout << label << ": nullptr\n";
    }
}


// A function to add a node after a particular index
void doublyListInsert(DoublyLinkedList* list, size_t index, int data) {
    if(index > list ->size) {
        throw std::out_of_range("index out of bounds");
    }
    if(index == 0) {
        doublyListPushFront(list, data);
        return;
    }
    if(index == list ->size) {
        doublyListPushBack(list, data);
        return;
    }
    
    auto newNode = std::make_unique<DoublyNode>(data);
    DoublyNode* curr = list ->head.get();
    for(size_t i = 0; i < index - 1; i++) {
        curr = curr ->next.get();
    }

    newNode ->next = std::move(curr ->next);
    newNode ->prev = curr;
    if(newNode ->next) {
        newNode ->next ->prev = newNode.get();
    }
    curr ->next = std::move(newNode);
    list ->size ++;
}

void doublyListErase(DoublyLinkedList* list, size_t index) {
    if (!list || index >= list->size) {
        throw std::out_of_range("Index out of bounds");
    }

    DoublyNode* curr = list->head.get();
    for (size_t i = 0; i < index; ++i) {
        if (!curr) {
            throw std::logic_error("Traversal failed: curr is nullptr.");
        }
        curr = curr->next.get();
    }

    // Logging the current node for debugging
    debugNode(curr, "Node to Delete");

    if (curr->prev) {
        curr->prev->next = std::move(curr->next);
    }

    if (curr->next) {
        curr->next->prev = curr->prev;
    }

    if (curr == list->head.get()) {
        list->head = std::move(curr->next);
    }

    if (curr == list->tail) {
        list->tail = curr->prev;
    }

    --list->size;
    if (list->size == 0) {
        list->head = nullptr;
        list->tail = nullptr;
    }
}

// A function to clear the whole doubly list nodes
// void doublyListClear(DoublyLinkedList* list) {
//     list ->head = nullptr;
//     list ->tail = nullptr;
//     list ->size = 0;
// }

void doublyListClear(DoublyLinkedList* list) {
    if (!list) {
        std::cerr << "Error: List is null.\n";
        return;
    }

    while (list->head) {
        auto next = std::move(list->head->next); // Move ownership of the next node
        if (next) {
            next->prev = nullptr; // Disconnect dangling raw pointer
        }
        list->head.reset(); // Safely delete the current node
        list->head = std::move(next); // Move to the next node
    }

    list->tail = nullptr; // Ensure tail is reset
    list->size = 0; // Reset the size
}

// A function to print all the data of the doubly list
void doublyListDisplay(const DoublyLinkedList* list) {
    DoublyNode* current = list->head.get();
    while (current) {
        std::cout << current->data << " <-> ";
        current = current->next.get();
    }
    std::cout << "NULL\n";
}

// A function to enable the usage of lambda functions or high order functions
void doublyListProcess(DoublyLinkedList* list, const std::function<void(int&)>& func) {
    DoublyNode* current = list->head.get();
    while (current) {
        func(current->data);
        current = current->next.get();
    }
}

// -------------------- CircularLinkedList Functions -------------------- //
// A function to create dynamic circular linked list
CircularLinkedList* createCircularLinkedList() {
    return new CircularLinkedList{nullptr, nullptr, 0};
}

// A function to add a node to the front of the circular list
void circularListPushFront(CircularLinkedList* list, int data) {
    auto newNode = std::make_unique<CircularNode>(data);
    if (list->tail) {
        newNode->next = std::move(list->head);
        list->head = std::move(newNode);
        // list->tail->next = list->head.get();
        list ->tail ->next.reset(list ->head.get());

    } else {
        list->head = std::move(newNode);
        list->tail = list->head.get();
        list->head->next.reset(list->tail); // Circular link
        // list ->tail ->next = list ->head.get();
    }
    ++list->size;
}

// A function to add a node to the back of the circular list
void circularListPushBack(CircularLinkedList* list, int data) {
    auto newNode = std::make_unique<CircularNode>(data);
    if (list->tail) {
        list->tail->next = std::move(newNode);
        list->tail = list->tail->next.get();
        list->tail->next.reset(list->head.get());
    } else {
        list->head = std::move(newNode);
        list->tail = list->head.get();
        list->head->next.reset(list->tail); // Circular link
    }
    ++list->size;
}

// A function to delete a node from the circular list front side
void circularListPopFront(CircularLinkedList* list) {
    if (list->head) {
        if (list->head.get() == list->tail) {
            list->head.reset();
            list->tail = nullptr;
        } else {
            list->head = std::move(list->head->next);
            list->tail->next.reset(list->head.get());
        }
        --list->size;
    }
}

// A function to delete a node from the circular list back side
void circularListPopBack(CircularLinkedList* list) {
    if(!list ->head) {
        return;
    }

    if(list ->head.get() == list ->tail) { // one node
        list ->head.reset();
        list ->tail = nullptr;
    }
    else {
        CircularNode* curr = list ->head.get();
        while(curr ->next.get() != list ->tail) {
            curr = curr ->next.get();
        }

        curr ->next.reset();
        list ->tail = curr;
        list ->tail ->next.reset(list ->head.get());
    }

    list ->size --;
}

// A function to clear the whole circular list nodes
void circularListClear(CircularLinkedList* list) {
    list->head.reset();
    list->tail = nullptr;
    list->size = 0;
}

// A function to print all the data of the circular list
void circularListDisplay(const CircularLinkedList* list) {
    if (!list->head) {
        std::cout << "NULL\n";
        return;
    }
    CircularNode* current = list->head.get();
    do {
        std::cout << current->data << " -> ";
        current = current->next.get();
    } while (current && current != list->head.get());
    std::cout << "(circular back to head)\n";
}

// A function to enable the usage of lambda functions or high order functions
void circularListProcess(CircularLinkedList* list, const std::function<void(int&)>& func) {
    if (!list->head) return;
    CircularNode* current = list->head.get();
    do {
        func(current->data);
        current = current->next.get();
    } while (current && current != list->head.get());
}

// =============================================== //
// Stack ForwardList - Stack using Singly Linked List Implementation
// =============================================== //
struct Stack {
    ForwardList* list;
};

// Functions prototype
Stack* createStack();
void stackPush(Stack* stack, int data);
int stackPop(Stack* stack);
int stackTop(const Stack* stack);
bool stackIsEmpty(const Stack* stack);
void stackClear(Stack* stack);

// =============================================== //
// Queue Forward List - Queue using Singly Linked List Implementation
// =============================================== //
struct Queue {
    ForwardList* list;
};

// functions prototype
Queue* createQueue();
void queueEnqueue(Queue* queue, int data);
int queueDeque(Queue* queue);
int queueFront(const Queue* queue);
bool queueIsEmpty(const Queue* queue);
void queueClear(Queue* queue);

// =============================================== //
// Deque List - Deque using doubly Linked List Implementation
// =============================================== //
struct Deque {
    DoublyLinkedList* list;
};

// functions prototype
void dequePushFront(Deque* deque, int data);
void dequePushBack(Deque* deque, int data);
int dequePopFront(Deque* deque);
int dequePopBack(Deque* deque);
int dequeFront(const Deque* deque);
int dequeBack(const Deque* deque);
bool dequeIsEmpty(const Deque* deque);
void dequeClear(Deque* deque);

// =============================================== //
// Implementations
// =============================================== //

// --------------------------------- Stack functions--------------------------------- 
// A function to create the dynamic stack
Stack* createStack() {
    Stack* stack = new Stack;
    stack->list = createForwardList();  // Default: using ForwardList
    return stack;
}

// A function to add element into the stack list
void stackPush(Stack* stack, int data) {
    forwardListPushFront(stack->list, data); 
}

// A function to delete an element from the stack list
int stackPop(Stack* stack) {
    if (stackIsEmpty(stack)) 
        throw std::out_of_range("Stack is empty");
    
    int topValue = stackTop(stack);
    forwardListPopFront(stack->list);  
    return topValue;
}

// A function to get the top value of the stack
int stackTop(const Stack* stack) {
    if (stackIsEmpty(stack)) 
        throw std::out_of_range("Stack is empty");
    
    return stack->list->head->data; 
}

// A function to check if the stack is empty
bool stackIsEmpty(const Stack* stack) {
    return stack->list->head == nullptr;
}

// A function to clear the whole stack list elements
void stackClear(Stack* stack) {
    forwardListClear(stack->list);
}

// --------------------------------- Queue functions--------------------------------- 
// A function to create the dynamic queue
Queue* createQueue() {
    Queue* queue = new Queue;
    queue->list = createForwardList();  
    return queue;
}

// A function to add element into the queue list
void queueEnqueue(Queue* queue, int data) {
    forwardListPushFront(queue->list, data);
}

// A function to delete an element from the queue list
int queueDequeue(Queue* queue) {
    if (queueIsEmpty(queue)) 
        throw std::out_of_range("Queue is empty");
    
    int frontValue = queueFront(queue);
    forwardListPopFront(queue->list);  
    return frontValue;
}

// A function to get the front value of the queue
int queueFront(const Queue* queue) {
    if (queueIsEmpty(queue)) 
        throw std::out_of_range("Queue is empty");
    
    return queue->list->head->data;  
}

// A function to check if the queue is empty
bool queueIsEmpty(const Queue* queue) {
    return queue->list->head == nullptr;
}

// A function to clear the whole queue list elements
void queueClear(Queue* queue) {
    forwardListClear(queue->list);
}

// --------------------------------- Deque functions--------------------------------- 
// A function to create the dynamic deque
Deque* createDeque() {
    Deque* deque = new Deque;
    deque->list = createDoublyLinkedList();  
    return deque;
}

// A function to add element into the deque list from the front side
void dequePushFront(Deque* deque, int data) {
    doublyListPushFront(deque->list, data);  
}

// A function to add element into the deque list from the back side
void dequePushBack(Deque* deque, int data) {
    doublyListPushBack(deque->list, data);  
}

// A function to delete an element from the deque list from the front side
int dequePopFront(Deque* deque) {
    if (dequeIsEmpty(deque)) 
        throw std::out_of_range("Deque is empty");
    
    int frontValue = dequeFront(deque);
    doublyListPopFront(deque->list);  
    return frontValue;
}

// A function to delete an element from the deque list from the back side
int dequePopBack(Deque* deque) {
    if (dequeIsEmpty(deque)) throw std::out_of_range("Deque is empty");
    int backValue = dequeBack(deque);
    doublyListPopBack(deque->list);  
    return backValue;
}

// A function to get the front value of the deque
int dequeFront(const Deque* deque) {
    if (dequeIsEmpty(deque)) 
        throw std::out_of_range("Deque is empty");
    
    return deque->list->head->data;  
}

// A function to get the back value of the deque
int dequeBack(const Deque* deque) {
    if (dequeIsEmpty(deque)) 
        throw std::out_of_range("Deque is empty");
    
    return deque->list->tail->data;  
}

// A function to check if the deque is empty
bool dequeIsEmpty(const Deque* deque) {
    return deque->list->head == nullptr;
}

// A function to clear the whole deque list elements
void dequeClear(Deque* deque) {
    doublyListClear(deque->list);  
}

int main() {
    // -------------------- Test ForwardList --------------------
    std::cout << "Testing ForwardList...\n";
    ForwardList* fl = createForwardList();
    forwardListPushFront(fl, 10);
    forwardListPushFront(fl, 20);
    forwardListPushFront(fl, 30);
    forwardListDisplay(fl);
    
    ForwardNode* first = fl->head.get();
    forwardListInsertAfter(fl, first, 25); 
    forwardListDisplay(fl); // List: 30 -> 25 -> 20 -> 10

    forwardListRemoveAfter(fl, first);
    forwardListDisplay(fl); // List: 30 -> 20 -> 10

    forwardListPopFront(fl);
    forwardListDisplay(fl); // List: 20 -> 10

    forwardListProcess(fl, [](int& value) { value *= 2; }); 
    forwardListDisplay(fl); // List: 40 -> 20

    forwardListClear(fl);
    forwardListDisplay(fl); 

    delete fl;

    // -------------------- Test DoublyLinkedList --------------------
    std::cout << "\nTesting DoublyLinkedList...\n";
    DoublyLinkedList* dll = createDoublyLinkedList();
    doublyListPushFront(dll, 10);
    doublyListPushFront(dll, 20);
    doublyListPushBack(dll, 5); // List: 20 <-> 10 <-> 5
    doublyListDisplay(dll);

    doublyListPopFront(dll); 
    doublyListDisplay(dll); // List: 10 <-> 5

    doublyListPopBack(dll); 
    doublyListDisplay(dll); // List: 10

    doublyListInsert(dll, 0, 30); 
    doublyListInsert(dll, 1, 40); 
    doublyListInsert(dll, 3, 50); 
    doublyListDisplay(dll); // List: 30 <-> 40 <-> 10 <-> 50

    doublyListErase(dll, 1); 
    doublyListDisplay(dll); // List: 30 <-> 10 <-> 50

    doublyListProcess(dll, [](int& value) { value += 10; }); 
    doublyListDisplay(dll); // List: 40 <-> 20 <-> 60

    doublyListClear(dll);
    doublyListDisplay(dll); 

    delete dll;

    // -------------------- Test CircularLinkedList --------------------
    std::cout << "\nTesting CircularLinkedList...\n";
    CircularLinkedList* cll = createCircularLinkedList();
    circularListPushFront(cll, 10);
    circularListPushBack(cll, 20);
    circularListPushFront(cll, 30); // List: 30 -> 10 -> 20
    circularListDisplay(cll);

    circularListPopFront(cll);
    circularListDisplay(cll); // List: 10 -> 20 

    circularListPopBack(cll);
    circularListDisplay(cll); // List: 10

    circularListClear(cll);
    circularListDisplay(cll); 

    delete cll; 

    // -------------------- Test Stack --------------------
    std::cout << "\nTesting Stack...\n";
    Stack* stack = createStack();
    stackPush(stack, 10);
    stackPush(stack, 20);
    stackPush(stack, 30); // Stack: 30, 20, 10
    std::cout << "Stack top: " << stackTop(stack) << "\n"; // 30
    std::cout << "Stack pop: " << stackPop(stack) << "\n"; // 30
    std::cout << "Stack pop: " << stackPop(stack) << "\n"; // 20
    std::cout << "Stack pop: " << stackPop(stack) << "\n"; // 10

    try {
        stackPop(stack); 
    } catch (const std::exception& e) {
        std::cout << e.what() << "\n";
    }

    delete stack->list;
    delete stack;

    // -------------------- Test Queue --------------------
    std::cout << "\nTesting Queue...\n";
    Queue* queue = createQueue();
    queueEnqueue(queue, 10);
    queueEnqueue(queue, 20);
    queueEnqueue(queue, 30); // Queue: 10, 20, 30
    std::cout << "Queue front: " << queueFront(queue) << "\n"; // 10
    std::cout << "Queue deque: " << queueDequeue(queue) << "\n"; // 10
    std::cout << "Queue deque: " << queueDequeue(queue) << "\n"; // 20
    std::cout << "Queue deque: " << queueDequeue(queue) << "\n"; // 30

    try {
        queueDequeue(queue); 
    } catch (const std::exception& e) {
        std::cout << e.what() << "\n";
    }

    delete queue->list;
    delete queue; 

    // -------------------- Test Deque --------------------
    std::cout << "\nTesting Deque...\n";
    Deque* deque = createDeque();
    dequePushFront(deque, 10);
    dequePushBack(deque, 20);
    dequePushFront(deque, 30); // Deque: 30, 10, 20
    std::cout << "Deque front: " << dequeFront(deque) << "\n"; // 30
    std::cout << "Deque back: " << dequeBack(deque) << "\n"; // 20
    std::cout << "Deque pop front: " << dequePopFront(deque) << "\n"; // 30
    std::cout << "Deque pop back: " << dequePopBack(deque) << "\n"; // 20
    std::cout << "Deque pop front: " << dequePopFront(deque) << "\n"; // 10

    try {
        dequePopFront(deque); 
    } catch (const std::exception& e) {
        std::cout << e.what() << "\n";
    }

    delete deque->list;
    delete deque;
}