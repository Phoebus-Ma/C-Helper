/**
 * C use process exec example.
 * 
 * License - MIT.
*/

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MAX_TEST_COUNT              5


/**
 * process_execvp - Execute FILE, searching in the `PATH' environment variable if it
 *                  contains no slashes, with arguments ARGV and environment from `environ'.
*/
int process_execvp(void)
{
    printf("\n----------Test excevp----------\n");

    char *param[] = {"ls", "-a", "-l", NULL};

    execvp("ls", param);

    return 0;
}

/**
 * process_execv - Execute PATH with arguments ARGV and environment from `environ'.
*/
int process_execv(void)
{
    printf("\n----------Test excev-----------\n");
    
    /* Keep the last member is NULL. */
    char *param[] = {"ls", "-a", "-l", NULL};

    execv("/bin/ls", param);

    return 0;
}

/**
 * process_execle - Execute PATH with all arguments after PATH until a NULL pointer,
 *                  and the argument after that for environment.
*/
int process_execle(void)
{
    printf("\n----------Test excele-----------\n");

    char *param[] = {"TEST1=123", NULL};

    execle("./showenv", "showenv", NULL, param);

    return 0;
}

/**
 * process_execlp - Execute FILE, searching in the `PATH' environment variable if
 *                  it contains no slashes, with all arguments after FILE until a
 *                  NULL pointer and environment from `environ'.
*/
int process_execlp(void)
{
    printf("\n----------Test excelp----------\n");
    execlp("ls", "ls", "-l", NULL);

    return 0;
}

/**
 * process_execl - Execute PATH with all arguments after PATH until
 *                 a NULL pointer and environment from `environ'.
*/
int process_execl(void)
{
    printf("\n----------Test excel-----------\n");

    execl("/bin/ls", "ls", "-l", NULL);

    return 0;
}

int (*exec_func[MAX_TEST_COUNT])(void) = {
    process_execl,
    process_execlp,
    process_execle,
    process_execv,
    process_execvp
};

/**
 * Main function.
*/
int main(void)
{
    int i = 0;
    int ret = -1;
    pid_t pid[MAX_TEST_COUNT] = { 0 };

    for (i = 0; i < MAX_TEST_COUNT; i++) {

        pid[i] = fork();

        if (0 > pid[i]) {
            printf("Error in fork.\n");
        }
        /* Child process. */
        else if (0 == pid[i]) {
            exec_func[i]();
            exit(0);
        }
        /* Parent process. */
        else {
            printf("Parent process: %d.\n", getpid());
            waitpid(pid[i], &ret, 0);
        }
    }

    return 0;
}
