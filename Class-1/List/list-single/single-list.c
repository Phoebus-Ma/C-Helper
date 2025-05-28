/**
 * C data structure single linked list.
 * 
 * License - MIT.
*/

#include "single-list.h"


/**
 * sinlist_empty - Determine if the list is empty.
*/
bool sinlist_empty(LPSINGLELIST lpHead)
{
    return (NULL == lpHead->next);
}


/**
 * sinlist_insert - Add the specified data at specified node next location.
*/
int sinlist_insert(LPSINGLELIST node, LPSINGLELIST newnode)
{
    newnode->next   = node->next;
    node->next      = newnode;

    return 0;
}


/**
 * sinlist_del - Deletes the specified data by specified node next location.
*/
int sinlist_del(LPSINGLELIST node)
{
    LPSINGLELIST tmp;

    tmp         = node->next;
    node->next  = tmp->next;

    free(tmp);
    tmp = NULL;

    return 0;
}


/**
 * sinlist_init - Initialize single linked list.
*/
int sinlist_init(LPSINGLELIST *lpHead)
{
    *lpHead = (LPSINGLELIST)malloc(sizeof(SINGLELIST));
    if (NULL == *lpHead) {
        return -1;
    }

    (*lpHead)->next = NULL;

    return 0;
}


/**
 * sinlist_clear - clear single linked list.
*/
int sinlist_clear(LPSINGLELIST lpHead)
{
    LPSINGLELIST pos;

    if (!sinlist_empty(lpHead)) {
        for (pos = lpHead; (NULL != pos) && (NULL != pos->next); pos = pos->next)
            sinlist_del(pos);
    }

    pos = NULL;

    free(lpHead);
    lpHead = NULL;

    return 0;
}

