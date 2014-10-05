#include <lcthw/dbg.h>
#include <lcthw/bstree.h>
#include <stdlib.h>
#include <lcthw/bstrlib.h>

static int default_compare(void* a, void* b)
{
  return bstrcmp((bstring) a, (bstring) b);
}

BSTree* BSTree_create(BSTree_compare compare)
{
  BSTree* tree = calloc(1, sizeof(BSTree));
  check_mem(tree);

  tree->compare = compare == NULL ? default_compare : compare;

  return tree;

error:
  if (tree) {
    BSTree_destroy(tree);
  }

  return NULL;
}

static int BSTree_destroy_cb(BSTreeNode* node)
{
  free(node);
  return 0;
}

void BSTree_destroy(BSTree* tree)
{
  if (tree) {
    BSTree_traverse(tree, BSTree_destroy_cb);
    free(tree);
  }
}

static inline BSTreeNode* BSTreeNode_create(BSTreeNode* parent, void* key, void* data)
{
  BSTreeNode* node = calloc(1, sizeof(BSTreeNode));
  check_mem(node);

  node->key = key;
  node->data = data;
  node->parent = parent;

  return node;

error:
  return NULL;
}

static inline void BSTree_setnode(BSTree* tree, BSTreeNode* node, void* key, void* data)
{
  int cmp = tree->compare(node->key, key);
  
  if (cmp <= 0) {
    if (node->left) {
      BSTree_setnode(tree, node->left, key, data);
    } else {
      node->left = BSTreeNode_create(node, key, data);
    }
  } else {
    if (node->right) {
      BSTree_setnode(tree, node->right, key, data);
    } else {
      node->right = BSTreeNode_create(node, key, data);
    }
  }
}

int BSTree_set(BSTree* tree, void* key, void* data)
{
  if (tree->root == NULL) {
    // First, so just make it and get out.
    tree->root = BSTreeNode_create(NULL, key, data);
    check_mem(tree->root);
  } else {
    BSTree_setnode(tree, tree->root, key, data);
  }

  return 0;

error:
  return -1;
}

static inline BSTreeNode* BSTree_getnode(BSTree* tree, BSTreeNode* node, void* key)
{
  int cmp = tree->compare(node->key, key);

  if (cmp == 0) {
    return node;
  } else if (cmp < 0) {
    if (node->left) {
      return BSTree_getnode(tree, node->left, key);
    } else {
      return NULL;
    }
  } else {
    if (node->right) {
      return BSTree_getnode(tree, node->right, key);
    } else {
      return NULL;
    }
  }
}

void* BSTree_get(BSTree* tree, void* key)
{
  if (tree->root == NULL) {
    return NULL;
  } else {
    BSTreeNode* node = BSTree_getnode(tree, tree->root, key);
    return node == NULL ? NULL : node->data;
  }
}

static inline int BSTree_traverse_nodes(BSTreeNode* node, BSTree_traverse_cb traverse_cb)
{
  int rc = 0;

  if (node->left) {
    rc = BSTree_traverse_nodes(node->left, traverse_cb);

    if (rc != 0) {
      return rc;
    }
  }

  if (node->right) {
    rc = BSTree_traverse_nodes(node->right, traverse_cb);

    if (rc != 0) {
      return rc;
    }
  }

  return traverse_cb(node);
}

int BSTree_traverse(BSTree* tree, BSTree_traverse_cb traverse_cb)
{
  if (tree->root) {
    return BSTree_traverse_nodes(tree->root, traverse_cb);
  }

  return 0;
}

static inline BSTreeNode* BSTree_find_min(BSTreeNode* node)
{
  while (node->left) {
    node = node->left;
  }

  return node;
}

static inline void BSTree_replace_node_in_parent(BSTree* tree, BSTreeNode* node, BSTreeNode* new_value)
{
  if (node->parent) {
    if (node == node->parent->left) {
      node->parent->left = new_value;
    } else {
      node->parent->right = new_value;
    }
  } else {
    // This is the root so gotta change it.
    tree->root = new_value;
  }

  if (new_value) {
    new_value->parent = node->parent;
  }
}

static inline void BSTree_swap(BSTreeNode* a, BSTreeNode* b)
{
  void* temp = NULL;
  temp = b->key; b->key = a->key; a->key = temp;
  temp = b->data; b->data = a->data; a->data = temp;
}

static inline BSTreeNode* BSTree_node_delete(BSTree* tree, BSTreeNode* node, void* key)
{
  int cmp = tree->compare(node->key, key);

  if (cmp < 0) {
    if (node->left) {
      return BSTree_node_delete(tree, node->left, key);
    } else {
      // Not found.
      return NULL;
    }
  } else if (cmp > 0) {
    if (node->right) {
      return BSTree_node_delete(tree, node->right, key);
    } else {
      // Not found.
      return NULL;
    }
  } else {
    if (node->left && node->right) {
      // Swap this node for the smallest node that is bigger than us.
      BSTreeNode* successor = BSTree_find_min(node->right);
      BSTree_swap(successor, node);

      // This leaves the old successor with possibly right child
      // so it replace it with right child.
      BSTree_replace_node_in_parent(tree, successor, successor->right);

      // Finally it's swaped, so return successor instead of node.
      return successor;
    } else if (node->left) {
      BSTree_replace_node_in_parent(tree, node, node->left);
    } else if (node->right) {
      BSTree_replace_node_in_parent(tree, node, node->right);
    } else {
      BSTree_replace_node_in_parent(tree, node, NULL);
    }

    return node;
  }
}

void* BSTree_delete(BSTree* tree, void* key)
{
  void* data = NULL;
  
  if (tree->root) {
    BSTreeNode* node = BSTree_node_delete(tree, tree->root, key);
    
    if (node) {
      data = node->data;
      free(node);
    }
  }

  return data;
}
