#include "ForwardList.h"
#include "DoublyList.h"
#include "CircularList.h"
#include <iostream>

int main() {
    // Testing ForwardList
    // std::cout << "------------Testing ForwardList-------------\n";
    // ForwardList<int> fl;
    // fl.pushBack(10);
    // fl.pushBack(20);
    // fl.pushFront(5);
    // fl.display(); // Expected: 5 -> 10 -> 20 -> Null

    // fl.popFront();
    // fl.display(); // Expected: 10 -> 20 -> Null

    // fl.popBack();
    // fl.display(); // Expected: 10 -> Null

    // fl.insert(1, 15);
    // fl.display(); // Expected: 10 -> 15 -> Null

    // fl.erase(1);
    // fl.display(); // Expected: 10 -> Null

    // // Testing DoublyList
    std::cout << "\n-----------------Testing DoublyList-----------------------\n";
    DoublyList<int> dl;
    dl.pushFront(100);
    dl.pushBack(200);
    dl.pushFront(50);
    dl.display(); // Expected: 50 <-> 100 <-> 200 <-> NULL

    dl.popBack();
    dl.display(); // Expected: 50 <-> 100 <-> NULL

    dl.insert(1, 75);
    dl.display(); // Expected: 50 <-> 75 <-> 100 <-> NULL

    dl.erase(1);
    dl.display(); // Expected: 50 <-> 100 <-> NULL

    // Testing CircularList
    std::cout << "\n----------------------Testing CircularList-------------------\n";
    CircularList<int> cl;
    cl.pushBack(1);
    cl.pushBack(2);
    cl.pushFront(0);
    cl.display(); // Expected: 0 -> 1 -> 2 -> (back to head)

    cl.popFront();
    cl.display(); // Expected: 1 -> 2 -> (back to head)

    cl.popBack();
    cl.display(); // Expected: 1 -> (back to head)

    cl.insert(1, 3);
    cl.display(); // Expected: 1 -> 3 -> (back to head)

    cl.erase(1);
    cl.display(); // Expected: 1 -> (back to head)

    return 0;
}