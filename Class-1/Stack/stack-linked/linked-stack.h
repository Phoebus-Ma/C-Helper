/**
 * C data structure linked stack example.
 * 
 * License - MIT.
*/

#ifndef __LINKED_STACK_H__
#define __LINKED_STACK_H__


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct _LINKSTACK {
    int data;
    struct _LINKSTACK *next;
} LINKSTACK, *LPLINKSTACK;


bool linkstack_isempty  (LPLINKSTACK lpcursor);
int linkstack_push      (LPLINKSTACK *lpcursor, int data);
int linkstack_pop       (LPLINKSTACK *lpcursor, int *data);
int linkstack_init      (LPLINKSTACK *lpcursor);
int linkstack_clear     (LPLINKSTACK *lpcursor);


#endif /* __LINKED_STACK_H__ */
