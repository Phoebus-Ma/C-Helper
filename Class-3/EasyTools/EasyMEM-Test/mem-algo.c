/**
 * Module Name:
 *      mem-algo.c
 * 
 * Abstract:
 *      Memory test algorithm.
 * 
 * License - MIT.
*/


#include "mem-test.h"


/**
 * easy_mem_test_diff - diff two memory area.
*/
int easy_mem_test_diff(uint32_t *mBuf, uint32_t *mCache, int count)
{
    int i = -1;
    uint32_t *p1 = mBuf;
    uint32_t *p2 = mCache;

    for (i = 0; i < count; i++) {
        if (*p1++ != *p2++)
            return i;
    }

    return 0;
}

/**
 * easy_mem_test_random - Memory is filled with random number.
*/
int easy_mem_test_random(uint32_t *mBuf, uint32_t *mCache, int count)
{
    int i = -1;
    uint32_t *p1 = mBuf;
    uint32_t *p2 = mCache;

    for (i = 0; i < count; i++) {
        *p1++ = *p2++ = EASY_RAND();
    }

    return easy_mem_test_diff(mBuf, mCache, count);
}

/**
 * easy_mem_test_sum - Calculate memory raw data plus random number.
*/
int easy_mem_test_sum(uint32_t *mBuf, uint32_t *mCache, int count)
{
    int i = -1;
    uint32_t *p1 = mBuf;
    uint32_t *p2 = mCache;
    unsigned long temp = EASY_RAND();

    for (i = 0; i < count; i++) {
        *p1++ += temp;
        *p2++ += temp;
    }

    return easy_mem_test_diff(mBuf, mCache, count);
}

/**
 * easy_mem_test_sub - Calculate memory raw data subtract random number.
*/
int easy_mem_test_sub(uint32_t *mBuf, uint32_t *mCache, int count)
{
    int i = -1;
    uint32_t *p1 = mBuf;
    uint32_t *p2 = mCache;
    unsigned long temp = EASY_RAND();

    for (i = 0; i < count; i++) {
        *p1++ -= temp;
        *p2++ -= temp;
    }

    return easy_mem_test_diff(mBuf, mCache, count);
}

/**
 * easy_mem_test_mul - Calculate memory raw data multiply random number.
*/
int easy_mem_test_mul(uint32_t *mBuf, uint32_t *mCache, int count)
{
    int i = -1;
    uint32_t *p1 = mBuf;
    uint32_t *p2 = mCache;
    unsigned long temp = EASY_RAND();

    for (i = 0; i < count; i++) {
        *p1++ *= temp;
        *p2++ *= temp;
    }

    return easy_mem_test_diff(mBuf, mCache, count);
}

/**
 * easy_mem_test_div - Calculate memory raw data divided random number.
*/
int easy_mem_test_div(uint32_t *mBuf, uint32_t *mCache, int count)
{
    int i = -1;
    uint32_t *p1 = mBuf;
    uint32_t *p2 = mCache;
    unsigned long temp = EASY_RAND();

    for (i = 0; i < count; i++) {
        *p1++ /= temp;
        *p2++ /= temp;
    }

    return easy_mem_test_diff(mBuf, mCache, count);
}

/**
 * easy_mem_test_and - Memory raw data and random number logic and calculation.
*/
int easy_mem_test_and(uint32_t *mBuf, uint32_t *mCache, int count)
{
    int i = -1;
    uint32_t *p1 = mBuf;
    uint32_t *p2 = mCache;
    unsigned long temp = EASY_RAND();

    for (i = 0; i < count; i++) {
        *p1++ &= temp;
        *p2++ &= temp;
    }

    return easy_mem_test_diff(mBuf, mCache, count);
}

/**
 * easy_mem_test_or - Memory raw data and random number logic or calculation.
*/
int easy_mem_test_or(uint32_t *mBuf, uint32_t *mCache, int count)
{
    int i = -1;
    uint32_t *p1 = mBuf;
    uint32_t *p2 = mCache;
    unsigned long temp = EASY_RAND();

    for (i = 0; i < count; i++) {
        *p1++ |= temp;
        *p2++ |= temp;
    }

    return easy_mem_test_diff(mBuf, mCache, count);
}

/**
 * easy_mem_test_xor - Memory raw data and random number logic xor calculation.
*/
int easy_mem_test_xor(uint32_t *mBuf, uint32_t *mCache, int count)
{
    int i = -1;
    uint32_t *p1 = mBuf;
    uint32_t *p2 = mCache;
    unsigned long temp = EASY_RAND();

    for (i = 0; i < count; i++) {
        *p1++ ^= temp;
        *p2++ ^= temp;
    }

    return easy_mem_test_diff(mBuf, mCache, count);
}

/**
 * easy_mem_test_xnor - Memory raw data and random number logic xnor calculation.
*/
int easy_mem_test_xnor(uint32_t *mBuf, uint32_t *mCache, int count)
{
    int i = -1;
    uint32_t *p1 = mBuf;
    uint32_t *p2 = mCache;
    unsigned long temp = EASY_RAND();

    for (i = 0; i < count; i++) {
        *p1 = ~(*p1 ^ temp);
        *p2 = ~(*p2 ^ temp);
        p1++;
        p2++;
    }

    return easy_mem_test_diff(mBuf, mCache, count);
}

/**
 * easy_mem_test_polarity - Random numbers and random number flips.
*/
int easy_mem_test_polarity(uint32_t *mBuf, uint32_t *mCache, int count)
{
    int i = -1;
    uint32_t *p1 = mBuf;
    uint32_t *p2 = mCache;
    unsigned long temp = 0;

    for (i = 0; i < count; i++) {
        *p1++ = *p2++ = ((0 == (i % 2)) ? temp : ~temp);
    }

    return easy_mem_test_diff(mBuf, mCache, count);
}

/**
 * easy_mem_test_varPolarity - Variable numbers and variable number flips.
*/
int easy_mem_test_varPolarity(uint32_t *mBuf, uint32_t *mCache, int count)
{
    int i = -1;
    uint32_t *p1 = mBuf;
    uint32_t *p2 = mCache;
    unsigned long temp = 0;

    for (i = 0; i < count; i++) {
        temp = ULWORD(i % 0xFF);
        *p1++ = *p2++ = ((0 == (i % 2)) ? temp : ~temp);
    }

    return easy_mem_test_diff(mBuf, mCache, count);
}

/**
 * easy_mem_test_pipeline - Pipeline data.
*/
int easy_mem_test_pipeline(uint32_t *mBuf, uint32_t *mCache, int count)
{
    int i = -1;
    uint32_t *p1 = mBuf;
    uint32_t *p2 = mCache;
    unsigned long temp = 0;

    for (i = 0; i < count; i++) {
        temp = 1 << (i % ULONGLEN);
        *p1++ = *p2++ = temp;
    }

    return easy_mem_test_diff(mBuf, mCache, count);
}

/**
 * easy_mem_test_negPipeline - Negative pipeline.
*/
int easy_mem_test_negPipeline(uint32_t *mBuf, uint32_t *mCache, int count)
{
    int i = -1;
    uint32_t *p1 = mBuf;
    uint32_t *p2 = mCache;
    unsigned long temp = 0;

    for (i = 0; i < count; i++) {
        temp = 1 << (ULONGLEN - (i % ULONGLEN));
        *p1++ = *p2++ = temp;
    }

    return easy_mem_test_diff(mBuf, mCache, count);
}

/**
 * easy_mem_test_bitstrip - Bit strip.
*/
int easy_mem_test_bitstrip(uint32_t *mBuf, uint32_t *mCache, int count)
{
    int i = -1;
    uint32_t *p1 = mBuf;
    uint32_t *p2 = mCache;
    unsigned long temp = 0;

    for (i = 0; i < count; i++) {
        temp = 1 << (i % ULONGLEN);
        *p1++ = *p2++ = ((0 == (i % 2)) ? temp : ~temp);
    }

    return easy_mem_test_diff(mBuf, mCache, count);
}

/**
 * easy_mem_test_negBitstrip - Negative bit strip.
*/
int easy_mem_test_negBitstrip(uint32_t *mBuf, uint32_t *mCache, int count)
{
    int i = -1;
    uint32_t *p1 = mBuf;
    uint32_t *p2 = mCache;
    unsigned long temp = 0;

    for (i = 0; i < count; i++) {
        temp = 0;
        temp = ~temp;
        temp |= ~(1 << (i % ULONGLEN));
        *p1++ = *p2++ = ((0 == (i % 2)) ? temp : ~temp);
    }

    return easy_mem_test_diff(mBuf, mCache, count);
}
