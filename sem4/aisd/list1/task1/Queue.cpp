#include "Queue.hpp"

#include <iostream>

void Queue::push(int value) {
    lastElementIndex_ = (lastElementIndex_ + 1) % MAX_SIZE;
    currentSize_++;

    if (currentSize_ > MAX_SIZE) {
        std::cout << "Can't add to the queue. It's full.\n";
        return;
    }

    elements_[lastElementIndex_] = value;
    std::cout << value << " added to the queue.\n";
}

int Queue::pop() {
    if (isEmpty()) {
        std::cout << "Can't pop from the queue. It's empty.\n";
        return 0;
    }

    int poppedElement = elements_[firstElementIndex_];
    firstElementIndex_ = (firstElementIndex_ + 1) % MAX_SIZE;
    currentSize_--;

    std::cout << poppedElement << " popped from the queue.\n";

    return poppedElement;
}

bool Queue::isEmpty() {
    return currentSize_ <= 0;
}
