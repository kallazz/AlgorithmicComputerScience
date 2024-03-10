#ifndef DOUBLY_LINKED_LIST_HPP
#define DOUBLY_LINKED_LIST_HPP

struct DoublyLinkedListNode {
    int value;
    DoublyLinkedListNode* next;
    DoublyLinkedListNode* previous;
};

struct DoublyLinkedList {
    int size;
    DoublyLinkedListNode* head;
    DoublyLinkedListNode* tail;
    DoublyLinkedListNode* currentNode;
};

void insertIntoEmptyList(DoublyLinkedList* l, int value);
void insert(DoublyLinkedList* l, int value);
void merge(DoublyLinkedList* l1, DoublyLinkedList* l2);

void moveToNext(DoublyLinkedList* l);
void moveToPrevious(DoublyLinkedList* l);
void printAllElementsInOrder(DoublyLinkedList* l);
int calculateSearchCost(DoublyLinkedList* l, int numberToFind);
int calculateSearchCostLeft(DoublyLinkedList* l, int numberToFind);
int calculateSearchCostRight(DoublyLinkedList* l, int numberToFind);

#endif // DOUBLY_LINKED_LIST_HPP
