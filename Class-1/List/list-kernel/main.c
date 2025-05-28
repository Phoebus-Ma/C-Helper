/**
 * C data structure kernel linked list example.
 * 
 * License - MIT.
*/

#include <stdio.h>
#include <stdlib.h>

#include "list.h"


#define MAX_TEST_NUM                10


typedef struct _TESTDATA {
    int data;
    struct list_head list;
} TESTDATA, *LPTESTDATA;


/**
 * test_show - Display data.
*/
int test_show(LPTESTDATA lphead)
{
    LPTESTDATA tmp = NULL;

    list_for_each_entry(tmp, &lphead->list, list)
        printf("%d ", tmp->data);

    printf("\n");

    return 0;
}


/**
 * test_create - Create kernel linked list.
*/
int test_create(LPTESTDATA lphead)
{
    LPTESTDATA node;
    int buf[MAX_TEST_NUM] = {92, 26, 35, 82, 57, 46, 50, 3, 22, 81};

    for (int i = 0; i < MAX_TEST_NUM; i++) {
        node = (LPTESTDATA) malloc(sizeof(TESTDATA));

        if (NULL == node) {
            printf("Error in create.\n");
            return -1;
        }

        node->data = buf[i];

        list_add_tail(&node->list, &lphead->list);
    }

    return 0;
}


/**
 * test_init - Initialize kernel linked list.
*/
int test_init(LPTESTDATA *lphead)
{
    *lphead = (LPTESTDATA) malloc(sizeof(TESTDATA));

    if (NULL == *lphead) {
        printf("Error in init.\n");
        return -1;
    }

    INIT_LIST_HEAD(&(*lphead)->list);

    return 0;
}


/**
 * test_clear - Clear kernel linked list data.
*/
int test_clear(LPTESTDATA lphead)
{
    LPTESTDATA pos = NULL, n = NULL;

    list_for_each_entry_safe(pos, n, &lphead->list, list) {
        list_del(&pos->list);

        free(pos);
    }

    free(lphead);

    pos     = NULL;
    n       = NULL;
    lphead  = NULL;

    return 0;
}


/**
 * Main function.
*/
int main(void)
{
    LPTESTDATA lphead;

    test_init(&lphead);

    test_create(lphead);

    test_show(lphead);

    test_clear(lphead);

    return 0;
}
