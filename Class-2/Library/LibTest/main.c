/**
 * C create and use static link library example.
 * 
 * License - MIT.
*/

#include <stdio.h>

#include "calculate.h"

/**
 * Main function.
*/
int main(void)
{
    int x = 11, y = 5;

    printf("Add: %d.\n", calc_add(x, y));
    printf("Sub: %d.\n", calc_sub(x, y));
    printf("Mul: %d.\n", calc_mul(x, y));
    printf("Div: %d.\n", calc_div(x, y));
    printf("Mod: %d.\n", calc_mod(x, y));


    return 0;
}
