/**
 * C tcp client test example.
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


/**
 * connect_server - Connect server.
*/
int connect_server(char *ser_ip, int ser_port)
{
    int clt_fd = -1;
    struct sockaddr_in ser_addr;

    /* Create socket. */
    clt_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (0 > clt_fd) {
        printf("Error in socket.\n");
        goto err_socket;
    }

    /* Connect to server. */
    memset(&ser_addr, 0, sizeof(ser_addr));

    ser_addr.sin_family         = AF_INET;
    ser_addr.sin_port           = ser_port;
    ser_addr.sin_addr.s_addr    = inet_addr(ser_ip);

    if (0 > connect(clt_fd, (struct sockaddr *)&ser_addr, sizeof(ser_addr))) {
        printf("Error in connect.\n");
        goto err_connect;
    }

    return clt_fd;

err_connect:
    close(clt_fd);

err_socket:
    return -1;
}


/**
 * Main function.
*/
int main(void)
{
    int cltfd = -1;

    char test_buf[] = "Test for client";

    cltfd = connect_server(SERVER_IP, SERVER_PORT);

    if (cltfd < 0) {
        printf("Error in client connect.\n");
        goto err_client;
    }

    /* Send normal data. */
    write(cltfd, test_buf, strlen(test_buf));
    sleep(1);

    write(cltfd, test_buf, strlen(test_buf));
    sleep(1);

    /* Send out of band data, 1 byte only. */
    send(cltfd, "A", 1, MSG_OOB);

    close(cltfd);

    return 0;

err_client:
    return -1;
}
