#include <stdio.h>
#include "test_bench_defs.h"
#include "linked_list.h"

//Test bench functions
void insertRemoveTestLinkedList(int len, int isUnique, int *testRes){
    LinkedList *list;
    int *vals, i, opRes;
    
    *testRes = 1;
    opRes = 0;
    vals = randList(len);
    list = createLinkedList(&copyInt, &delInt, &compInt, isUnique);
    
    //First Insertion
    for(i = 0; i < len; i++){
        opRes = appendLinkedList(list, (void*) &vals[i]);
        if(list->len != i+1 || !opRes)
            *testRes = 0;
    }
    
    //Seond Insertion
    free(vals);
    vals = randList(len);
    for(i = 0; i < len; i++){
        opRes = appendLinkedList(list, (void*) &vals[i]);
        if(isUnique){
            if(list->len != len || opRes)
                *testRes = 0;
        } else{
            if(list->len != len + i + 1 || !opRes)
                *testRes = 0;
        }
    }
    
    //First Removal
    for(i = 0; i < len; i++){
        opRes = removeLinkedList(list, (void*) &i);
        if(isUnique){
            if(list->len != len-i-1 || !opRes)
                *testRes = 0;
        } else{
            if(list->len != 2*(len-i-1) || !opRes)
                *testRes = 0;
        }
    }
    
    //Second Removal
    for(i = 0; i < len; i++){
        opRes = removeLinkedList(list, (void*) &i);
        if(list->len != 0 || opRes)
            *testRes = 0;
    }

    flushLinkedList(list);
    free(vals);
}

int linkedListTest(int repeat_cnt, int len){
    int testRes, i;
    
    for(i = 0; i < repeat_cnt; i++){
        testRes = 0;
        insertRemoveTestLinkedList(len, 1, &testRes);
        if(testRes)
            printf("UNIQUE MODE SUCCESS.\n");
        else
            printf("UNIQUE MODE FAILURE.\n");
        
        insertRemoveTestLinkedList(len, 0, &testRes);
        if(testRes)
            printf("NON-UNIQUE MODE SUCCESS.\n");
        else
            printf("NON-UNIQUE MODE FAILURE.\n");
    }
    
    return 0;
}
