#include "linked_list.h"

//-------------------------------------------------------------------------------
//-----------------------------Interface Functions-------------------------------
//-------------------------------------------------------------------------------

LinkedList* createLinkedList(copyFunction copy, deleteFunction del, compareFunction compare, int isUnique){
    LinkedList *list;
    
    list = malloc(sizeof(LinkedList));
    list->copyFcn = copy;
    list->delFcn = del;
    list->compFcn = compare;
    list->len = 0;
    list->head = 0;
    list->isUnique = isUnique;
    
    return list;
}

int pushLinkedList(LinkedList *list, void *key){
    LinkedListNode *newNode;
    void* searchRes;
    
    //Null list check
    if(!list){
        return 0;
    }
    
    //Searching the list for unique option.
    if(list->isUnique){
        searchRes = searchLinkedList(list, key);
    } else{
        searchRes = 0;
    }
    
    //Adding the node as the head
    if(searchRes){
        return 0;
    } else{
        newNode = malloc(sizeof(LinkedListNode));
        newNode->key = list->copyFcn(key);
        newNode->next = list->head;
        list->head = newNode;
    }
    
    list->len = list->len + 1;
    return 1;
}

int appendLinkedList(LinkedList *list, void *key){
    LinkedListNode *newNode, **currentNode;
    int compRes;
    
    //Null list check
    if(!list){
        return 0;
    }
    
    //Go to the end of the list while checking the uniqueness when it is enabled.
    //To eliminate the need to check for empty list, pointer to pointer reference
    //is used. This way, at any time the current node is accessed through the
    //previous node's next pointer. Thus updating the value of the pointer to
    //pointer, previous node's next is updated.
    currentNode = &(list->head);
    while(*currentNode){
        if(list->isUnique){
            compRes = list->compFcn((*currentNode)->key,key);
        } else{
            compRes = 1;
        }
        
        if(compRes){
            currentNode = &((*currentNode)->next);
        } else{
            return 0;
        }
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
    int compRes, keyFound;
    
    //Null list check
    if(!list){
        return 0;
    }
    
    //Search for the key iterating over the previous nodes to make the remove
    //process easier. At any time, the compared node is viewed from the previous
    //node's next pointer. For the head, it is the next pointer of list.
    keyFound = 0;
    currNode = &(list->head);
    while(*currNode){
        compRes = list->compFcn((*currNode)->key,key);
        if(!compRes){ //Key is found
            //Copy the next pointer of the removed node
            tmp = (*currNode)->next;
            //Free the removed node's data
            list->delFcn((*currNode)->key);
            free(*currNode);
            //Set the next pointer of the removed node's previous node to the
            //next pointer of the removed node.
            *currNode = tmp;
            list->len = list->len - 1;
            if(list->isUnique){
                return 1;
            } else{ //When the list is not unique, all copies are deleted.
                if(*currNode)
                    keyFound = 1;
                else
                    return 1;
            }
        } else{
            currNode = &((*currNode)->next);
        }
    }
    
    return keyFound;
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
