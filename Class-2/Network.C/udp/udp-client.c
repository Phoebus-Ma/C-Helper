/**
 * C udp client test example.
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
 * Main function.
*/
int main(void)
{
    int ret = -1;
    int len = -1;
    int cltfd = -1;

    char wbuf[] = "Hello UDP Server";
    char rbuf[128] = { 0 };

    struct sockaddr_in ser_addr;

    /* Create socket. */
    cltfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (0 > cltfd) {
        printf("Error in socket.\n");
        goto err_socket;
    }

    /* Initialize server address. */
    len = sizeof(ser_addr);
    memset(&ser_addr, 0, len);

    ser_addr.sin_family         = AF_INET;
    ser_addr.sin_port           = SERVER_PORT;
    ser_addr.sin_addr.s_addr    = inet_addr(SERVER_IP);

    /* Working. */
    for (int i = 0; i < 5; i++) {
        ret = sendto(cltfd, wbuf, strlen(wbuf), 0, (struct sockaddr*)&ser_addr, (socklen_t)len);

        if (0 > ret) {
            printf("Error in sendto.\n");
            break;
        }

        ret = recvfrom(cltfd, rbuf, 127, 0, (struct sockaddr *)&ser_addr, (socklen_t *)&len);

        if (ret < 0) {
            printf("Error in recvfrom.\n");
            break;
        }

        printf("[Client] Recv data: %s.\n", rbuf);

        sleep(1);
    }

    close(cltfd);

    return 0;

err_socket:
    return -1;
}

