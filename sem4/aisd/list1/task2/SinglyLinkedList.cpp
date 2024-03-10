#include "SinglyLinkedList.hpp"

#include <iostream>

void insertIntoEmptyList(SinglyLinkedList* l, int value) {
    SinglyLinkedListNode* newNode = new SinglyLinkedListNode();
    newNode->value = value;
    newNode->next = newNode;

    l->currentNode = newNode;
    l->head = newNode;
    l->tail = newNode;
    l->size++;
}

void insert(SinglyLinkedList* l, int value) {
    if (l->size == 0) {
        insertIntoEmptyList(l, value);
    } else {
        SinglyLinkedListNode* newNode = new SinglyLinkedListNode();
        newNode->value = value;
        newNode->next = l->head;

        l->tail->next = newNode;
        l->tail = newNode;
        l->size++;
    }
}

void merge(SinglyLinkedList* l1, SinglyLinkedList* l2) {
    l1->tail->next = l2->head;
    l2->tail->next = l1->head;
    l2->head = l1->head;

    int firstListSize = l1->size;
    l1->size += l2->size;
    l2->size += firstListSize;
}

void moveToNext(SinglyLinkedList* l) {
    l->currentNode = l->currentNode->next;
}

void printAllElementsInOrder(SinglyLinkedList* l) {
    SinglyLinkedListNode* currentNode = l->currentNode;

    l->currentNode = l->head;
    for (int i = 0; i < l->size - 1; i++) {
        std::cout << l->currentNode->value << ", ";
        moveToNext(l);
    }
    std::cout << l->currentNode->value << '\n';

    l->currentNode = currentNode;
}

int calculateSearchCost(SinglyLinkedList* l, int numberToFind) {
    int comparisons = 0;
    while (comparisons < l->size && l->currentNode->value != numberToFind) {
        moveToNext(l);
        comparisons++;
    }
    comparisons++;
    return comparisons;
}