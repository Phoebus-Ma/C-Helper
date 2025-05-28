/**
 * C show current enviorment variable value.
 * 
 * License - MIT.
*/

#include <stdio.h>

extern char** environ;

/**
 * Main function.
*/
int main(void)
{
    for (int i = 0; NULL != environ[i]; i++)
        printf("%s\n", environ[i]);

    return 0;
}
