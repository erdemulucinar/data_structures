#include "test_bench_defs.h"

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
