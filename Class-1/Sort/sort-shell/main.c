/**
 * C data structure shell sort example.
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
 * shell_sort - Shell sort.
*/
int shell_sort(int *buf, int len)
{
    int i   = -1,
        j   = -1,
        pos = -1,
        tmp = -1;

    for (pos = len / 2; pos > 0; pos /= 2) {
        for (i = pos; i < len; i++) {
            tmp = buf[i];

            for (j = i - pos; j > -1; j -= pos) {
                if (tmp >= buf[j])
                    break;
                else
                    buf[j + pos] = buf[j];
            }

            buf[j + pos] = tmp;
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
    int buf[] = {49, 76, 19, 67, 5, 15, 89, 47, 44, 53};
    int len = sizeof(buf) / sizeof(int);

    printf("The original array:\n");
    DISPLAY_ARRAY(i, buf, len);

    shell_sort(buf, len);

    printf("The sort array:\n");
    DISPLAY_ARRAY(i, buf, len);

    return 0;
}
