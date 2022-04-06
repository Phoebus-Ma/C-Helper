/**
 * C data structure sequence queue example.
 * 
 * License - MIT.
*/

#include "sequence-queue.h"


/**
 * sequeue_isempty - Determine if the queue is empty.
*/
bool sequeue_isempty(LPSEQUEUE lpqueue)
{
    return (lpqueue->front == lpqueue->rear);
}


/**
 * sequeue_isfull - Determine if the queue is full.
*/
bool sequeue_isfull(LPSEQUEUE lpqueue)
{
    return (lpqueue->front == (lpqueue->rear + 1) % MAX_DATA_SIZE);
}


/**
 * sequeue_put - Put data to queue.
*/
int sequeue_put(LPSEQUEUE lpqueue, int data)
{
    /* Determine if sequential stack is full. */
    if (sequeue_isfull(lpqueue))
        return -1;

    /* Put data to stack. */
    lpqueue->rear = (lpqueue->rear + 1) % MAX_DATA_SIZE;
    lpqueue->data[lpqueue->rear] = data;

    return 0;
}


/**
 * sequeue_get - Get data from queue.
*/
int sequeue_get(LPSEQUEUE lpqueue, int *data)
{
    /* Determine if sequential stack is empty. */
    if (sequeue_isempty(lpqueue))
        return -1;

    /* Get data from stack. */
    lpqueue->front = (lpqueue->front + 1) % MAX_DATA_SIZE;
    *data = lpqueue->data[lpqueue->front];

    return 0;
}


/**
 * sequeue_init - Initialize sequence queue.
*/
int sequeue_init(LPSEQUEUE *lpqueue)
{
    /* Allocate memory space. */
    *lpqueue = (LPSEQUEUE) malloc(sizeof(SEQUEUE));

    if (NULL == *lpqueue) {
        printf("Error in queue init.\n");
        return -1;
    }

    (*lpqueue)->front = MAX_DATA_SIZE - 1;
    (*lpqueue)->rear  = MAX_DATA_SIZE - 1;

    return 0;
}


/**
 * sequeue_clear - Clear sequence queue.
*/
int sequeue_clear(LPSEQUEUE lpqueue)
{
    int tmp = -1;

    while (!sequeue_isempty(lpqueue))
    {
        sequeue_get(lpqueue, &tmp);
    }

    free(lpqueue);
    lpqueue = NULL;

    return 0;
}
