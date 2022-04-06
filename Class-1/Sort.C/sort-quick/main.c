/**
 * C data structure quick sort example.
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
 * quick_pass - Quick pass.
*/
int quick_pass(int *buf, int i, int j)
{
    int tmp = buf[i];

    while (i < j)
    {
        while ((i < j) && (tmp <= buf[j]))
            j--;

        if (i < j)
            buf[i] = buf[j];

        while ((i < j) && (tmp >= buf[i]))
            i++;

        if (i < j)
            buf[j] = buf[i];
    }
    
    buf[i] = tmp;

    return i;
}


/**
 * quick_sort - Quick sort.
*/
int quick_sort(int *buf, int low, int high)
{
    int mid = 0;

    if (low < high) {
        mid = quick_pass(buf, low, high);

        quick_sort(buf, low, mid - 1);
        quick_sort(buf, mid + 1, high);
    }

    return 0;
}


/**
 * Main function.
*/
int main(void)
{
    int i = 0;
    int buf[] = {79, 28, 23, 0, 46, 89, 65, 21, 97, 5};
    int len = sizeof(buf) / sizeof(int);

    printf("The original array:\n");
    DISPLAY_ARRAY(i, buf, len);

    quick_sort(buf, 0, len - 1);

    printf("The sort array:\n");
    DISPLAY_ARRAY(i, buf, len);

    return 0;
}
