#pragma once
#include "dvd.h"
typedef struct {
    Dvd* array;
    int len;
    int used;
} DvdArray;

void initDvdArray(DvdArray* a, int initialSize);
void popDvdArrayItem(DvdArray* a);
int insertDvdArray(DvdArray* a, Dvd element);
void delDvdArray(DvdArray* a);
