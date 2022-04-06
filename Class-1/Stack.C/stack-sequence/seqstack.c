/**
 * C data structure sequence stack example. 
 * 
 * License - MIT.
*/

#include "seqstack.h"


/**
 * seqstack_isempty - Determine if the stack is empty.
*/
bool seqstack_isempty(LPSEQSTACK lpstack)
{
    return (-1 == lpstack->top);
}


/**
 * seqstack_isfull - Determine if the stack is full.
*/
bool seqstack_isfull(LPSEQSTACK lpstack)
{
    return ((MAX_DATA_SIZE - 1) == lpstack->top);
}


/**
 * seqstack_push - .
*/
int seqstack_push(LPSEQSTACK lpstack, int data)
{
    /* Determine if sequential stack is full. */
    if (seqstack_isfull(lpstack))
        return -1;

    /* Push data to stack. */
    lpstack->top++;
    lpstack->data[lpstack->top] = data;

    return 0;
}


/**
 * seqstack_pop - .
*/
int seqstack_pop(LPSEQSTACK lpstack, int *data)
{
    /* Determine if sequential stack is empty. */
    if (seqstack_isempty(lpstack))
        return -1;

    /* Pop data from stack. */
    *data = lpstack->data[lpstack->top];
    lpstack->top--;

    return 0;
}


/**
 * seqstack_init - Initialize sequence stack.
*/
int seqstack_init(LPSEQSTACK *lpHead)
{
    /* Allocate memory space. */
    *lpHead = (LPSEQSTACK)malloc(sizeof(SEQSTACK));

    if (NULL == *lpHead) {
        printf("Error in sequence stack init.\n");
        return -1;
    }

    (*lpHead)->top = -1;

    return 0;
}


/**
 * seqstack_clear - Clear sequence stack.
*/
int seqstack_clear(LPSEQSTACK lpHead)
{
    int i = -1;

    while (!seqstack_isempty(lpHead))
    {
        seqstack_pop(lpHead, &i);
    }

    free(lpHead);
    lpHead = NULL;

    return 0;
}

