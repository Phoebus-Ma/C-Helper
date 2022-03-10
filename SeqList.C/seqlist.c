/**
 * License - MIT.
*/

#include "seqlist.h"


/**
 * seqlist_isempty - Determine if the table is empty.
*/
int seqlist_isempty(LPSEQLIST lplist)
{
    return (-1 == lplist->last_index);
}

/**
 * seqlist_isfull - Determine if the table is full up.
*/
int seqlist_isfull(LPSEQLIST lplist)
{
    return ((MAX_DATA_SIZE - 1) == lplist->last_index);
}

/**
 * seqlist_insert - Add the specified data  by index.
*/
int seqlist_insert(LPSEQLIST lplist, int index, int data)
{
    int i;

    if ((index < 0) || (index > MAX_DATA_SIZE - 1)) {
        printf("invalid index!\n");
        return -1;
    }

    /* Move the data behind the index. */
    for (i = lplist->last_index; i >= index; i--)
        lplist->data[i + 1] = lplist->data[i];

    /* Insert the data. */
    lplist->data[index] = data;

    /* Update the last index. */
    lplist->last_index++;

    return 0;
}

/**
 * seqlist_del - Deletes the specified data by index.
*/
int seqlist_del(LPSEQLIST lplist, int index)
{
    int i;

    if ((index < 0) || (index > MAX_DATA_SIZE - 1)) {
        printf("invalid index!\n");
        return -1;
    }

    /* Move the data behind the index forward. */
    for (i = index; i < lplist->last_index; i++)
        lplist->data[i] = lplist->data[i + 1];

    /* Update the last index. */
    lplist->last_index--;

    return 0;
}

/**
 * seqlist_init - Initialize sequence list.
*/
int seqlist_init(LPSEQLIST *lpHead)
{
    /* Allocate memory space. */
    *lpHead = (LPSEQLIST)malloc(sizeof(SEQLIST));
    if (NULL == *lpHead) {
        perror("malloc");
        exit(1);
    }

    (*lpHead)->last_index = -1;

    return 0;
}

/**
 * seqlist_exit - clear sequence list.
*/
int seqlist_exit(LPSEQLIST lpHead)
{
    int i = -1;

    if (!seqlist_isempty(lpHead)) {
        for (i = 0; i < lpHead->last_index; i++)
            seqlist_del(lpHead, i);
    }

    free(lpHead);
    lpHead = NULL;

    return 0;
}
