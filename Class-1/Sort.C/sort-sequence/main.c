/**
 * C data structure sequence sort example.
 * 
 * License - MIT.
*/

#include <stdio.h>
#include <string.h>


#define DISPLAY_ARRAY(i, buf, len) \
        do { \
            for (i = 0; i < len; i++) \
                printf("%d ", buf[i]); \
            printf("\n"); \
        } while(0)


/**
 * sequence_sort - Sequence sort.
*/
int sequence_sort(int *buf, int len)
{
    int i = -1,
        j = -1,
        tmp = -1;

    for (i = 0; i < len; i++) {
        tmp = buf[i];

        for (j = i - 1; j > -1; j--) {
            if (tmp >= buf[j])
                break;
            else
                buf[j + 1] = buf[j];
        }

        buf[j + 1] = tmp;
    }

    return 0;
}


/**
 * Main function.
*/
int main(void)
{
    int i = 0;
    int buf[] = {11, 13, 65, 85, 59, 27, 54, 98, 51, 75};
    int len = sizeof(buf) / sizeof(int);

    printf("The original array:\n");
    DISPLAY_ARRAY(i, buf, len);

    sequence_sort(buf, len);

    printf("The sort array:\n");
    DISPLAY_ARRAY(i, buf, len);

    return 0;
}
