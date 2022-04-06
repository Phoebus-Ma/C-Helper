/**
 * C data structure sequence sort example.
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
 * binary_sort - Binary sort.
*/
int binary_sort(int *buf, int len)
{
    int i   = -1,
        j   = -1,
        tmp = -1,
        low = -1,
        mid = -1,
        high= -1;

    for (i = 0; i < len; i++) {
        tmp = buf[i];

        for (low = 0, high = i - 1; low <= high;) {
            mid = (low + high) / 2;

            if (tmp > buf[mid])
                low = mid + 1;
            else
                high = mid - 1;
        }

        /* Move data. */
        for (j = i; j > low; j--)
            buf[j] =  buf[j - 1];

        buf[low] = tmp;
    }

    return 0;
}


/**
 * Main function.
*/
int main(void)
{
    int i = 0;
    int buf[] = {30, 99, 85, 11, 75, 57, 59, 15, 78, 67};
    int len = sizeof(buf) / sizeof(int);

    printf("The original array:\n");
    DISPLAY_ARRAY(i, buf, len);

    binary_sort(buf, len);

    printf("The sort array:\n");
    DISPLAY_ARRAY(i, buf, len);

    return 0;
}
