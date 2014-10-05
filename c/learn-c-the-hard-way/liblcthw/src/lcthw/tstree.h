#ifndef _lcthw_tstree_h_
#define _lcthw_tstree_h_

#include <stdlib.h>
#include <lcthw/darray.h>

typedef struct TSTree {
  char splitchar;

  struct TSTree* low;
  struct TSTree* equal;
  struct TSTree* high;

  void* value;
} TSTree;

TSTree* TSTree_insert(TSTree* node, const char* key, size_t len, void* value);
void TSTree_destroy(TSTree* root);

typedef void (*TSTree_traverse_cb)(void* value, void* data);
void TSTree_traverse(TSTree* node, TSTree_traverse_cb cb, void* data);

void* TSTree_search(TSTree* root, const char* key, size_t len);
void* TSTree_search_prefix(TSTree* root, const char* key, size_t len);

#endif
