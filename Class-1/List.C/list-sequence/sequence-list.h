/**
 * C data structure sequence list example.
 * 
 * License - MIT.
*/

#ifndef __SEQUENCE_LIST_H__
#define __SEQUENCE_LIST_H__


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_DATA_SIZE           10

typedef struct _SEQLIST {
    int data[MAX_DATA_SIZE];
    int last_index;
} SEQLIST, *LPSEQLIST;


bool seqlist_isempty (LPSEQLIST lplist);
bool seqlist_isfull  (LPSEQLIST lplist);
int seqlist_insert  (LPSEQLIST lplist, int index, int data);
int seqlist_del     (LPSEQLIST lplist, int index);
int seqlist_init    (LPSEQLIST *lpHead);
int seqlist_clear   (LPSEQLIST lpHead);


#endif /* __SEQUENCE_LIST_H__ */
