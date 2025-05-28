/**
 * C data structure double linked list example.
 * 
 * License - MIT.
*/

#include "double-list.h"


/**
 * doulist_empty - Determine if the list is empty.
*/
bool doulist_empty(LPDOUBLELIST lpHead)
{
    return (lpHead == lpHead->next);
}


/**
 * doulist_show - Display list data.
*/
int doulist_show(LPDOUBLELIST lpHead)
{
    LPDOUBLELIST tmp;

    for (tmp = lpHead->next; tmp != lpHead; tmp = tmp->next)
        printf("%d ", tmp->data);

    printf("\n");

    return 0;
}


/**
 * doulist_insert - Add the specified data at specified node next location.
*/
int doulist_insert(LPDOUBLELIST lpHead, LPDOUBLELIST lpNode)
{
    lpNode->next        = lpHead->next;
    lpHead->next->prev  = lpNode;
    lpNode->prev        = lpHead;
    lpHead->next        = lpNode;

    return 0;
}


/**
 * doulist_insert_tail - Insert data to list tail.
*/
int doulist_insert_tail(LPDOUBLELIST lpHead, LPDOUBLELIST lpNode)
{
    lpNode->prev        = lpHead->prev;
    lpHead->prev->next  = lpNode;
    lpNode->next        = lpHead;
    lpHead->prev        = lpNode;

    return 0;
}


/**
 * doulist_del - Deletes the specified data by specified node next location.
*/
int doulist_del(LPDOUBLELIST lpNode)
{
    lpNode->prev->next = lpNode->next;
    lpNode->next->prev = lpNode->prev;

    return 0;
}


/**
 * doulist_init - Initialize double linked list.
*/
int doulist_init(LPDOUBLELIST *lpHead)
{
    *lpHead = (LPDOUBLELIST) malloc(sizeof(DOUBLELIST));
    if (NULL == *lpHead) {
        return -1;
    }

    (*lpHead)->next = *lpHead;
    (*lpHead)->prev = *lpHead;

    return 0;
}


/**
 * doulist_clear - clear double linked list.
*/
int doulist_clear(LPDOUBLELIST lpHead)
{
    LPDOUBLELIST tmp;

    if (!doulist_empty(lpHead)) {
        for (tmp = lpHead->next; tmp != lpHead; tmp = tmp->next) {
            doulist_del(tmp);
            free(tmp);
        }
    }

    tmp = NULL;

    free(lpHead);
    lpHead = NULL;

    return 0;
}
