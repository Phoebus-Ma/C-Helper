/**
 * C daemon process example.
 * 
 * License - MIT.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>


#define _PATH_DEVNULL                   "/dev/null"
#define _FILE_PATH                      "/tmp/test.txt"


/**
 * process_function - Process function.
*/
int process_function()
{
    int fd = -1;
    char test_buf[] = "To be NO.1.\n";

    fd = open(_FILE_PATH, O_WRONLY | O_CREAT);

    if (0 > fd) {
        printf("Error in open.\n");
        goto err_open;
    }

    write(fd, test_buf,  strlen(test_buf));

    close(fd);

    return 0;

err_open:
    return -1;
}


/**
 * init_daemon - Initialize daemon process.
*/
int init_daemon()
{
    int fd = -1;

    /* Create process. */
    switch (fork())
    {
    case -1:
        goto err_daemon;
        break;

    case 0:
        break;

    default:
        exit(0);
    }

    /* Set session id. */
    if (-1 == setsid())
        goto err_daemon;

    /* Change work directory. */
    (void)chdir("/");

    /* Redirect. */
    if (-1 != (fd = open(_PATH_DEVNULL, O_RDWR, 0))) {
        (void) dup2(fd, STDIN_FILENO);
        (void) dup2(fd, STDOUT_FILENO);
        (void) dup2(fd, STDERR_FILENO);

        if (2 < fd)
            (void) close(fd);
    }

    return 0;

err_daemon:
    return -1;
}


/**
 * Main function.
*/
int main(void)
{
    /* Set the process to background. */
    init_daemon();

    /* Daemon process target function. */
    process_function();

    return 0;
}
