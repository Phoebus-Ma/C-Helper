/**
 * License - MIT.
*/

#include <stdio.h>
#include <stdlib.h>

#include "singlelist.h"


/**
 * singlylist_empty - Determine if the list is empty.
*/
int singlylist_empty(LPSINGLYLIST lpHead)
{
    return (lpHead->next == NULL);
}

/**
 * singlylist_insert - Add the specified data at specified node next location.
*/
int singlylist_insert(LPSINGLYLIST node, LPSINGLYLIST newnode)
{
    newnode->next = node->next;
    node->next = newnode;

    return 0;
}

/**
 * singlylist_del - Deletes the specified data by specified node next location.
*/
int singlylist_del(LPSINGLYLIST node)
{
    LPSINGLYLIST tmp;

    tmp = node->next;
    node->next = tmp->next;

    free(tmp);
    tmp = NULL;

    return 0;
}

/**
 * singlylist_init - Initialize singly list.
*/
int singlylist_init(LPSINGLYLIST *lpHead)
{
    *lpHead = (LPSINGLYLIST)malloc(sizeof(SINGLYLIST));
    if (NULL == *lpHead) {
        return -1;
    }

    (*lpHead)->next = NULL;

    return 0;
}

/**
 * singlylist_exit - clear singly list.
*/
int singlylist_exit(LPSINGLYLIST lpHead)
{
    LPSINGLYLIST pos;

    if (!singlylist_empty(lpHead)) {
        for (pos = lpHead; (pos != NULL) && (pos->next != NULL); pos = pos->next)
            singlylist_del(pos);
    }

    pos = NULL;

    free(lpHead);
    lpHead = NULL;

    return 0;
}
