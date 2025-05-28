/**
 * C data structure sequence queue example.
 * 
 * License - MIT.
*/

#include <stdio.h>

#include "sequence-queue.h"


/**
 * queue_test - Use queue test example.
*/
int queue_test(LPSEQUEUE lpqueue, int buf[], int len)
{
    int i = 0;
    int data = 0;

    printf("Put data: ");

    for (i = 0; i < len; i++) {
        sequeue_put(lpqueue, buf[i]);
        printf("%d ", buf[i]);
    }

    printf("\nGet data: ");

    for (i = 0; i < len; i++) {
        sequeue_get(lpqueue, &data);
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
    LPSEQUEUE sequeue = NULL;

    sequeue_init(&sequeue);

    queue_test(sequeue, buf, 5);

    sequeue_clear(sequeue);

    return 0;
}
