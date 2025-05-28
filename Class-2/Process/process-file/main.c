/**
 * C process use file communication example.
 *
 * License - MIT.
 */

#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>


#define TEMP_FILE_NAME                  "communication.tmp"


/**
 * child_process_function - Read data from file.
*/
int child_process_function(void)
{
    int fd = -1;
    char buf[32 + 1] = { 0 };

    sleep(1);

    fd = open(TEMP_FILE_NAME, O_RDONLY);

    if (0 > fd) {
        printf("Error in open.");
        return -1;
    }

    read(fd, buf, 32);
    printf("Child process read: %s.\n", buf);

    close(fd);

    return 0;
}

/**
 * parent_process_function - Write data to file.
*/
int parent_process_function(void)
{
    int fd = open(TEMP_FILE_NAME, O_WRONLY | O_CREAT, 0664);

    if (0 > fd) {
        printf("Error in open.");
        return -1;
    }

    printf("Parent process write: Hello.\n");
    write(fd, "Hello", 5 + 1);

    close(fd);

    return 0;
}

/**
 * Main function.
*/
int main(void)
{
    pid_t pid = -1;

    pid = fork();

    switch (pid)
    {
    case -1:
        printf("Error in fork.\n");
        break;

    /* Child process. */
    case 0:
        child_process_function();
        exit(0);
        break;
    
    /* Parent process. */
    default:
        parent_process_function();
        wait(NULL);
        break;
    }

    return 0;
}
