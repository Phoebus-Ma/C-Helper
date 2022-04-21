/**
 * C thread affinty example.
 * 
 * License - MIT.
*/

#define _GNU_SOURCE
#include <stdio.h>

#include <pthread.h>


#define MAX_XXOPS_LOOPS                 500000
#define MAX_TEST_LENGHT                 32


/**
 * thread_function - Thread function.
*/
void *thread_function(void *param)
{
    int i = -1,
        j = -1,
        k = -1;

    long temValue = 0;

    volatile int random_buf[MAX_TEST_LENGHT] = {
        95,     175,    103,    22,
        52,     49,     175,    43,
        223,    156,    310,    34,
        163,    275,    232,    79,
        105,    73,     99,     35,
        34,     295,    6,      233,
        136,    192,    176,    83,
        149,    229,    161,    193
    };

    volatile int random_num[MAX_TEST_LENGHT] = {
        529,    992,    358,    378,
        737,    594,    539,    246,
        664,    400,    371,    873,
        715,    582,    771,    437,
        473,    935,    415,    730,
        301,    277,    850,    738,
        344,    704,    476,    783,
        968,    974,    586,    985
    };

    for (i = 0; i < 500; i++) {
        for (j = 0; j < MAX_XXOPS_LOOPS; j++) {
            for (k = 0; k < MAX_TEST_LENGHT >> 1; k++) {
                switch (j % 4)
                {
                case 0:
                    temValue = random_buf[k] + random_num[MAX_TEST_LENGHT - k - 1];
                    temValue = random_num[k] * random_buf[MAX_TEST_LENGHT - k - 1];
                    break;

                case 1:
                    temValue = random_buf[k] * random_num[MAX_TEST_LENGHT - k - 1];
                    temValue = random_num[k] + random_buf[MAX_TEST_LENGHT - k - 1];
                    break;

                case 2:
                    temValue = random_buf[k * 2] + random_num[MAX_TEST_LENGHT - (k * 2) - 1];
                    temValue = random_num[k * 2] * random_buf[MAX_TEST_LENGHT - (k * 2) - 1];
                    break;

                case 3:
                    temValue = random_buf[k * 2] * random_num[MAX_TEST_LENGHT - (k * 2) - 1];
                    temValue = random_num[k * 2] + random_buf[MAX_TEST_LENGHT - (k * 2) - 1];
                    break;

                default:
                    break;
                }
            }
        }
    }

    if (0 < temValue)
        temValue = 0;

    return (void *)0;
}

/**
 * Main function.
*/
int main(void)
{
    int ret = -1;
    unsigned long bitmask = 0;

    pthread_t tid;
    cpu_set_t mask;
    CPU_ZERO(&mask);

    /* Create thread. */
    ret = pthread_create(&tid, NULL, thread_function, NULL);

    if (0 != ret) {
        printf("Error in pthread_create.\n");
        goto err_create;
    }

    /* 0000 0001(b) == 0x01 == cpu id 0. */
    CPU_SET(0, &mask);

    /* Set cpu affinity mask. */
    ret = pthread_setaffinity_np(tid, sizeof(mask), &mask);
    
    if (0 != ret) {
        printf("Error in pthread_setaffinity_np.\n");
        goto err_create;
    }

    CPU_ZERO(&mask);

    /* Get cpu affinity mask. */
    ret = pthread_getaffinity_np(tid, sizeof(mask), &mask);

    if (0 != ret) {
        printf("Error in pthread_getaffinity_np.\n");
        goto err_create;
    }

    for (int i = 0; i < CPU_SETSIZE; i++) {
        if (CPU_ISSET(i, &mask)) {
            bitmask |= (0x01 << i);
            printf("CPU ID: %d is set.\n", i);
        }
    }

    printf("bitmask: 0x%lx.\n", bitmask);

    /* Wait child thread to end. */
    ret = pthread_join(tid, NULL);

    if (0 != ret) {
        printf("Error in pthread_join.\n");
        goto err_create;
    }

    printf("Main thread to end.\n");

    return 0;

err_create:
    return -1;
}
