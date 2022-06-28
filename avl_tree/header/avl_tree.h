#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <stdlib.h>
#include "stdio.h"

typedef void* (*copyFunction) (void*);
typedef void (*deleteFunction) (void*);
typedef int (*compareFunction) (void*,void*);
typedef void (*printFunction) (void*);

typedef struct AVLNode{
    void *key;
    struct AVLNode* left;
    struct AVLNode* right;
} AVLNode;

typedef struct AVLTree{
    copyFunction copyFcn;
    deleteFunction delFcn;
    compareFunction compFcn;
    AVLNode *head;
} AVLTree;

//Operations on tree
AVLTree* createAVL(copyFunction copy, deleteFunction del, compareFunction compare);
AVLTree* insertAVL(AVLTree *tree, void *key);
AVLTree* removeAVL(AVLTree *tree, void *key);
void* searchAVL(AVLTree *tree, void *key);
void flushAVL(AVLTree * tree);

//Debug functions
void printAVL(AVLTree *tree, printFunction print);
void reportAVL(AVLTree *tree, printFunction print);

#endif
