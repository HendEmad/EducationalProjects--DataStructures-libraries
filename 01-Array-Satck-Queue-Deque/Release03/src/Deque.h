// src/Deque.h
#ifndef DEQUE_H
#define DEQUE_H

#include "Array.h"
#include "AbstractDS.h"
using namespace std;

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
    void print() override;
    int get_front();
    int get_rear();
    void process_elements(const function<void(int)>& process_fn) override;
    int get_front_idx() const;
    void search(int element, int front = -1) override;
};

#endif //DEQUE_H