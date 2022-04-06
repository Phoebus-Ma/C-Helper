/**
 * C data structure binary tree example.
 * 
 * License - MIT.
*/

#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct _BINTREE {
    char data;
    struct _BINTREE *lchild, *rchild;
} BINTREE, *LPBINTREE;


int bintree_last_traversal  (LPBINTREE lptree);
int bintree_mid_traversal   (LPBINTREE lptree);
int bintree_pre_traversal   (LPBINTREE lptree);
int bintree_create          (LPBINTREE *lptree);
int bintree_clear           (LPBINTREE lptree);


#endif /* __BINARY_TREE_H__ */
