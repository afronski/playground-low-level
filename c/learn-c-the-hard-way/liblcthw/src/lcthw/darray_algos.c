#include <lcthw/darray_algos.h>
#include <stdlib.h>

int DArray_qsort(DArray* array, DArray_compare cmp)
{
  qsort(array->contents, DArray_count(array), sizeof(void*), cmp);
  return 0;
}

// WARNING: On Linux you don't have an implementation of heapsort in <stdlib.h>.
int heapsort(void* array, size_t count, size_t size, int (*cmp)(const void*, const void*))
{
  qsort(array, count, size, cmp);
  return 0;
}

int DArray_heapsort(DArray* array, DArray_compare cmp)
{
  return heapsort(array->contents, DArray_count(array), sizeof(void*), cmp);
}

// WARNING: On Linux you don't have an implementation of mergesort in <stdlib.h>.
int mergesort(void* array, size_t count, size_t size, int (*cmp)(const void*, const void*))
{
  qsort(array, count, size, cmp);
  return 0;
}

int DArray_mergesort(DArray* array, DArray_compare cmp)
{
  return mergesort(array->contents, DArray_count(array), sizeof(void*), cmp);
}
