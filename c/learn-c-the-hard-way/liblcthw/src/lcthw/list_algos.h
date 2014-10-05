#ifndef _lcthw_list_algos_h_
#define _lcthw_list_algos_h_

#include <lcthw/list.h>

typedef int (*List_compare)(const void* a, const void* b);

int List_bubble_sort(List* list, List_compare cmp);
List* List_merge_sort(List* list, List_compare cmp);

#endif
