/**
 * License - MIT.
*/

#include <stdio.h>
#include <stdlib.h>

#include "singlelist.h"

#define MAX_TEST_NUM            5


/**
 * test_show - Show the singly list data.
*/
int test_show(LPSINGLYLIST lpHead)
{
    LPSINGLYLIST pos;

    for (pos = lpHead->next; pos != NULL; pos = pos->next)
        printf("%d ", pos->data);

    printf("\n");

    return 0;
}

/**
 * test_sort - Sort the data.
*/
int test_sort(LPSINGLYLIST lpHead)
{
    LPSINGLYLIST pos, tmp;

    pos = lpHead->next;
    lpHead->next = NULL;

    while (pos != NULL)
    {
        tmp = pos;
        pos = pos->next;

        singlylist_insert(lpHead, tmp);
    }

    return 0;
}

/**
 * test_create - Create singly list example.
*/
int test_create(LPSINGLYLIST lpHead)
{
    int i;
    LPSINGLYLIST newNode, tmp = lpHead;

    for (i = 0; i < MAX_TEST_NUM; i++) {
        newNode = (LPSINGLYLIST)malloc(sizeof(SINGLYLIST));
        if (NULL == newNode) {
            return -1;
        }

        newNode->data = i + 1;
        singlylist_insert(tmp, newNode);
        tmp = tmp->next;
    }

    return 0;
}

/**
 * Reverse sort data: 1,2,3,4,5 --> 5,4,3,2,1
*/
int main(void)
{
    LPSINGLYLIST lphead;

    singlylist_init(&lphead);

    test_create(lphead);
    test_show(lphead);
    test_sort(lphead);
    test_show(lphead);

    singlylist_exit(lphead);

    return 0;
}
