/**
 * C data structure double linked list example.
 * 
 * License - MIT.
*/

#include <stdio.h>

#include "double-list.h"


#define MAX_TEST_NUM                10


/**
 * test_sort - Sort the data.
*/
int test_sort(LPDOUBLELIST lpHead)
{
    LPDOUBLELIST pos, tmp;

    pos = lpHead->prev;

    while (pos != lpHead)
    {
        if (1 == (pos->data % 2)) {
            pos = pos->prev;
        }
        else {
            tmp = pos;
            pos = pos->prev;

            doulist_del(tmp);
            doulist_insert_tail(lpHead, tmp);
        }
    }

    return 0;
}


/**
 * test_create - Create single list example.
*/
int test_create(LPDOUBLELIST lpHead)
{
    int i;
    LPDOUBLELIST newNode;

    for (i = 0; i < MAX_TEST_NUM; i++) {
        newNode = (LPDOUBLELIST) malloc(sizeof(DOUBLELIST));
        if (NULL == newNode) {
            return -1;
        }

        newNode->data = i + 1;
        doulist_insert_tail(lpHead, newNode);
    }

    return 0;
}


/**
 * Main function.
*/
int main(void)
{
    LPDOUBLELIST lphead = NULL;

    doulist_init(&lphead);

    test_create(lphead);
    doulist_show(lphead);

    test_sort(lphead);
    doulist_show(lphead);

    doulist_clear(lphead);

    return 0;
}
