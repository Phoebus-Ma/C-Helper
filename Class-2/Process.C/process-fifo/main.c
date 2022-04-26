/**
 * C use process fifo communication example.
 * 
 * License - MIT.
*/

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>


#define MAX_BUF_LEN                 128


/**
 * Main function.
*/
int main(void)
{
    int len = 0;
    int fd = -1;
    pid_t pid = -1;

    char read_buf[MAX_BUF_LEN + 1] = { 0 };

    /**
     * Creating a named pipe.
     * 
     * Note: 
     * 1. Duplex communication.
     * 2. Processes can communicate with and without relatives.
    */
    if (-1 < access("./test_fifo", F_OK)) {
        remove("./test_fifo");
    }

    if (0 > mkfifo("test_fifo", 0664)) {
        printf("Error in mkfifo.\n");
        goto out_fifo;
    }

    /* Open fifo. */
    fd = open("./test_fifo", O_RDWR);

    if (0 > fd) {
        printf("Error in open.\n");
        goto out_open;
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
        len = read(fd, read_buf, MAX_BUF_LEN);

        /* '\0' == 0, '0' == 48. */
        read_buf[len] = 0;
        printf("Child process receive: %s.\n", read_buf);

        sleep(1);

        /* Send message. */
        printf("Child process send: Nihao.\n");
        write(fd, "Nihao", 5);
    }
    /* Parent process. */
    else {
        /* Send message. */
        printf("Parent process send: Hello.\n");
        write(fd, "Hello", 5);

        sleep(1);

        /* Receive message. */
        len = read(fd, read_buf, MAX_BUF_LEN);

        read_buf[len] = 0;
        printf("Parent process receive: %s.\n", read_buf);
    }

    close(fd);

    return 0;

out_fork:
    close(fd);

out_open:
out_fifo:
    return -1;
}
