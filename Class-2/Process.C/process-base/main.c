/**
 * C data structure sequence list example. 
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

    for (i = 0; i < 10; i++) {
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
    int ret = 0;

    printf("Parent process start, pid: %d, child pid: %d.\n", getpid(), subpid);

    for (i = 0; i < 5; i++) {
        printf("This parent process.\n");

        sleep(1);
    }

    /* Wait for child process to end. */
    wait(&ret);

    printf("Parent process end, child status: %d.\n", WEXITSTATUS(ret));

    return 0;
}


/**
 * Main function.
*/
int main(void)
{
    pid_t pid = fork();

    switch (pid)
    {
    case -1:
        exit(0);
        break;

    case 0:         // child-process
        childproc_function();
        break;
    
    default:        // parent-process
        process_function(pid);
        break;
    }

    return 0;
}
