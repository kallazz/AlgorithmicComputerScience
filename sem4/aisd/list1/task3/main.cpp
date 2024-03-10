#include "DoublyLinkedList.hpp"

#include <iostream>

const int RANDOM_ARRAY_SIZE = 10000;
const int RANDOM_UPPER_BOUND = 100000;

int getRandomNumber(int upperBound) {
    return rand() % (upperBound + 1);
}

void fillArrayWithRandomNumbers(int array[RANDOM_ARRAY_SIZE], int upperBound = RANDOM_UPPER_BOUND) {
    for (int i = 0; i < RANDOM_ARRAY_SIZE; i++) {
        array[i] = getRandomNumber(upperBound);
    }
}

int getRandomElementFromArray(int array[RANDOM_ARRAY_SIZE]) {
    int index = rand() % (RANDOM_ARRAY_SIZE + 1);
    return array[index];
}

int main() {
    DoublyLinkedList* list1 = new DoublyLinkedList();
    DoublyLinkedList* list2 = new DoublyLinkedList();

    for (int i = 10; i <= 19; i++) {
        insert(list1, i);
        insert(list2, i + 10);
    }

    std::cout << "List1: ";
    printAllElementsInOrder(list1);
    std::cout << "List2: ";
    printAllElementsInOrder(list2);

    merge(list1, list2);
    std::cout << "Merged list: ";
    printAllElementsInOrder(list1);

    delete list1;
    delete list2;


    srand((unsigned) time(NULL));

    DoublyLinkedList* L = new DoublyLinkedList();
    int T[RANDOM_ARRAY_SIZE];
    fillArrayWithRandomNumbers(T);
    for (const auto number : T) {
        insert(L, number);
    }

    int averageComparisons = 0;
    for (int i = 0; i < 1000; i++) {
        int number = getRandomElementFromArray(T);
        averageComparisons += calculateSearchCost(L, number);
    }
    averageComparisons = averageComparisons / 1000;
    std::cout << "Average comparisons with elements from T: " << averageComparisons << '\n';

    averageComparisons = 0;
    for (int i = 0; i < 1000; i++) {
        int number = getRandomNumber(RANDOM_UPPER_BOUND);
        averageComparisons += calculateSearchCost(L, number);
    }
    averageComparisons = averageComparisons / 1000;
    std::cout << "Average comparisons with random numbers: " << averageComparisons << '\n';

    delete L;

    return 0;
}