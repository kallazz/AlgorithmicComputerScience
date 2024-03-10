#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <cstddef>

class Queue {
public:
    static const int MAX_SIZE = 100;

    Queue() {}

    void push(int value);
    int pop();

private:
    int currentSize_ = 0;
    int firstElementIndex_ = 0;
    int lastElementIndex_ = -1;
    int elements_[MAX_SIZE];

    bool isEmpty();
};

#endif // QUEUE_HPP
