#include "DoublyLinkedList.hpp"

#include <iostream>

void insertIntoEmptyList(DoublyLinkedList* l, int value) {
    DoublyLinkedListNode* newNode = new DoublyLinkedListNode();
    newNode->value = value;
    newNode->next = newNode;
    newNode->previous = newNode;

    l->currentNode = newNode;
    l->head = newNode;
    l->tail = newNode;
    l->size++;
}

void insert(DoublyLinkedList* l, int value) {
    if (l->size == 0) {
        insertIntoEmptyList(l, value);
    } else {
        DoublyLinkedListNode* newNode = new DoublyLinkedListNode();
        newNode->value = value;
        newNode->next = l->head;
        newNode->previous = l->tail;

        l->tail->next = newNode;
        l->tail = newNode;
        l->size++;
        l->head->previous = newNode;
    }
}

void merge(DoublyLinkedList* l1, DoublyLinkedList* l2) {
    l1->tail->next = l2->head;
    l2->tail->next = l1->head;
    l1->head->previous = l2->tail;
    l2->head->previous = l1->tail;
    l2->head = l1->head;

    int firstListSize = l1->size;
    l1->size += l2->size;
    l2->size += firstListSize;
}

void moveToNext(DoublyLinkedList* l) {
    l->currentNode = l->currentNode->next;
}

void moveToPrevious(DoublyLinkedList* l) {
    l->currentNode = l->currentNode->previous;
}

void printAllElementsInOrder(DoublyLinkedList* l) {
    DoublyLinkedListNode* currentNode = l->currentNode;

    l->currentNode = l->head;
    for (int i = 0; i < l->size - 1; i++) {
        std::cout << l->currentNode->value << ", ";
        moveToNext(l);
    }
    std::cout << l->currentNode->value << '\n';

    l->currentNode = currentNode;
}

int calculateSearchCost(DoublyLinkedList* l, int numberToFind) {
    if (rand() % 2 == 0) {
        return calculateSearchCostLeft(l, numberToFind);
    }
    return calculateSearchCostRight(l, numberToFind);
}

int calculateSearchCostLeft(DoublyLinkedList* l, int numberToFind) {
    int comparisons = 0;
    while (comparisons < l->size && l->currentNode->value != numberToFind) {
        moveToPrevious(l);
        comparisons++;
    }
    return comparisons;
}

int calculateSearchCostRight(DoublyLinkedList* l, int numberToFind) {
    int comparisons = 0;
    while (comparisons < l->size && l->currentNode->value != numberToFind) {
        moveToNext(l);
        comparisons++;
    }
    comparisons++;
    return comparisons;
}
