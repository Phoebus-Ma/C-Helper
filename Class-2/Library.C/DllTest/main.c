/**
 * C create and use dyunamic link library example.
 * 
 * License - MIT.
*/

#include <stdio.h>
#include <dlfcn.h>

#include "calculate.h"


#define MAX_FUNC_COUNT              5
#define DYNAMIC_LIB_NAME            "./calculate.so"


/* Define global function handle. */
CALCULATE_ADD calculate_add = NULL;
CALCULATE_SUB calculate_sub = NULL;
CALCULATE_MUL calculate_mul = NULL;
CALCULATE_DIV calculate_div = NULL;
CALCULATE_MOD calculate_mod = NULL;


/**
 * dll_load - Load dynamic link library.
*/
int dll_load(void *lib_handler)
{
    char *errnoInfo = NULL;

    /* 1. Open dynamic link library. */
    lib_handler = dlopen(DYNAMIC_LIB_NAME, RTLD_LAZY);
    if (!lib_handler) {
        perror("dlopen");
        goto out_open;
    }

    /* 2. Parse function from handler. */
    calculate_add = (CALCULATE_ADD)dlsym(lib_handler, CALCULATE_API_ADD);
    errnoInfo = dlerror();
    if (NULL != errnoInfo) {
        perror("dlsym");
        goto out_dll;
    }

    calculate_sub = (CALCULATE_SUB)dlsym(lib_handler, CALCULATE_API_SUB);
    errnoInfo = dlerror();
    if (NULL != errnoInfo) {
        perror("dlsym");
        goto out_dll;
    }

    calculate_mul = (CALCULATE_MUL)dlsym(lib_handler, CALCULATE_API_MUL);
    errnoInfo = dlerror();
    if (NULL != errnoInfo) {
        perror("dlsym");
        goto out_dll;
    }

    calculate_div = (CALCULATE_DIV)dlsym(lib_handler, CALCULATE_API_DIV);
    errnoInfo = dlerror();
    if (NULL != errnoInfo) {
        perror("dlsym");
        goto out_dll;
    }

    calculate_mod = (CALCULATE_MOD)dlsym(lib_handler, CALCULATE_API_MOD);
    errnoInfo = dlerror();
    if (NULL != errnoInfo) {
        perror("dlsym");
        goto out_dll;
    }

    return 0;

out_dll:
    /* 3.Close dll file. */
    dlclose(lib_handler);
    lib_handler = NULL;

out_open:
    return -1;
}

/**
 * Main function.
*/
int main(void)
{
    int x = 11, y = 5;
    void *lib_handler = NULL;

    dll_load(lib_handler);

    printf("Add: %d.\n", calculate_add(x, y));
    printf("Sub: %d.\n", calculate_sub(x, y));
    printf("Mul: %d.\n", calculate_mul(x, y));
    printf("Div: %d.\n", calculate_div(x, y));
    printf("Mod: %d.\n", calculate_mod(x, y));

    if (NULL != lib_handler)
        dlclose(lib_handler);

    return 0;
}
