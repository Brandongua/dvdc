#include <stdlib.h>

#include "intarray.h"

void initIntArray(IntArray *a, int initialSize) {
  a->array = malloc(initialSize * sizeof(int));
  a->used = 0;
  a->len = initialSize;
}

int insertIntArray(IntArray* a, int element) {
  if (a->used == a->len) {
      if(a->len == 0){
          a->len = 1;
      }
      else{
        a->len *= 2;
      }
    void *mem = realloc(a->array, a->len * sizeof(int));
    if (!mem) {
      free(mem);
      return 1;
    }
    a->array = mem;
  }
  a->array[a->used++] = element;
  return 0;
}

void delIntArray(IntArray* a) {
  free(a->array);
  a->array = NULL;
  a->used = a->len = 0;
}
