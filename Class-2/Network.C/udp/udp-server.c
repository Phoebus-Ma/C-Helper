/**
 * C udp server test example.
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
#define SERVER_PORT                 65532
#define MAX_CONNECT                 8


/**
 * start_server - Start udp server.
*/
int start_server(char *ser_ip, int ser_port)
{
    int ser_fd = -1;
    struct sockaddr_in ser_addr;

    /* Create socket. */
    ser_fd = socket(AF_INET, SOCK_DGRAM, 0);

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
    int serfd = -1;
    int len = -1;
    int ret = -1;
    char buf[128] = { 0 };
    struct sockaddr_in clt_addr;

    /* Initialize. */
    len = sizeof(clt_addr);
    memset(&clt_addr, 0, len);

    /* Start udp server. */
    serfd = start_server(SERVER_IP, SERVER_PORT);

    printf("UDP server running.\n");

    /* Working */
    while (1)
    {
        ret = recvfrom(serfd, buf, 127, 0, (struct sockaddr *)&clt_addr, (socklen_t *)&len);

        if (ret < 0) {
            printf("Error in recvfrom.\n");
            break;
        }

        printf("[Server] client ip: %s, port: %d.\n",
                inet_ntoa(clt_addr.sin_addr), ntohs(clt_addr.sin_port));

        printf("[Server] Recv data: %s.\n", buf);

        ret = sendto(serfd, "OK", strlen("OK"), 0, (struct sockaddr*)&clt_addr, (socklen_t)len);

        if (0 > ret) {
            printf("Error in sendto.\n");
            break;
        }

        sleep(1);
    }

    close(serfd);

    return 0;
}

