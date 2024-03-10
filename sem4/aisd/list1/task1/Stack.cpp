#include "Stack.hpp"

#include <iostream>

void Stack::push(int value) {
    currentHeight_++;
    if (currentHeight_ > MAX_SIZE) {
        std::cout << "Can't add to the stack. It's full.\n";
        return;
    }

    elements_[currentHeight_ - 1] = value;
    std::cout << value << " added to the stack.\n";
}

int Stack::pop() {
    if (isEmpty()) {
        std::cout << "Can't pop from the stack. It's empty.\n";
        return 0;
    }

    int poppedElement = elements_[currentHeight_ - 1];
    currentHeight_--;

    std::cout << poppedElement << " popped from the stack.\n";

    return poppedElement;
}

bool Stack::isEmpty() {
    return currentHeight_ <= 0;
}
