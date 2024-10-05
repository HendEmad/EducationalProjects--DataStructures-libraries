// src/Queue.h
#ifndef QUEUE_H
#define QUEUE_H

#include "Array.h"
using namespace std;

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

#endif // QUEUE_H