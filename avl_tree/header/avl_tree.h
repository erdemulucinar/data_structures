#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <stdlib.h>
#include "stdio.h"

//  A generic AVL tree implementation interface, where the keys are taken in as void
//pointers to any data structure. To make the tree act like a template, user must
//define application specific functions somewhere according to the template below and
//feed their pointers to the constructor of the tree.

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
//used for sortprint, report and tree map print functionalities.
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
    int len;
} AVLTree;

//Operations on tree
//Constructor of AVL.
AVLTree* createAVL(copyFunction copy, deleteFunction del, compareFunction compare);
//Key insertion function.
int insertAVL(AVLTree *tree, void *key);
//Key removal function.
int removeAVL(AVLTree *tree, void *key);
//BST search function.
void* searchAVL(AVLTree *tree, void *key);
//A function to free all the heap memory used by the tree in parameter.
void flushAVL(AVLTree *tree);
//A function to list the keys of the tree in an array.
void listAVL(AVLTree *tree, void **list);

//Debug functions
//  Prints the whole tree, with the head node having 0 tabs before, and i'th level nodes
//are printed with i number of tabs on new lines. Right node is printed first left second.
//For example,
//                     a
//                  b     g
//                c     f    h
//              d   e          i
//is printed as follows:
//  a
//      g
//          h
//              i
//          f
//      b
//          c
//              e
//              d
void printAVL(AVLTree *tree, printFunction print);
//Report scans all the nodes in the tree and reports the maximum deviation from the
//balance with maxDeviation parameter and reports if the nodes in the tree are placed
//correctly, i.e. if the tree is sorted correctly.
void reportAVL(AVLTree *tree, int *isTreeSorted, int *maxDeviation);

#endif
