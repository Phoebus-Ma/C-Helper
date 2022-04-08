/**
 * Module Name:
 *      mem-test.h
 * 
 * Abstract:
 *      Memory Test Header file.
 * 
 * License - MIT
*/


#ifndef __MEM_TEST_H__
#define __MEM_TEST_H__

#include <stdlib.h>
#include <stdint.h>

/* (1 << 26) == 64M, sizeof(uint32_t) == 4, total == (64 * 4) MiB. */
#define MAX_DATA_SIZE                       (1 << 26)
#define OP_COUNT                            10
#define RAND32()                            ((uint32_t)rand())
#define RAND64()                            (RAND32() << 32 | RAND32())
#define WORD32(x)                           ((x) | (x) << 8 | (x) << 16 | (x) << 24)

#define EASY_RAND()                         RAND32()
#define ULWORD(x)                           WORD32((x))
#define ULONGLEN                            32


typedef struct _BRISK_MEM_SCORE {
    double mem_score;
    double seq_read_speed;
    double seq_write_speed;
    double rand_read_speed;
    double rand_write_speed;
} BRISK_MEM_SCORE, *LPBRISK_MEM_SCORE;


int easy_mem_test_diff(uint32_t *mBuf, uint32_t *mCache, int count);
int easy_mem_test_random(uint32_t *mBuf, uint32_t *mCache, int count);
int easy_mem_test_sum(uint32_t *mBuf, uint32_t *mCache, int count);
int easy_mem_test_sub(uint32_t *mBuf, uint32_t *mCache, int count);
int easy_mem_test_mul(uint32_t *mBuf, uint32_t *mCache, int count);
int easy_mem_test_div(uint32_t *mBuf, uint32_t *mCache, int count);
int easy_mem_test_and(uint32_t *mBuf, uint32_t *mCache, int count);
int easy_mem_test_or(uint32_t *mBuf, uint32_t *mCache, int count);
int easy_mem_test_xor(uint32_t *mBuf, uint32_t *mCache, int count);
int easy_mem_test_xnor(uint32_t *mBuf, uint32_t *mCache, int count);
int easy_mem_test_polarity(uint32_t *mBuf, uint32_t *mCache, int count);
int easy_mem_test_varPolarity(uint32_t *mBuf, uint32_t *mCache, int count);
int easy_mem_test_pipeline(uint32_t *mBuf, uint32_t *mCache, int count);
int easy_mem_test_negPipeline(uint32_t *mBuf, uint32_t *mCache, int count);
int easy_mem_test_bitstrip(uint32_t *mBuf, uint32_t *mCache, int count);
int easy_mem_test_negBitstrip(uint32_t *mBuf, uint32_t *mCache, int count);

int easy_mem_test_seq_rspeed(uint32_t *mBuf, uint32_t *mCache, int count);
int easy_mem_test_seq_wspeed(uint32_t *mBuf, uint32_t *mCache, int count);
int easy_mem_test_rand_rspeed(uint32_t *mBuf, uint32_t *mCache, int count);
int easy_mem_test_rand_wspeed(uint32_t *mBuf, uint32_t *mCache, int count);
int easy_mem_test(int num_loops, LPBRISK_MEM_SCORE pScore);

#endif /* __MEM_TEST_H__ */
