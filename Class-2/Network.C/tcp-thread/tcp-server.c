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

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>


#define SERVER_IP                   "127.0.0.1"
#define SERVER_PORT                 65533
#define MAX_CONNECT                 8


/**
 * thread_function - Thread function.
*/
void *thread_function(void *param)
{
    int ret         = -1;
    int connfd      = *(int *)param;
    char buf[128]   = { 0 };

    while (1)
    {
        ret = read(connfd, buf, 127);

        if (0 > ret) {
            printf("Error in read.\n");
            goto err_read;
        }
        else if (0 == ret){
            printf("Client exit.\n");
            goto err_read;
        }

        if (!strcmp("quit!!!", buf)) {
            write(connfd, "OK", strlen("OK"));
            break;
        }

        printf("Server %d Recv: %s.\n", connfd, buf);

        write(connfd, "OK", strlen("OK"));

        sleep(1);
    }

err_read:
    close(connfd);

    return (void *)0;
}


/**
 * start_server - Start tcp server.
*/
int start_server(char *ser_ip, int ser_port)
{
    int ser_fd = -1;
    struct sockaddr_in ser_addr;

    /* Create socket. */
    ser_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (ser_fd < 0) {
        printf("Error in socket.\n");
        goto err_socket;
    }

    /* Binding IP and port. */
    memset(&ser_addr, 0, sizeof(ser_addr));

    ser_addr.sin_family         = AF_INET;
    ser_addr.sin_port           = ser_port;
    ser_addr.sin_addr.s_addr    = inet_addr(ser_ip);

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
    int connfd  = -1;
    pthread_t tid;

    /* Start tcp server. */
    serfd = start_server(SERVER_IP, SERVER_PORT);

    if (serfd < -1) {
        printf("Error in start_server.\n");
        goto err_start;
    }

    printf("TCP Sever running.\n");

    while (1)
    {
        connfd = accept(serfd, NULL, NULL);

        ret = pthread_create(&tid, NULL, thread_function, &connfd);

        if (0 != ret) {
            printf("Error in pthread_create.\n");
        }

        printf("Server loop accept.\n");
        sleep(1);
    }
    
    close(serfd);

    return 0;

err_start:
    return -1;
}

