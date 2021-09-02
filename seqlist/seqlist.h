/**
 * License - MIT.
*/

#ifndef __SEQLIST_H__
#define __SEQLIST_H__

#include <stdio.h>
#include <stdlib.h>

#define MAX_DATA_SIZE           10

typedef struct _SEQLIST {
    int data[MAX_DATA_SIZE];
    int last_index;
} SEQLIST, *LPSEQLIST;


int seqlist_isempty (LPSEQLIST lplist);
int seqlist_isfull  (LPSEQLIST lplist);
int seqlist_insert  (LPSEQLIST lplist, int index, int data);
int seqlist_del     (LPSEQLIST lplist, int index);
int seqlist_init    (LPSEQLIST *lpHead);
int seqlist_exit    (LPSEQLIST lpHead);

#endif /* __SEQLIST_H__ */
