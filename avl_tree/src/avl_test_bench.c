#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "avl_tree.h"

//AVL key functions for integers
void* copyInt(void *a){
    int *x,*y;

    x = (int*) a;
    y = malloc(sizeof(int));
    *y = *x;
    
    return (void*) y;
}

void delInt (void *a){
    int *x;
    
    x = (int*) a;
    free(x);
}

int compInt(void *a, void *b){
    int *x,*y;
    
    x = (int*) a;
    y = (int*) b;
    
    return *x - *y;
}

void printInt(void *a){
    int *x;
    
    x = (int*) a;
    printf("%d",*x);
}

//Test bench helpers
int* randList(int len){
    int *list, i, j, temp;
    
    list = malloc(len*sizeof(int));
    for(i = 0; i < len; i++)
        list[i] = i;
    
    for(i = 0; i < len; i++){
        j = rand() % (len-i) + i;
        temp = list[i];
        list[i] = list[j];
        list[j] = temp;
    }
    
    return list;
}

AVLTree* insertionTest(int len, int *isSortedAcc, int *maxDevAcc, int *treeLenAcc){
    AVLTree *tree;
    int *list, isSorted, maxDev, treeLen, treeLenPrev, i;

    list = randList(len);
    
    //First addition test
    *isSortedAcc = 1;
    *maxDevAcc = 0;
    treeLen = 0;
    treeLenPrev = 0;
    *treeLenAcc = 1;
    tree = createAVL(&copyInt, &delInt, &compInt);
    for(i = 0; i < len; i++){
        insertAVL(tree, (void*) (list+i));
        
        //Tree status check
        reportAVL(tree, &isSorted, &maxDev);
        
        //Inorder check
        *isSortedAcc = *isSortedAcc & isSorted;
        
        //Balance check
        if(maxDev > *maxDevAcc)
            *maxDevAcc = maxDev;
        
        //Insert logic check
        treeLen = tree->len;
        if(treeLen != treeLenPrev+1)
            *treeLenAcc = 0;
        treeLenPrev = treeLen;
    }
    
    //Duplicate test
    for(i = 0; i < len; i++){
        insertAVL(tree, (void*)&i);
        
        //Tree status check
        reportAVL(tree, &isSorted, &maxDev);
        
        //Inorder check
        *isSortedAcc = *isSortedAcc & isSorted;
        
        //Balance check
        if(maxDev > *maxDevAcc)
            *maxDevAcc = maxDev;
        
        //Insert logic check
        treeLen = tree->len;
        if(treeLen != treeLenPrev)
            *treeLenAcc = 0;
    }
    free(list);
    return tree;
}

void deletionTest(AVLTree* tree, int len, int *isSortedAcc, int *maxDevAcc, int *treeLenAcc){
    int *list, isSorted, maxDev, treeLen, treeLenPrev, i;

    list = randList(len);
    
    //First removal test
    *isSortedAcc = 1;
    *maxDevAcc = 0;
    treeLen = 0;
    treeLenPrev = len;
    *treeLenAcc = 1;
    for(i = 0; i < len; i++){
        removeAVL(tree, (void*) &(list[i]));
        
        //Tree status check
        reportAVL(tree, &isSorted, &maxDev);
        
        //Inorder check
        *isSortedAcc = *isSortedAcc & isSorted;
        
        //Balance check
        if(maxDev > *maxDevAcc)
            *maxDevAcc = maxDev;
        
        //Insert logic check
        treeLen = tree->len;
        if(treeLen != treeLenPrev-1)
            *treeLenAcc = 0;
        treeLenPrev = treeLen;
    }
    
    //Duplicate test
    for(i = 0; i < len; i++){
        removeAVL(tree, (void*)&i);
        
        //Tree status check
        reportAVL(tree, &isSorted, &maxDev);
        
        //Inorder check
        *isSortedAcc = *isSortedAcc & isSorted;
        
        //Balance check
        if(maxDev > *maxDevAcc)
            *maxDevAcc = maxDev;
        
        //Insert logic check
        treeLen = tree->len;
        if(treeLen != treeLenPrev)
            *treeLenAcc = 0;
    }
    
    free(list);
    free(tree);
}

int avlTest(int repeat_cnt, int len) {
    AVLTree *tree;
    int repeat_cnt, len;
    int isSortedAcc, maxDevAcc, treeLenAcc;
    int isSortedAccInsertion, maxDevAccInsertion, treeLenAccInsertion;
    int isSortedAccDeletion, maxDevAccDeletion, treeLenAccDeletion;
    int i;
    
    srand((unsigned)(time(0)));
    
    isSortedAccInsertion = 1;
    maxDevAccInsertion = 0;
    treeLenAccInsertion = 1;
    isSortedAccDeletion = 1;
    maxDevAccDeletion = 0;
    treeLenAccDeletion = 1;
    
    for(i = 0; i < repeat_cnt; i++){
        tree = insertionTest(len,&isSortedAcc, &maxDevAcc, &treeLenAcc);
        isSortedAccInsertion = isSortedAccInsertion & isSortedAcc;
        treeLenAccInsertion = treeLenAccInsertion & treeLenAcc;
        if(maxDevAcc > maxDevAccInsertion)
            maxDevAccInsertion = maxDevAcc;
        
        deletionTest(tree, len,&isSortedAcc, &maxDevAcc, &treeLenAcc);
        isSortedAccDeletion = isSortedAccDeletion & isSortedAcc;
        treeLenAccDeletion = treeLenAccDeletion & treeLenAcc;
        if(maxDevAcc > maxDevAccDeletion)
            maxDevAccDeletion = maxDevAcc;
    }
    
    if(isSortedAccInsertion)
        printf("INSERTION SORTED SUCCESS: List is sorted.\n");
    else
        printf("INSERTION SORTED FAILURE: List is not sorted.\n");
    if(maxDevAccInsertion <= 1)
        printf("INSERTION BALANCE SUCCESS: List is balanced.\n");
    else
        printf("INSERTION BALANCE FAILURE: List is not balanced.\n");
    if(treeLenAccInsertion)
        printf("INSERTION LENGTH CHECK SUCCESS: List's length is correct.\n");
    else
        printf("INSERTION LENGTH CHECK FAILURE: List's length is not correct.\n");
    
    if(isSortedAccDeletion)
        printf("DELETION SORTED SUCCESS: List is sorted.\n");
    else
        printf("DELETION SORTED FAILURE: List is not sorted.\n");
    if(maxDevAccDeletion <= 1)
        printf("DELETION BALANCE SUCCESS: List is balanced.\n");
    else
        printf("DELETION BALANCE FAILURE: List is not balanced.\n");
    if(treeLenAccDeletion)
        printf("DELETION LENGTH CHECK SUCCESS: List's length is correct.\n");
    else
        printf("DELETION LENGTH CHECK FAILURE: List's length is not correct.\n");
    
    return 0;
}
