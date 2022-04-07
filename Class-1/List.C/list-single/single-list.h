/**
 * C data structure single linked list.
 * 
 * License - MIT.
*/

#ifndef __SINGLE_LIST_H__
#define __SINGLE_LIST_H__


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct _SINGLELIST{
    int data;
    struct _SINGLELIST *next;
} SINGLELIST, *LPSINGLELIST;


bool sinlist_empty  (LPSINGLELIST lpHead);
int sinlist_insert  (LPSINGLELIST lpNode, LPSINGLELIST newNode);
int sinlist_del     (LPSINGLELIST lpNode);
int sinlist_init    (LPSINGLELIST *lpHead);
int sinlist_clear   (LPSINGLELIST lpHead);


#endif /* __SINGLE_LIST_H__ */
