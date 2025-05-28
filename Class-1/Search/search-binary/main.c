/**
 * C data structure binary search example.
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
 * binary_search - Binary search.
*/
int binary_search(int *buf, int len, int key)
{
    int low = -1,
        mid = -1,
        high = -1;

    for (low = 0, high = len - 1; low <= high;) {
        mid = (low + high) / 2;

        if (key == buf[mid]) {
            return mid;
        }
        else if (key < buf[mid]) {
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
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
    int buf[] = {9, 10, 13, 28, 34, 36, 38, 63, 85, 97};
    int len = sizeof(buf) / sizeof(int);

    printf("The original array:\n");
    DISPLAY_ARRAY(i, buf, len);

    ret = binary_search(buf, len, key);

    if (0 > ret) {
        printf("Not found key: %d.\n", key);
    }
    else {
        printf("Find key %d at index: %d.\n", key, ret);
    }

    return 0;
}
