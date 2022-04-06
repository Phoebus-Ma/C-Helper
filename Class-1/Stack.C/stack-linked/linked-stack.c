/**
 * C data structure linked stack example.
 * 
 * License - MIT.
*/

#include "linked-stack.h"


/**
 * linkstack_isempty - Determine if the stack is empty.
*/
bool linkstack_isempty(LPLINKSTACK lpcursor)
{
    return (NULL == lpcursor);
}


/**
 * linkstack_push - Push data to stack.
*/
int linkstack_push(LPLINKSTACK *lpcursor, int data)
{
    LPLINKSTACK member = NULL;

    member = (LPLINKSTACK) malloc(sizeof(LINKSTACK));

    if (NULL == member) {
        printf("Error in push.\n");
        return -1;
    }

    member->data = data;
    member->next = *lpcursor;

    *lpcursor = member;

    return 0;
}


/**
 * linkstack_pop - Pop data from stack.
*/
int linkstack_pop(LPLINKSTACK *lpcursor, int *data)
{
    LPLINKSTACK tmp;

    if(linkstack_isempty(*lpcursor)){
        printf("Stack is empty.\n");
        return -1;
    }

    tmp       = *lpcursor;
    *data     = tmp->data;
    *lpcursor = (*lpcursor)->next;

    free(tmp);

    return 0;
}


/**
 * linkstack_init - Initialize linked stack.
*/
int linkstack_init(LPLINKSTACK *lpcursor)
{
    *lpcursor = NULL;

    return 0;
}


/**
 * linkstack_clear - Clear linked stack.
*/
int linkstack_clear(LPLINKSTACK *lpcursor)
{
    int i = -1;

    while (!linkstack_isempty(*lpcursor))
    {
        linkstack_pop(lpcursor, &i);
    }

    *lpcursor = NULL;

    return 0;
}

