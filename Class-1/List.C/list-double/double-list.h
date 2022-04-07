/**
 * C data structure double linked list example.
 * 
 * License - MIT.
*/

#ifndef __DOUBLE_LIST_H__
#define __DOUBLE_LIST_H__


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _DOUBLELIST{
    int data;
    struct _DOUBLELIST *prev, *next;
} DOUBLELIST, *LPDOUBLELIST;


bool doulist_empty      (LPDOUBLELIST lpHead);
int doulist_show        (LPDOUBLELIST lpHead);
int doulist_insert      (LPDOUBLELIST lpHead, LPDOUBLELIST lpNode);
int doulist_insert_tail (LPDOUBLELIST lpHead, LPDOUBLELIST lpNode);
int doulist_del         (LPDOUBLELIST lpNode);
int doulist_init        (LPDOUBLELIST *lpHead);
int doulist_clear       (LPDOUBLELIST lpHead);


#endif /* __DOUBLE_LIST_H__ */
