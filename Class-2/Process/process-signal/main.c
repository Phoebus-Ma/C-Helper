/**
 * C use process signal communication example.
 * 
 * License - MIT.
*/

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MAX_CHILD_PROC               2

/**
 * Console
 * $ kill -l
 * 
 * 1) SIGHUP       2) SIGINT       3) SIGQUIT      4) SIGILL       5) SIGTRAP
 * 6) SIGABRT      7) SIGBUS       8) SIGFPE       9) SIGKILL      10) SIGUSR1
 * 11) SIGSEGV     12) SIGUSR2     13) SIGPIPE     14) SIGALRM     15) SIGTERM
 * 16) SIGSTKFLT   17) SIGCHLD     18) SIGCONT     19) SIGSTOP     20) SIGTSTP
 * 21) SIGTTIN     22) SIGTTOU     23) SIGURG      24) SIGXCPU     25) SIGXFSZ
 * 26) SIGVTALRM   27) SIGPROF     28) SIGWINCH    29) SIGIO       30) SIGPWR
 * 31) SIGSYS      34) SIGRTMIN    35) SIGRTMIN+1  36) SIGRTMIN+2  37) SIGRTMIN+3
 * 38) SIGRTMIN+4  39) SIGRTMIN+5  40) SIGRTMIN+6  41) SIGRTMIN+7  42) SIGRTMIN+8
 * 43) SIGRTMIN+9  44) SIGRTMIN+10 45) SIGRTMIN+11 46) SIGRTMIN+12 47) SIGRTMIN+13
 * 48) SIGRTMIN+14 49) SIGRTMIN+15 50) SIGRTMAX-14 51) SIGRTMAX-13 52) SIGRTMAX-12
 * 53) SIGRTMAX-11 54) SIGRTMAX-10 55) SIGRTMAX-9  56) SIGRTMAX-8  57) SIGRTMAX-7
 * 58) SIGRTMAX-6  59) SIGRTMAX-5  60) SIGRTMAX-4  61) SIGRTMAX-3  62) SIGRTMAX-2
 * 63) SIGRTMAX-1  64) SIGRTMAX
*/

/**
 * signal_handler2 - signal receive handler.
*/
void signal_handler2(int signo, siginfo_t *info, void *context)
{
    printf("Receive signal number %d from pid: %d.\n", signo, info->si_pid);
    printf("Reveive value: %d.\n", info->si_value.sival_int);
}

/**
 * signal_handler1 - signal receive handler.
*/
void signal_handler1(int signo)
{
    switch (signo)
    {
        /* SIGUSR1. */
        case 10:
            printf("Receive SIGUSR1.\n");
            break;

        /* SIGXFSZ. */
        case 25:
            printf("Receive SIGXFSZ.\n");
            break;
    
        default:
            break;
    }
}

/**
 * child_function2 - Child process function.
*/
int child_function2(void)
{
    int i = 0;
    struct sigaction action;

    action.sa_flags     = SA_SIGINFO;
    action.sa_sigaction = signal_handler2;

    printf("Child process start, pid: %d, ppid: %d.\n", getpid(), getppid());

    sigaction(SIGUSR1, &action, NULL);
    sigaction(SIGUSR2, &action, NULL);

    for (i = 0; i < 5; i++) {
        printf("Nihao.\n");
        sleep(1);
    }

    printf("Child 2 process end.\n");

    return 0;
}

/**
 * child_function1 - Child process function.
*/
int child_function1(void)
{
    int i = 0;

    printf("Child process start, pid: %d, ppid: %d.\n", getpid(), getppid());

    signal(SIGUSR1, signal_handler1);
    signal(SIGXFSZ, signal_handler1);

    for (i = 0; i < 5; i++) {
        printf("Hello.\n");
        sleep(1);
    }

    printf("Child 1 process end.\n");

    return 0;
}


/**
 * process_function - Process function.
*/
int process_function(pid_t pid[], int len)
{
    union sigval value;

    value.sival_int = 100;

    printf("Parent process start, pid: %d.\n", getpid());

    sleep(2);

    kill(pid[0], SIGUSR1);
    kill(pid[0], SIGXFSZ);

    sleep(2);

    sigqueue(pid[1], SIGUSR1, value);
    sigqueue(pid[1], SIGUSR2, value);

    printf("Parent process end.\n");

    return 0;
}


/**
 * Main function.
*/
int main(void)
{
    int ret = -1;
    pid_t pids[MAX_CHILD_PROC] = { 0 };

    for (int i = 0; i < MAX_CHILD_PROC; i++)
    {
        pids[i] = fork();

        switch (pids[i])
        {
        case -1:
            exit(0);
            break;

        /* child-process */
        case 0:
            if (0 == i) {
                child_function1();
            }
            else if (1 == i) {
                child_function2();
            }

            /* Must be. */
            exit(0);
            break;

        default:
            break;
        }
    }

    /* parent-process */
    process_function(pids, MAX_CHILD_PROC);

    for (int i = 0; i < MAX_CHILD_PROC; i++)
        waitpid(pids[i], &ret, 0);

    return 0;
}
