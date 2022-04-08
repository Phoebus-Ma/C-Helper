/**
 * Module Name:
 *      main.c
 * 
 * Abstract:
 *      Easy Memory Test.
 * 
 * License - MIT
*/


#include <stdio.h>
#include "mem-test.h"



int main(void)
{
    BRISK_MEM_SCORE mem_score = { 0 };

    easy_mem_test(10, &mem_score);

    printf("The Memory Performance Score:\n");
    printf("sequential write speed: %.2lf MB/s.\n", mem_score.seq_write_speed);
    printf("sequential read speed: %.2lf MB/s.\n", mem_score.seq_read_speed);
    printf("random write speed: %.2lf MB/s.\n", mem_score.rand_write_speed);
    printf("random read speed: %.2lf MB/s.\n", mem_score.rand_read_speed);
    printf("memory score: %.2lf.\n", mem_score.mem_score);

    return 0;
}
