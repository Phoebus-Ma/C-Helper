/**
 * License - MIT.
*/

#ifndef __SINGLY_LIST_H__
#define __SINGLY_LIST_H__


typedef struct _SINGLYLIST{
	int data;
	struct _SINGLYLIST *next;
} SINGLYLIST, *LPSINGLYLIST;


int singlylist_empty    (LPSINGLYLIST lpHead);
int singlylist_insert   (LPSINGLYLIST lpNode, LPSINGLYLIST newNode);
int singlylist_del      (LPSINGLYLIST lpNode);
int singlylist_init     (LPSINGLYLIST *lpHead);
int singlylist_exit     (LPSINGLYLIST lpHead);

#endif /* __SINGLY_LIST_H__ */
