/**
 * C data structure binary tree example.
 * 
 * License - MIT.
*/

#include <stdio.h>

#include "binary-tree.h"


/**
 * Main function.
*/
int main(void)
{
    LPBINTREE lptree = NULL;

    /**
     * Such as: [ABD##E##CF##G##].
    */
    printf("Input data:\n");
    bintree_create(&lptree);

    printf("Preorder traversal.\n");
    bintree_pre_traversal(lptree);

    printf("\nInorder traversal.\n");
    bintree_mid_traversal(lptree);

    printf("\nPostorder traversal.\n");
    bintree_last_traversal(lptree);

    printf("\n");

    bintree_clear(lptree);

    return 0;
}
