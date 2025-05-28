/**
 * C data structure sequence search example.
 * 
 * License - MIT.
*/

#include <stdio.h>


#define DISPLAY_ARRAY(i, buf, len) \
        do { \
            for (i = 0; i < len; i++) \
                printf("%d ", buf[i]); \
            printf("\n"); \
        } while(0)


/**
 * sequence_search - Sequence search.
*/
int sequence_search(int *buf, int len, int key)
{
    for (int i = 0; i < len; i++) {
        if (key == buf[i])
            return i;
    }

    return -1;
}


/**
 * Main function.
*/
int main(void)
{
    int i = 0;
    int ret = -1;
    int key = 10;
    int buf[] = {83, 21, 28, 47, 69, 10, 43, 33, 5, 41};
    int len = sizeof(buf) / sizeof(int);

    printf("The original array:\n");
    DISPLAY_ARRAY(i, buf, len);

    ret = sequence_search(buf, len, key);

    if (0 > ret) {
        printf("Not found key: %d.\n", key);
    }
    else {
        printf("Find key %d at index: %d.\n", key, ret);
    }

    return 0;
}
