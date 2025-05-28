/**
 * C data structure binary tree example.
 * 
 * License - MIT.
*/

#include "binary-tree.h"


/**
 * bintree_last_traversal - Postorder traversal.
*/
int bintree_last_traversal(LPBINTREE lptree)
{
    if (NULL != lptree) {
        bintree_last_traversal(lptree->lchild);

        bintree_last_traversal(lptree->rchild);

        printf("%c ", lptree->data);
    }

    return 0;
}


/**
 * bintree_mid_traversal - Inorder traversal.
*/
int bintree_mid_traversal(LPBINTREE lptree)
{
    if (NULL != lptree) {
        bintree_mid_traversal(lptree->lchild);

        printf("%c ", lptree->data);

        bintree_mid_traversal(lptree->rchild);
    }

    return 0;
}


/**
 * bintree_pre_traversal - Preorder traversal.
*/
int bintree_pre_traversal(LPBINTREE lptree)
{
    if (NULL != lptree) {
        printf("%c ", lptree->data);

        bintree_pre_traversal(lptree->lchild);

        bintree_pre_traversal(lptree->rchild);
    }

    return 0;
}


/**
 * bintree_init - Create data to binary tree.
*/
int bintree_create(LPBINTREE *lptree)
{
    char data;

    scanf("%c", &data);

    if ('#' == data) {
        *lptree = NULL;
    }
    else {
        *lptree = (LPBINTREE) malloc(sizeof(BINTREE));

        if (NULL == *lptree) {
            printf("Error in create.\n");
            exit(1);
        }

        (*lptree)->data = data;

        bintree_create(&(*lptree)->lchild);

        bintree_create(&(*lptree)->rchild);
    }

    return 0;
}


/**
 * bintree_clear - Delete all data from tree.
*/
int bintree_clear(LPBINTREE lptree)
{
    if (NULL != lptree) {
        bintree_clear(lptree->lchild);

        bintree_clear(lptree->rchild);

        /* 0 == '\0'. */
        lptree->data   = 0;
        lptree->lchild = NULL;
        lptree->rchild = NULL;

        free(lptree);
    }

    return 0;
}
