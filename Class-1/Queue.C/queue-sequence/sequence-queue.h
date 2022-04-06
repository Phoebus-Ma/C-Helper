/**
 * C data structure linked queue example.
 * 
 * License - MIT.
*/

#ifndef __SEQUENCE_QUEUE_H__
#define __SEQUENCE_QUEUE_H__


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_DATA_SIZE               10

typedef struct _SEQUEUE {
    int data[MAX_DATA_SIZE];
    int front, rear;
} SEQUEUE, *LPSEQUEUE;


bool sequeue_isempty (LPSEQUEUE lpqueue);
bool sequeue_isfull  (LPSEQUEUE lpqueue);
int sequeue_put      (LPSEQUEUE lpqueue, int data);
int sequeue_get      (LPSEQUEUE lpqueue, int *data);
int sequeue_init     (LPSEQUEUE *lpHead);
int sequeue_clear    (LPSEQUEUE lpHead);


#endif /* __SEQUENCE_QUEUE_H__ */
