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


#define MULTICAST_IP                "224.22.22.222"
#define SERVER_PORT                 65532
#define MAX_CONNECT                 1


/**
 * start_server - Start udp server.
*/
int start_server(int ser_port)
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
    ser_addr.sin_addr.s_addr    = htonl(INADDR_ANY);

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
    int serfd   = -1;
    int len     = -1;
    int ret     = -1;

    char buf[128] = { 0 };
    struct sockaddr_in clt_addr;
    struct ip_mreq multi_addr;

    /* Initialize. */
    len = sizeof(clt_addr);
    memset(&clt_addr, 0, len);

    /* Start udp server. */
    serfd = start_server(SERVER_PORT);

    if (0 > serfd) {
        printf("Error in start server.\n");
        goto out_start;
    }

    /* Initialize multicast data. */
    memset(&multi_addr, 0, len);

    multi_addr.imr_interface.s_addr = htonl(INADDR_ANY);
    multi_addr.imr_multiaddr.s_addr = inet_addr(MULTICAST_IP);

    /* join multicast group. */
    setsockopt(serfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &multi_addr, sizeof(multi_addr));

    printf("UDP server running.\n");

    /* Working */
    ret = recvfrom(serfd, buf, 127, 0, (struct sockaddr *)&clt_addr, (socklen_t *)&len);

    if (ret < 0) {
        printf("Error in recvfrom.\n");
    }

    printf("[Server] client ip: %s, port: %d.\n",
            inet_ntoa(clt_addr.sin_addr), ntohs(clt_addr.sin_port));

    printf("[Server] Recv data: %s.\n", buf);

    ret = recvfrom(serfd, buf, 127, 0, (struct sockaddr *)&clt_addr, (socklen_t *)&len);

    if (ret < 0) {
        printf("Error in recvfrom.\n");
    }

    printf("[Server] Recv data: %s.\n", buf);

    ret = sendto(serfd, "OK", strlen("OK"), 0, (struct sockaddr*)&clt_addr, (socklen_t)len);

    if (0 > ret) {
        printf("Error in sendto.\n");
    }

    sleep(1);

out_start:
    close(serfd);

    return 0;
}
