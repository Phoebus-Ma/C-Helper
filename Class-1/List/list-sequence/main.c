/**
 * C data structure sequence list example. 
 * 
 * License - MIT.
*/

#include <stdio.h>

#include "sequence-list.h"


/**
 * test_show - Diaplay list data.
*/
void test_show(LPSEQLIST lplist)
{
    int i;

    for (i = 0; i <= lplist->last_index; i++)
        printf("%d ", lplist->data[i]);

    printf("\n");
}


/**
 * Main function.
*/
int main(void)
{
    int i = -1;

    LPSEQLIST lphead;

    seqlist_init(&lphead);

    for (i = 0; i < MAX_DATA_SIZE; i++)
        seqlist_insert(lphead, i, i + 1);

    test_show(lphead);

    seqlist_del(lphead, 3);

    test_show(lphead);

    seqlist_clear(lphead);

    return 0;
}
