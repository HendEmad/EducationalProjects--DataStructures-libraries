#include "Release02/List/IList.h"
#include "Release02/LinearDS/headers/IDataStructure.h"
#include "Release02/List/ForwardList.h"
#include "Release02/List/DoublyList.h"
#include "Release02/List/CircularList.h"
#include "Release02/LinearDS/headers/Stack.h"
#include "Release02/LinearDS/headers/Queue.h"
#include "Release02/LinearDS/headers/Deque.h"

int main() {
    // ForwardList example
    ForwardList<int> forwardList;
    forwardList.pushFront(10);
    forwardList.pushFront(20);
    std::cout << "ForwardList Front: " << forwardList.front() << "\n";
    std::cout << "ForwardList Back: " << forwardList.back() << "\n";

    // DoublyLinkedList example
    DoublyList<int> doublyList;
    doublyList.pushFront(30);
    doublyList.pushBack(40);
    std::cout << "DoublyList Front: " << doublyList.front() << "\n";
    std::cout << "DoublyList Back: " << doublyList.back() << "\n";

    // CircularLinkedList example
    CircularList<int> circularList;
    circularList.pushBack(50);
    circularList.pushBack(60);
    std::cout << "CircularList Front: " << circularList.front() << "\n";
    std::cout << "CircularList Back: " << circularList.back() << "\n";

    return 0;
}
