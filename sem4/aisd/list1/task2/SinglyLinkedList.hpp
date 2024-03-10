#ifndef SINGLY_LINKED_LIST_HPP
#define SINGLY_LINKED_LIST_HPP

struct SinglyLinkedListNode {
    int value;
    SinglyLinkedListNode* next;
};

struct SinglyLinkedList {
    int size;
    SinglyLinkedListNode* head;
    SinglyLinkedListNode* tail;
    SinglyLinkedListNode* currentNode;
};

void insertIntoEmptyList(SinglyLinkedList* l, int value);
void insert(SinglyLinkedList* l, int value);
void merge(SinglyLinkedList* l1, SinglyLinkedList* l2);

void moveToNext(SinglyLinkedList* l);
void printAllElementsInOrder(SinglyLinkedList* l);
int calculateSearchCost(SinglyLinkedList* l, int numberToFind);

#endif // SINGLY_LINKED_LIST_HPP
