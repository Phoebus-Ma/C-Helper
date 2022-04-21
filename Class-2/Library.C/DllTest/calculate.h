/**
 * C create and use dynamic link library example.
 * 
 * License - MIT.
*/

#ifndef __CALCULATE_H__
#define __CALCULATE_H__

#include <stdio.h>


#define CALCULATE_API_ADD                   "calc_add"
#define CALCULATE_API_SUB                   "calc_sub"
#define CALCULATE_API_MUL                   "calc_mul"
#define CALCULATE_API_DIV                   "calc_div"
#define CALCULATE_API_MOD                   "calc_mod"

typedef int (*CALCULATE_ADD) (int, int);
typedef int (*CALCULATE_SUB) (int, int);
typedef int (*CALCULATE_MUL) (int, int);
typedef int (*CALCULATE_DIV) (int, int);
typedef int (*CALCULATE_MOD) (int, int);


#endif /* __CALCULATE_H__ */
