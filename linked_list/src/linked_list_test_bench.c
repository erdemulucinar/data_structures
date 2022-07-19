#include <stdio.h>
#include "test_bench_defs.h"
#include "linked_list.h"

//Test bench functions
void insertRemoveTestLinkedList(int len, int *testRes){
    LinkedList *list;
    void *searchRes;
    int *vals, i, opRes;
    
    *testRes = 1;
    opRes = 0;
    vals = randList(len);
    list = createLinkedList(&copyInt, &delInt, &compInt);
    
    //Insertion (append)
    for(i = 0; i < len; i++){
        opRes = appendLinkedList(list, (void*) &vals[i]);
        if(list->len != i+1 || !opRes)
            *testRes = 0;
    }
    
    //Search
    free(vals);
    vals = randList(len);
    for(i = 0; i < len; i++){
        searchRes = searchLinkedList(list, (void*) &vals[i]);
        if(!searchRes)
            *testRes = 0;
    }
    
    //First removal
    free(vals);
    vals = randList(len);
    for(i = 0; i < len; i++){
        opRes = removeLinkedList(list, (void*) &vals[i]);
        if(!opRes){
            *testRes = 0;
        }
        searchRes = searchLinkedList(list, (void*) &vals[i]);
        if(searchRes)
            *testRes = 0;
    }
    
    //Second Removal
    free(vals);
    vals = randList(len);
    for(i = 0; i < len; i++){
        opRes = removeLinkedList(list, (void*) &vals[i]);
        if(opRes){
            *testRes = 0;
        }
        searchRes = searchLinkedList(list, (void*) &vals[i]);
        if(searchRes)
            *testRes = 0;
    }

    flushLinkedList(list);
    free(vals);
}

int linkedListTest(int repeat_cnt, int len){
    int testRes, i;
    
    for(i = 0; i < repeat_cnt; i++){
        testRes = 0;
        insertRemoveTestLinkedList(len, &testRes);
        if(testRes)
            printf("TRIAL:%d LINKED LIST TEST SUCCESS.\n",i);
        else
            printf("TRIAL:%d LINKED LIST TEST FAILURE.\n",i);
    }
    
    return 0;
}
