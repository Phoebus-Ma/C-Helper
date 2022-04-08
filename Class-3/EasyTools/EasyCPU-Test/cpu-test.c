/**
 * Module Name:
 *      cpu-test.c
 * 
 * Abstract:
 *      Easy CPU Test.
 * 
 * License - MIT
*/


#include <stdlib.h>
#include <sys/time.h>

#include <pthread.h>

#include "cpu-test.h"


/**
 * GetTickCount - millisecond time.
*/
long GetTickCount(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);

    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

/**
 * easy_flops_handler - flops test handler.
*/
void *easy_flops_handler(void *lpParam)
{
    int nloops = *(int *)lpParam;

    int i = -1,
        j = -1,
        k = -1;

    double temValue = 0;

    volatile double random_buf[MAX_TEST_LENGHT] = {
        95.7797,    175.2475,   103.3413,   22.8105,
        52.5641,    49.3812,    175.1631,   43.9449,
        223.3421,   156.8970,   310.1342,   34.4141,
        163.3211,   275.4511,   232.4866,   79.2518,
        105.1021,   73.4432,    99.4024,    35.3568,
        34.8089,    295.2115,   6.2299,     233.6851,
        136.5720,   192.1421,   176.5191,   83.8560,
        149.8046,   229.6326,   161.3105,   193.8751
    };

    volatile double random_num[MAX_TEST_LENGHT] = {
        529.1613,   992.5802,   358.4822,   378.5829,
        737.3104,   594.3224,   539.2577,   246.4940,
        664.4583,   400.4281,   371.4413,   873.2190,
        715.4557,   582.4671,   771.7804,   437.9065,
        473.7502,   935.4474,   415.2539,   730.2243,
        301.9403,   277.9416,   850.5141,   738.2836,
        344.7338,   704.2637,   476.5231,   783.6878,
        968.5662,   974.2615,   586.9085,   985.8523
    };

    for (i = 0; i < nloops; i++) {
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

    return NULL;
}

/**
 * easy_cpu_test_flops - flops test.
*/
double easy_cpu_test_flops(int num_thd, int num_loops)
{
    int i   = -1,
        ret = -1;

    long time_start = 0,
        time_end   = 0,
        time_total = 0;

    double iops_score = 0;

    pthread_t *tid = NULL;

    tid = (pthread_t *)malloc(sizeof(pthread_t) * num_thd);

    time_start = GetTickCount();

    for (i = 0; i < num_thd; i++) {
        ret = pthread_create(&tid[i], NULL, easy_flops_handler, &num_loops);
        if (0 != ret) {
            goto err_thd;
        }
    }

    for (i = 0; i < num_thd; i++)
        pthread_join(tid[i], NULL);

    time_end = GetTickCount();

    free(tid);

    /* calculate iops score. */
    time_total = time_end - time_start;
    time_total /= num_loops;

    /* time_total is ms, iops_score * 1000. */
    iops_score = num_thd * OP_COUNT * 1000 / time_total;

    return iops_score;

err_thd:
    return -1;
}

/**
 * easy_iops_handler - iops test handler.
*/
void *easy_iops_handler(void *lpParam)
{
    int nloops = *(int *)lpParam;

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

    for (i = 0; i < nloops; i++) {
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

    return NULL;
}

/**
 * easy_cpu_test_iops - iops test.
*/
double easy_cpu_test_iops(int num_thd, int num_loops)
{
    int i   = -1,
        ret = -1;

    long time_start = 0,
        time_end   = 0,
        time_total = 0;

    double iops_score = 0;

    pthread_t *tid = NULL;

    tid = (pthread_t *)malloc(sizeof(pthread_t) * num_thd);

    time_start = GetTickCount();

    for (i = 0; i < num_thd; i++) {
        ret = pthread_create(&tid[i], NULL, easy_iops_handler, &num_loops);
        if (0 != ret) {
            goto err_thd;
        }
    }

    for (i = 0; i < num_thd; i++)
        pthread_join(tid[i], NULL);

    time_end = GetTickCount();

    free(tid);

    /* calculate iops score. */
    time_total = time_end - time_start;
    time_total /= num_loops;

    /* time_total is ms, iops_score * 1000. */
    iops_score = num_thd * OP_COUNT * 1000 / time_total;

    return iops_score;

err_thd:
    return -1;
}

/**
 * easy_cpu_test - cpu performance score.
*/
int easy_cpu_test(int num_cpu, LPEASY_CPU_SCORE pScore)
{
    pScore->single_int      = easy_cpu_test_iops(1, 100);
    pScore->multi_int       = easy_cpu_test_iops(num_cpu, 100);
    pScore->single_float    = easy_cpu_test_flops(1, 100);
    pScore->multi_float     = easy_cpu_test_flops(num_cpu, 100);

    return 0;
}
