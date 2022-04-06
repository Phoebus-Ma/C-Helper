/**
 * C data structure linked stack example.
 * 
 * License - MIT.
*/

#include <stdio.h>

#include "linked-stack.h"


/**
 * linklist_test - Use linked stack test example.
*/
int stack_test(LPLINKSTACK *lpcursor, int buf[], int len)
{
    int i = 0;
    int data = 0;

    printf("Push data: ");

    for (i = 0; i < len; i++) {
        linkstack_push(lpcursor, buf[i]);
        printf("%d ", buf[i]);
    }

    printf("\nPop data: ");

    for (i = 0; i < len; i++) {
        linkstack_pop(lpcursor, &data);

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
    LPLINKSTACK lpcursor = NULL;

    linkstack_init(&lpcursor);

    stack_test(&lpcursor, buf, 5);

    linkstack_clear(&lpcursor);

    return 0;
}

