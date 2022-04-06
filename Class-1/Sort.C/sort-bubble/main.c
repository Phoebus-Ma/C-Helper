/**
 * C data structure bubble sort example.
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
 * bubble_sort - Bubble sort.
*/
int bubble_sort(int *buf, int len)
{
    int i   = -1,
        j   = -1,
        tmp = -1;

    for (i = 0; i < len - 1; i++) {
        for (j = 0; j < len - 1 - i; j++) {
            if (buf[j] > buf[j + 1]) {
                tmp         = buf[j];
                buf[j]      = buf[j + 1];
                buf[j + 1]  = tmp;
            }
        }
    }

    return 0;
}


/**
 * Main function.
*/
int main(void)
{
    int i = 0;
    int buf[] = {27, 13, 18, 29, 74, 73, 50, 65, 97, 36};
    int len = sizeof(buf) / sizeof(int);

    printf("The original array:\n");
    DISPLAY_ARRAY(i, buf, len);

    bubble_sort(buf, len);

    printf("The sort array:\n");
    DISPLAY_ARRAY(i, buf, len);

    return 0;
}
