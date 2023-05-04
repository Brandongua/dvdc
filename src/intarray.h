#pragma once

typedef struct{
    int* array;
    int len;
    int used;
} IntArray;

void initIntArray(IntArray* a, int initialSize);
int insertIntArray(IntArray* a, int element);
void delIntArray(IntArray* a);
