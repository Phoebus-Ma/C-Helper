/**
 * Module Name:
 *      cpu-test.h
 * 
 * Abstract:
 *      Easy CPU Test header file.
 * 
 * License - MIT
*/


#ifndef __CPU_TEST_H__
#define __CPU_TEST_H__


#define MAX_XXOPS_LOOPS                     500000
#define MAX_TEST_LENGHT                     32
#define OP_COUNT                            20

typedef struct _EASY_CPU_SCORE {
    double single_int;
    double multi_int;
    double single_float;
    double multi_float;
} EASY_CPU_SCORE, *LPEASY_CPU_SCORE;


double easy_cpu_test_flops(int num_thd, int num_loops);
double easy_cpu_test_iops(int num_thd, int num_loops);
int easy_cpu_test(int num_cpu, LPEASY_CPU_SCORE pScore);


#endif /* __CPU_TEST_H__ */
