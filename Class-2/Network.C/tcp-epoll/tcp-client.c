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

#include <sys/un.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>


#define SOCKET_PATH                 "/tmp/testepoll.sock"

/**
 * connect_server - Connect server.
*/
int connect_server(void)
{
    int clt_fd = -1;
    struct sockaddr_un ser_addr;

    /* Create socket. */
    clt_fd = socket(AF_UNIX, SOCK_STREAM, 0);

    if (0 > clt_fd) {
        printf("Error in socket.\n");
        goto err_socket;
    }

    /* Connect to server. */
    memset(&ser_addr, 0, sizeof(ser_addr));

    ser_addr.sun_family = AF_UNIX;
    strncpy(ser_addr.sun_path, SOCKET_PATH, strlen(SOCKET_PATH) + 1);

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
    int i = 0;
    int cltfd = -1;

    char test_buf[] = "Hello from client";
    char buf[128] = { 0 };

    cltfd = connect_server();

    if (cltfd < 0) {
        printf("Error in client connect.\n");
        goto err_client;
    }

    for (i = 0; i < 5; i++) {
        write(cltfd, test_buf, strlen(test_buf));

        read(cltfd, buf, 127);

        printf("Client recv: %s.\n", buf);

        sleep(1);
    }

    close(cltfd);

    return 0;

err_client:
    return -1;
}
