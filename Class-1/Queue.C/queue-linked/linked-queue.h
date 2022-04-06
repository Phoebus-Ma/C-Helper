/**
 * C data structure linked queue example.
 * 
 * License - MIT.
*/

#ifndef __LINKED_QUEUE_H__
#define __LINKED_QUEUE_H__


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct _LINKQUEUE {
    int data;
    struct _LINKQUEUE *next;
} LINKQUEUE, *LPLINKQUEUE;

typedef struct _QUEUECURSOR {
    LPLINKQUEUE front, rear;
} QUEUECURSOR, *LPQUEUECURSOR;


bool linkqueue_isempty (LPQUEUECURSOR lpcursor);
int linkqueue_put      (LPQUEUECURSOR lpcursor, int data);
int linkqueue_get      (LPQUEUECURSOR lpcursor, int *data);
int linkqueue_init     (LPQUEUECURSOR *lpcursor);
int linkqueue_clear    (LPQUEUECURSOR lpcursor);


#endif /* __LINKED_QUEUE_H__ */
