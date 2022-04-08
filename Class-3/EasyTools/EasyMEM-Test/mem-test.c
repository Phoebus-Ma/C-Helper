/**
 * Module Name:
 *      mem-test.c
 * 
 * Abstract:
 *      Memory Test.
 * 
 * License - MIT
*/


#include <sys/time.h>

#include "mem-test.h"



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
 * easy_mem_test_seq_rspeed - Test memory sequential read speed.
*/
int easy_mem_test_seq_rspeed(uint32_t *mBuf, uint32_t *mCache, int count)
{
    int i = -1;
    uint32_t *p1 = mBuf;
    uint32_t *p2 = mCache;

    for (i = 0; i < count; i++)
        *p2++ = *p1++;

    return 0;
}

/**
 * easy_mem_test_seq_wspeed - Test memory sequential write speed.
*/
int easy_mem_test_seq_wspeed(uint32_t *mBuf, uint32_t *mCache, int count)
{
    int i = -1;
    uint32_t *p1 = mBuf;

    for (i = 0; i < count; i++)
        *p1++ = 0xf0f0f0f0;

    return 0;
}

/**
 * easy_mem_test_rand_rspeed - Test memory random read speed.
*/
int easy_mem_test_rand_rspeed(uint32_t *mBuf, uint32_t *mCache, int count)
{
    int i = -1, times = 0;
    uint32_t *p1 = mBuf;
    uint32_t *p2 = mCache;

    for (i = 0; i < count; i += 4) {
        *p2++ = *p1++;
        times++;
    }

    return times;
}

/**
 * easy_mem_test_rand_wspeed - Test memory random write speed.
*/
int easy_mem_test_rand_wspeed(uint32_t *mBuf, uint32_t *mCache, int count)
{
    int i = -1, times = 0;
    uint32_t *p1 = mBuf;

    for (i = 0; i < count; i += 4) {
        *p1++ = 0xAAAAAAAA;
        times++;
    }

    return times;
}

/**
 * easy_mem_test - Test Memory Score.
*/
int easy_mem_test(int num_loops, LPBRISK_MEM_SCORE pScore)
{
    int i = -1;
    int testlen = MAX_DATA_SIZE >> 1;

    long  time_start = 0,
          time_end   = 0,
          time_total = 0;

    uint32_t *test_data;
    uint32_t *mbuf, *mCache;

    test_data = (uint32_t *)malloc(sizeof(uint32_t) * MAX_DATA_SIZE);
    mbuf = test_data;
    mCache = test_data + testlen;

    srand(0x5733);

    /* 1, Test memory bandwidth. */

    /* 1.1, Calculate sequential write speed. */
    time_start = GetTickCount();
    easy_mem_test_seq_wspeed(mbuf, mCache, testlen);
    time_end = GetTickCount();

    if (!easy_mem_test_diff(mbuf, mCache, testlen)) {
        time_total = time_end - time_start;
        /* MiB */
        pScore->seq_write_speed = (double)((testlen * sizeof(uint32_t) * 1000 / time_total) >> 20);
    }
    else {
        pScore->seq_write_speed = -1;
    }

    /* 1.2, Calculate sequential read speed. */
    time_start = GetTickCount();
    easy_mem_test_seq_rspeed(mbuf, mCache, testlen);
    time_end = GetTickCount();

    if (!easy_mem_test_diff(mbuf, mCache, testlen)) {
        time_total = time_end - time_start;
        pScore->seq_read_speed = (double)((testlen * sizeof(uint32_t) * 1000 / time_total) >> 20);
    }
    else {
        pScore->seq_read_speed = -1;
    }

    /* 1.3, Calculate random write speed. */
    time_start = GetTickCount();
    i = easy_mem_test_rand_wspeed(mbuf, mCache, testlen);
    time_end = GetTickCount();

    if (!easy_mem_test_diff(mbuf, mCache, testlen)) {
        time_total = time_end - time_start;
        pScore->rand_write_speed = (double)((i * sizeof(uint32_t) * 1000 / time_total) >> 20);
    }
    else {
        pScore->rand_write_speed = -1;
    }

    /* 1.4, Calculate random read speed. */
    time_start = GetTickCount();
    i = easy_mem_test_rand_rspeed(mbuf, mCache, testlen);
    time_end = GetTickCount();

    if (!easy_mem_test_diff(mbuf, mCache, testlen)) {
        time_total = time_end - time_start;
        pScore->rand_read_speed = (double)((i * sizeof(uint32_t) * 1000 / time_total) >> 20);
    }
    else {
        pScore->rand_read_speed = -1;
    }

    /* 2, Test memory performance. */
    time_start = GetTickCount();

    for (i = 0; i < num_loops; i++) {
        easy_mem_test_random       (mbuf, mCache, testlen);
        easy_mem_test_sum          (mbuf, mCache, testlen);
        easy_mem_test_sub          (mbuf, mCache, testlen);
        easy_mem_test_mul          (mbuf, mCache, testlen);
        easy_mem_test_div          (mbuf, mCache, testlen);
        easy_mem_test_and          (mbuf, mCache, testlen);
        easy_mem_test_or           (mbuf, mCache, testlen);
        easy_mem_test_xor          (mbuf, mCache, testlen);
        easy_mem_test_xnor         (mbuf, mCache, testlen);
        easy_mem_test_polarity     (mbuf, mCache, testlen);
        easy_mem_test_varPolarity  (mbuf, mCache, testlen);
        easy_mem_test_pipeline     (mbuf, mCache, testlen);
        easy_mem_test_negPipeline  (mbuf, mCache, testlen);
        easy_mem_test_bitstrip     (mbuf, mCache, testlen);
        easy_mem_test_negBitstrip  (mbuf, mCache, testlen);
    }

    time_end = GetTickCount();

    free(test_data);

    /* Calculte Memory Score. */
    time_total = time_end - time_start;
    time_total /= num_loops;

    pScore->mem_score = (double)time_total;
    pScore->mem_score /= OP_COUNT;

    return 0;
}
