/**
 * C data structure single linked list example.
 * 
 * License - MIT.
*/

#include <stdio.h>
#include <stdlib.h>

#include "single-list.h"


#define MAX_TEST_NUM            5


/**
 * test_show - Show the single list data.
*/
int test_show(LPSINGLELIST lpHead)
{
    LPSINGLELIST pos;

    for (pos = lpHead->next; pos != NULL; pos = pos->next)
        printf("%d ", pos->data);

    printf("\n");

    return 0;
}


/**
 * test_sort - Sort the data.
*/
int test_sort(LPSINGLELIST lpHead)
{
    LPSINGLELIST pos, tmp;

    pos = lpHead->next;
    lpHead->next = NULL;

    while (pos != NULL)
    {
        tmp = pos;
        pos = pos->next;

        sinlist_insert(lpHead, tmp);
    }

    return 0;
}


/**
 * test_create - Create single list example.
*/
int test_create(LPSINGLELIST lpHead)
{
    int i;
    LPSINGLELIST newNode, tmp = lpHead;

    for (i = 0; i < MAX_TEST_NUM; i++) {
        newNode = (LPSINGLELIST) malloc(sizeof(SINGLELIST));
        if (NULL == newNode) {
            return -1;
        }

        newNode->data = i + 1;
        sinlist_insert(tmp, newNode);
        tmp = tmp->next;
    }

    return 0;
}


/**
 * Reverse sort data: 1,2,3,4,5 --> 5,4,3,2,1
*/
int main(void)
{
    LPSINGLELIST lphead;

    sinlist_init(&lphead);

    test_create(lphead);
    test_show(lphead);
    test_sort(lphead);
    test_show(lphead);

    sinlist_clear(lphead);

    return 0;
}
