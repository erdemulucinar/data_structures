#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>
#include "stdio.h"

//  A generic linked list implementation interface, where the values are taken in as
//void pointers to any data structure. To make the list act like a template, user must
//define application specific functions somewhere according to the template below and
//feed their pointers to the constructor of the list.

//  User must define below functions somewhere in the code for the application at hand
//Copy function must allocate memory and copy what is inside the key in parameter.
typedef void* (*copyFunction) (void*);
//Delete function must free any memory which is used by the application specific key.
typedef void (*deleteFunction) (void*);
//  Compare function must return >0 when first argument is bigger than the second
//according to any metric defined on any data type key represents, <0 when first
//argument is smaller than the second and =0 when the arguments are equal.
typedef int (*compareFunction) (void*,void*);
//  Print function must use printf to print any relevant information inside key. It is
//used for link print functionality.
typedef void (*printFunction) (void*);

typedef struct LinkedListNode{
    void *key;
    struct LinkedListNode *next;
} LinkedListNode;

typedef struct LinkedList{
    copyFunction copyFcn;
    deleteFunction delFcn;
    compareFunction compFcn;
    LinkedListNode *head;
    int len;
} LinkedList;

//Operations on linked list
//Constructor of the list.
LinkedList* createLinkedList(copyFunction copy, deleteFunction del, compareFunction compare);
//Insertion function to the beginning of the list
int pushLinkedList(LinkedList *list, void *key);
//Insertion function to the end of the list
int appendLinkedList(LinkedList *list, void *key);
//Pop function to use the linked list as FIFO or LIFO
void* popLinkedList(LinkedList *list);
//Removal function
int removeLinkedList(LinkedList *list, void *key);
//Search function
void* searchLinkedList(LinkedList *list, void *key);
//A function to empty a list
void flushLinkedList(LinkedList *list);
//A function to copy all the contents of a linked list
LinkedList* copyLinkedList(LinkedList *list);

//Debug functions
void printLinkedList(LinkedList *list, printFunction print);

#endif
