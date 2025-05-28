/**
 * C tcp server test example.
 * 
 * License - MIT.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <sys/un.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>


#define MAX_CONNECT                 8
#define SOCKET_PATH                 "/tmp/testunix.sock"

/**
 * thread_function - Thread function.
*/
void *thread_function(void *param)
{
    int ret         = -1;
    int cltfd       = *(int *)param;
    char buf[128]   = { 0 };

    while (1)
    {
        ret = read(cltfd, buf, 127);

        if (0 > ret) {
            printf("Error in read.\n");
            goto err_read;
        }
        else if (0 == ret){
            printf("Client exit.\n");
            goto err_read;
        }

        if (!strcmp("quit!!!", buf)) {
            write(cltfd, "OK", strlen("OK"));
            break;
        }

        printf("From client %d Recv: %s.\n", cltfd, buf);

        write(cltfd, "OK", strlen("OK"));

        sleep(1);
    }

err_read:
    close(cltfd);

    return (void *)0;
}


/**
 * start_server - Start tcp server.
*/
int start_server(void)
{
    int ser_fd = -1;
    struct sockaddr_un ser_addr;

    /* Create socket. */
    ser_fd = socket(AF_UNIX, SOCK_STREAM, 0);

    if (ser_fd < 0) {
        printf("Error in socket.\n");
        goto err_socket;
    }

    /* Delete file. */
    unlink(SOCKET_PATH);

    /* Binding IP and port. */
    memset(&ser_addr, 0, sizeof(ser_addr));

    ser_addr.sun_family = AF_UNIX;
    strncpy(ser_addr.sun_path, SOCKET_PATH, strlen(SOCKET_PATH) + 1);

    if (bind(ser_fd, (struct sockaddr *)&ser_addr, sizeof(ser_addr)) < 0) {
        printf("Error in bind.\n");
        goto err_bind;
    }

    /* Listen. */
    if (listen(ser_fd, MAX_CONNECT) < 0) {
        printf("Error in listen.\n");
        goto err_bind;
    }

    return ser_fd;

err_bind:
    close(ser_fd);

err_socket:
    return -1;
}


/**
 * Main function.
*/
int main(void)
{
    int ret     = -1;
    int serfd   = -1;
    int cltfd   = -1;
    pthread_t tid;

    /* Start socket unix server. */
    serfd = start_server();

    if (serfd < -1) {
        printf("Error in start_server.\n");
        goto err_start;
    }

    printf("TCP Sever running.\n");
    printf("Communication node: %s.\n", SOCKET_PATH);
    printf("Press CTRL+C to quit!\n\n");

    while (1)
    {
        cltfd = accept(serfd, NULL, NULL);

        ret = pthread_create(&tid, NULL, thread_function, &cltfd);

        if (0 != ret) {
            printf("Error in pthread_create.\n");
        }

        printf("Connected client: %d, loop accept.\n", cltfd);
        sleep(1);
    }
    
    close(serfd);

    return 0;

err_start:
    return -1;
}
