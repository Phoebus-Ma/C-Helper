/**
 * Module Name:
 *      main.c
 * 
 * Abstract:
 *      Easy CPU Test.
 * 
 * License - MIT
*/


#include <stdio.h>

#include "cpu-test.h"



int main(void)
{
    EASY_CPU_SCORE cpu_score;

    easy_cpu_test(8, &cpu_score);

    printf("The CPU Performance Score:\n");
    printf("Single-core integer: %.2lf.\n", cpu_score.single_int);
    printf("multi-core integer: %.2lf.\n", cpu_score.multi_int);
    printf("Single-core float: %.2lf.\n", cpu_score.single_float);
    printf("multi-core float: %.2lf.\n", cpu_score.multi_float);

    return 0;
}
