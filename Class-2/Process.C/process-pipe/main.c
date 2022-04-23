/**
 * C use process pipe communication example.
 * 
 * License - MIT.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define MAX_BUF_LEN                 128


/**
 * Main function.
*/
int main(void)
{
    int len = 0;
    pid_t pid = -1;
    int fd[2] = { 0 };

    char read_buf[MAX_BUF_LEN + 1] = { 0 };

    /**
     * Create unnamed pipe.
     *  
     * fd[0] is read pipe.
     * fd[1] is write pipe.
     * 
     * Note: 
     * 1. Half duplex communication.
     * 2. Processes can communicate using unnamed pipes only if they are related.
     * 
     * So, if you want need duplex communication, you need create two pipe.
    */
    if (0 > pipe(fd)) {
        printf("Error in pipe.\n");
        goto out_pipe;
    }

    /* Create child process. */
    pid = fork();

    if (0 > pid) {
        printf("Error in fork.\n");
        goto out_fork;
    }
    /* Child process. */
    else if (0 == pid) {
        /* Receive message. */
        close(fd[1]);

        len = read(fd[0], read_buf, MAX_BUF_LEN);
        close(fd[0]);

        /* '\0' == 0, '0' == 48. */
        read_buf[len] = 0;
        printf("Child process receive: %s.\n", read_buf);

        exit(0);
    }
    /* Parent process. */
    else {
        /* Send message. */
        close(fd[0]);

        printf("Parent process send: Hello.\n");
        write(fd[1], "Hello", 5);

        close(fd[1]);
    }

    return 0;

out_fork:
out_pipe:
    return -1;
}
