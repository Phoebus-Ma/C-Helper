/**
 * C data structure linked queue example.
 * 
 * License - MIT.
*/

#include "linked-queue.h"


/**
 * linkqueue_isempty - Determine if the queue is empty.
*/
bool linkqueue_isempty(LPQUEUECURSOR lpcursor)
{
    return (lpcursor->front == lpcursor->rear);
}


/**
 * linkqueue_put - Put data to queue.
*/
int linkqueue_put(LPQUEUECURSOR lpcursor, int data)
{
    LPLINKQUEUE node = NULL;

    node = (LPLINKQUEUE) malloc(sizeof(LINKQUEUE));

    if (NULL == node) {
        printf("Error in queue put.\n");
        return -1;
    }

    /* Put data to queue. */
    node->data              = data;
    node->next              = lpcursor->rear->next;
    lpcursor->rear->next    = node;
    lpcursor->rear          = lpcursor->rear->next;

    return 0;
}


/**
 * linkqueue_get - Get data from queue.
*/
int linkqueue_get(LPQUEUECURSOR lpcursor, int *data)
{
    LPLINKQUEUE tmp;

    /* Determine if queue is empty. */
    if (linkqueue_isempty(lpcursor))
        return -1;

    /* Get data from queue. */
    tmp             = lpcursor->front;
    lpcursor->front = lpcursor->front->next;
    *data           = lpcursor->front->data;

    free(tmp);

    return 0;
}


/**
 * linkqueue_init - Initialize linked queue.
*/
int linkqueue_init(LPQUEUECURSOR *lpcursor)
{
    /* Allocate cursor memory space. */
    *lpcursor = (LPQUEUECURSOR) malloc(sizeof(QUEUECURSOR));

    if (NULL == *lpcursor) {
        printf("Error in queue init.\n");
        return -1;
    }

    /* Allocate head node memory space. */
    (*lpcursor)->front = (LPLINKQUEUE) malloc(sizeof(LINKQUEUE));

    if (NULL == (*lpcursor)->front) {
        printf("Error in queue init.\n");
        return -1;
    }

    (*lpcursor)->front->next    = NULL;
    (*lpcursor)->rear           = (*lpcursor)->front;

    return 0;
}


/**
 * linkqueue_clear - Clear linked queue.
*/
int linkqueue_clear(LPQUEUECURSOR lpcursor)
{
    int tmp = -1;

    while (!linkqueue_isempty(lpcursor))
    {
        linkqueue_get(lpcursor, &tmp);
    }

    free(lpcursor);
    lpcursor = NULL;

    return 0;
}
