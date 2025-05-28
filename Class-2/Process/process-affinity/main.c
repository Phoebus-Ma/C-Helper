/**
 * C process affinty example.
 * 
 * License - MIT.
*/

#define _GNU_SOURCE
#include <stdio.h>

#include <unistd.h>
#include <sched.h>
#include <sys/types.h>


#define MAX_XXOPS_LOOPS                 500000
#define MAX_TEST_LENGHT                 32


/**
 * process_function - Process working function.
*/
int process_function()
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

    return 0;
}

/**
 * Main function.
*/
int main(void)
{
    int cpu_count = 0;
    u_long bitmask = 0;

    cpu_set_t mask;
    CPU_ZERO(&mask);

    printf("Process test running.\n");

    /* Get processor count. */
    cpu_count = sysconf(_SC_NPROCESSORS_ONLN);
    printf("CPU count: %d.\n", cpu_count);

    /* 0000 0110(b) == 0x06 == cpu id 1 + cpu id 2. */
    CPU_SET(1, &mask);
    CPU_SET(2, &mask);

    /* Set process affinity cpu mask. */
    if (0 > sched_setaffinity(getpid(), sizeof(mask), &mask)) {
        printf("Error in sched_setaffinity.\n");
        return -1;
    }

    CPU_ZERO(&mask);

    /* Get process affinity cpu mask. */
    if (0 > sched_getaffinity(getpid(), sizeof(mask), &mask)) {
        printf("Error in sched_getaffinity.\n");
        return -1;
    }

    for (int i = 0; i < cpu_count; i++) {
        if (CPU_ISSET(i, &mask)) {
            bitmask |= (0x01 << i);
            printf("CPU ID: %d is set.\n", i);
        }
    }

    printf("bitmask: 0x%lx.\n", bitmask);

    /* do work. */
    process_function();

    printf("Process test end.\n");

    return 0;
}
