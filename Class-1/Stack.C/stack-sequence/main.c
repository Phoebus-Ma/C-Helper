/**
 * C data structure sequence list example. 
 * 
 * License - MIT.
*/

#include <stdio.h>
#include <string.h>

#include "seqstack.h"


/**
 * stack_test - Use stack test example.
*/
int stack_test(LPSEQSTACK lpHead, int buf[], int len)
{
    int i = 0;
    int data = 0;

    for (i = 0; i < len; i++)
        seqstack_push(lpHead, buf[i]);

    for (i = 0; i < len; i++) {
        seqstack_pop(lpHead, &data);

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
    LPSEQSTACK seqhead = NULL;

    seqstack_init(&seqhead);

    stack_test(seqhead, buf, 5);

    seqstack_clear(seqhead);

    return 0;
}

