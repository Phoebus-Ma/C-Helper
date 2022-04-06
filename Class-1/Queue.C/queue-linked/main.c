/**
 * C data structure linked queue example.
 * 
 * License - MIT.
*/

#include <stdio.h>

#include "linked-queue.h"


/**
 * queue_test - Test linked queue example.
*/
int queue_test(LPQUEUECURSOR lpcursor, int buf[], int len)
{
    int i = 0;
    int data = 0;

    printf("Put data: ");

    for (i = 0; i < len; i++) {
        linkqueue_put(lpcursor, buf[i]);
        printf("%d ", buf[i]);
    }

    printf("\nGet data: ");

    for (i = 0; i < len; i++) {
        linkqueue_get(lpcursor, &data);
        printf("%d ", data);
    }

    printf("\n");

    return 0;
}


/**
 * Main function.
*/
int main(void)
{
    int buf[5] = {1, 2, 3, 4, 5};
    LPQUEUECURSOR lpcursor = NULL;

    linkqueue_init(&lpcursor);

    queue_test(lpcursor, buf, 5);

    linkqueue_clear(lpcursor);

    return 0;
}
