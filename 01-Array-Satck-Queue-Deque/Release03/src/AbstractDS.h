#ifndef ABSTRACTDS
#define ABSTRACTDS

#include <iostream>
#include <functional>
using namespace std;

class AbstractDS {
public:
    virtual void add_element(int element) = 0;
    virtual int remove_element() = 0;
    virtual void print() = 0;
    virtual void process_elements(const function<void(int)>& process_fn) = 0;
    // virtual ~AbstractDS() = default;
    virtual void search(int element, int front = -1) = 0;
};

#endif  // ABSTRACTDS