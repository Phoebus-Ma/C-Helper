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


/**
 * childproc_function - Child process function.
*/
int childproc_function(void)
{
    int i = 0;

    printf("Child process start, pid: %d, ppid: %d.\n", getpid(), getppid());

    for (i = 0; i < 5; i++) {
        printf("Hello from child process.\n");

        sleep(1);
    }

    printf("Child process end.\n");

    return 0;
}


/**
 * process_function - Process function.
*/
int process_function(pid_t subpid)
{
    int i = 0;

    printf("Parent process start, pid: %d, child pid: %d.\n", getpid(), subpid);

    for (i = 0; i < 5; i++) {
        printf("This parent process.\n");

        sleep(1);
    }

    printf("Parent process end.\n");

    return 0;
}


/**
 * Main function.
*/
int main(void)
{
    pid_t pid = vfork();

    switch (pid)
    {
    case -1:
        exit(0);
        break;

    /* child-process */
    case 0:
        childproc_function();
        exit(0);    // Must be.
        break;
    
    /* parent-process */
    default:
        process_function(pid);
        exit(0);    // Must be.
        break;
    }

    return 0;
}
