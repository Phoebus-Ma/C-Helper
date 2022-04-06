/**
 * C data structure sequence list example. 
 * 
 * License - MIT.
*/

#ifndef __SEQ_STACK_H__
#define __SEQ_STACK_H__


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_DATA_SIZE               10

typedef struct _SEQSTACK {
    int data[MAX_DATA_SIZE];
    int top;
} SEQSTACK, *LPSEQSTACK;


bool seqstack_isempty (LPSEQSTACK lpstack);
bool seqstack_isfull  (LPSEQSTACK lpstack);
int seqstack_push     (LPSEQSTACK lpstack, int data);
int seqstack_pop      (LPSEQSTACK lpstack, int *data);
int seqstack_init     (LPSEQSTACK *lpHead);
int seqstack_clear    (LPSEQSTACK lpHead);


#endif /* __SEQ_STACK_H__ */
