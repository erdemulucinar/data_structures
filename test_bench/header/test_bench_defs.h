#ifndef TEST_BENCH_DEFS_H
#define TEST_BENCH_DEFS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void* copyInt(void *a);
void delInt (void *a);
int compInt(void *a, void *b);
void printInt(void *a);

int* randList(int len);

#endif
