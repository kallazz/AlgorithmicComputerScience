#include "Queue.hpp"
#include "Stack.hpp"

#include <iostream>

int main() {
    std::cout << "********** STACK **********\n";
    Stack stack;
    for (int i = 1; i <= 50; i++) {
        stack.push(i);
    }
    for (int i = 1; i <= 50; i++) {
        stack.pop();
    }

    std::cout << "\n********** QUEUE **********\n";
    Queue queue;
    for (int i = 1; i <= 50; i++) {
        queue.push(i);
    }
    for (int i = 1; i <= 50; i++) {
        queue.pop();
    }

    return 0;
}
