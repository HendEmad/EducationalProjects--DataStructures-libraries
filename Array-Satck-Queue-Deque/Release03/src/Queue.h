// src/Queue.h
#ifndef QUEUE_H
#define QUEUE_H

#include "Array.h"
#include "AbstractDS.h"
using namespace std;

class Queue : public AbstractDS {
    Array array;
    int front, rear;
public:
    Queue(int init_capacity = 10);
    void add_element(int element) override;
    int remove_element() override;
    int get_front();
    void process_elements(const function<void(int)>& process_fn) override;
    void print() override;
    int get_front_idx();
    void search(int element, int front = -1) override;
};

#endif // QUEUE_H