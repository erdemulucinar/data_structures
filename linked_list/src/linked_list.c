#include "linked_list.h"

//-------------------------------------------------------------------------------
//-----------------------------Interface Functions-------------------------------
//-------------------------------------------------------------------------------

LinkedList* createLinkedList(copyFunction copy, deleteFunction del, compareFunction compare){
    LinkedList *list;
    
    list = malloc(sizeof(LinkedList));
    list->copyFcn = copy;
    list->delFcn = del;
    list->compFcn = compare;
    list->len = 0;
    list->head = 0;
    
    return list;
}

int pushLinkedList(LinkedList *list, void *key){
    LinkedListNode *newNode;
    
    //Null list check
    if(!list){
        return 0;
    }
    
    //Adding the node as the head
    newNode = malloc(sizeof(LinkedListNode));
    newNode->key = list->copyFcn(key);
    newNode->next = list->head;
    list->head = newNode;
    
    list->len = list->len + 1;
    return 1;
}

int appendLinkedList(LinkedList *list, void *key){
    LinkedListNode *newNode, **currentNode;
    
    //Null list check
    if(!list){
        return 0;
    }
    
    //To eliminate the need to check for empty list, pointer to pointer reference
    //is used. This way, at any time the current node is accessed through the
    //previous node's next pointer. Thus updating the value of the pointer results
    //in updating the previous node's next pointer.
    currentNode = &(list->head);
    while(*currentNode){
        currentNode = &((*currentNode)->next);
    }
    
    //Create the new node
    newNode = malloc(sizeof(LinkedListNode));
    newNode->key = list->copyFcn(key);
    newNode->next = 0;
    
    //Add the node to the list
    *currentNode = newNode;
    list->len = list->len + 1;
    return 1;
}

int removeLinkedList(LinkedList *list, void *key){
    LinkedListNode **currNode, *tmp;
    int compRes;
    
    //Null list check
    if(!list){
        return 0;
    }
    
    //Search for the key iterating over the previous nodes to make the remove
    //process easier. At any time, the compared node is viewed from the previous
    //node's next pointer. For the head, it is the next pointer of list. Thus there
    //no need to keep track of the previous node.
    currNode = &(list->head);
    while(*currNode){
        compRes = list->compFcn((*currNode)->key,key);
        if(!compRes){ //Key is found
            //Copy the next pointer of the node to be removed
            tmp = (*currNode)->next;
            //Free the removed node's data
            list->delFcn((*currNode)->key);
            free(*currNode);
            //Set the next pointer of the previous node to the node following the
            //removed node.
            *currNode = tmp;
            list->len = list->len - 1;
            return 1;
        } else{
            currNode = &((*currNode)->next);
        }
    }
    
    //Node to be deleted was not foundç
    return 0;
}

void* searchLinkedList(LinkedList *list, void *key){
    LinkedListNode *currNode;
    int compRes;
    
    //Null list check
    if(!list){
        return 0;
    }
    
    //Go through the list and check for equivalence
    currNode = list->head;
    while(currNode){
        compRes = list->compFcn(currNode->key,key);
        if(compRes){ //Key not found check next
            currNode = currNode->next;
        } else{ //Key found
            return currNode->key;
        }
    }
    
    //Not found
    return 0;
}

void flushLinkedList(LinkedList *list){
    LinkedListNode *currNode, *tmp;
    
    currNode = list->head;
    while(currNode){
        tmp = currNode->next;
        list->delFcn(currNode->key);
        free(currNode);
        currNode = tmp;
    }
    
    free(list);
}

LinkedList* copyLinkedList(LinkedList *list){
    LinkedList *newList;
    LinkedListNode *node;
    
    newList = malloc(sizeof(LinkedList));
    newList->copyFcn = list->copyFcn;
    newList->delFcn = list->delFcn;
    newList->compFcn = list->compFcn;
    newList->len = 0;
    newList->head = 0;
    
    node = list->head;
    while(node){
        appendLinkedList(newList, (void*) node->key);
        node = node->next;
    }
    
    return newList;
}

//Debug functions
void printLinkedList(LinkedList *list, printFunction print){
    LinkedListNode *currNode;
    
    currNode = list->head;
    while(currNode){
        print(currNode->key);
        printf(" ");
        currNode = currNode->next;
    }
    printf("\n");
}
