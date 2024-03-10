#ifndef STACK_HPP
#define STACK_HPP

#include <cstddef>

class Stack {
public:
    static const int MAX_SIZE = 100;

    Stack() {}

    void push(int value);
    int pop();

private:
    int currentHeight_ = 0;
    int elements_[MAX_SIZE];

    bool isEmpty();
};

#endif // STACK_HPP
