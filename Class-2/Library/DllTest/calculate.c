/**
 * C create and use dynamic link library example.
 * 
 * License - MIT.
*/

#include "calculate.h"


/**
 * calc_add - additive operation.
*/
int calc_add(int x, int y)
{
    return (x + y);
}

/**
 * calc_sub - subtraction operation.
*/
int calc_sub(int x, int y)
{
    return (x - y);
}

/**
 * calc_mul - multiplication operation.
*/
int calc_mul(int x, int y)
{
    return (x * y);
}

/**
 * calc_div - division operation.
*/
int calc_div(int x, int y)
{
    if (0 == y)
        return -1;

    return (x / y);
}

/**
 * calc_mod - calculating residue.
*/
int calc_mod(int x, int y)
{
    if (0 == y)
        return -1;

    return (x % y);
}
