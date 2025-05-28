/**
 * C tcp server test example.
 * 
 * License - MIT.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <sys/time.h>
#include <sys/socket.h>
#include <sys/select.h>

#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>


#define SERVER_IP                   "127.0.0.1"
#define SERVER_PORT                 65533
#define MAX_CONNECT                 8
#define DATA_BUFLEN                 128


/**
 * client_maxfd - Get max client fd.
*/
int client_maxfd(int *list, int len)
{
    int status = list[0];

    for (int i = 1; i < len; i++) {
        if (status < list[i])
            status = list[i];
    }

    return status;
}

/**
 * client_delete - Delete client member from list.
*/
int client_delete(int *list, int len, int member)
{
    int status = -1;

    for (int i = 0; i < len; i++) {
        if (member == list[i]) {
            list[i] = 0;

            status = 0;
        }
    }

    return status;
}

/**
 * client_insert - Insert client member to list.
*/
int client_insert(int *list, int len, int member)
{
    int status = -1;

    for (int i = 0; i < len; i++) {
        if (0 == list[i]) {
            list[i] = member;
            status  = 0;

            break;
        }
    }

    return status;
}

/**
 * timeout_function - Timeout callback function.
*/
int timeout_function(void)
{
    printf("Select timeout.\n");

    return 0;
}

/**
 * read_from_client - Read data from client.
*/
int read_from_client(int *clt_list, int len, int index)
{
    int ret = -1;
    char buf[DATA_BUFLEN + 1] = { 0 };

    ret = read(clt_list[index], buf, DATA_BUFLEN);

    if (0 < ret) {
        buf[ret] = 0;
        printf("From client %d, data: %s.\n", clt_list[index], buf);
    }
    else if (0 == ret) {
        close(clt_list[index]);

        printf("Client %d exit.\n", clt_list[index]);
        client_delete(clt_list, len, clt_list[index]);
    }
    else {
        printf("Error in read.\n");
    }

    return ret;
}

/**
 * write_to_client - Write data to client.
*/
int write_to_client(int *clt_list, int len, int index)
{
    int ret = -1;

    ret = write(clt_list[index], "OK", 2);

    if (0 > ret) {
        printf("Error in write.\n");
    }

    return 0;
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
    int i       = 0;
    int ret     = -1;
    int serfd   = -1;
    int cltfd   = -1;
    int maxfd  = 0;
    int cltfds[MAX_CONNECT] = { 0 };

    char usr_buf[DATA_BUFLEN + 1] = { 0 };

    struct timeval time_out;
    struct sockaddr_in clt_addr;

    memset(&clt_addr, 0, sizeof(clt_addr));
    int len = sizeof(clt_addr);

    fd_set read_fds;
    fd_set write_fds;
    fd_set except_fds;

    FD_ZERO(&read_fds);
    FD_ZERO(&write_fds);
    FD_ZERO(&except_fds);

    /* Start tcp server. */
    serfd = start_server(SERVER_IP, SERVER_PORT);

    if (serfd < -1) {
        printf("Error in start_server.\n");
        goto err_start;
    }

    maxfd = serfd;

    printf("TCP Sever running.\n");
    printf("Server ip: %s, port: %d.\n", SERVER_IP, SERVER_PORT);
    printf("Press CTRL+C to quit.\n\n");

    while (1)
    {
        time_out.tv_sec  = 60;
        time_out.tv_usec = 0;

        FD_ZERO(&read_fds);
        FD_ZERO(&except_fds);

        /**
         * stdin == 0, stdout == 1, stderr == 2.
         * Add stdin to read_fds.
        */
        FD_SET(0, &read_fds);

        /* Add serfd to read_fds. */
        FD_SET(serfd, &read_fds);

        /* Add all valid client. */
        for (i = 0; i < MAX_CONNECT; i++) {
            if (0 < cltfds[i]) {
                FD_SET(cltfds[i], &read_fds);
                FD_SET(cltfds[i], &except_fds);
            }
        }

        maxfd = client_maxfd(cltfds, MAX_CONNECT);

        maxfd = maxfd > serfd ? maxfd : serfd;

        /**
         * MAX_CONNECT + 2 == all client + server + stdin.
        */
        ret = select(maxfd + 1, &read_fds, &write_fds, &except_fds, &time_out);
        if (0 < ret) {
            /* New client. */
            if (FD_ISSET(serfd, &read_fds)) {
                cltfd = accept(serfd, (struct sockaddr*)&clt_addr, (socklen_t *)&len);

                if (-1 < client_insert(cltfds, MAX_CONNECT, cltfd)) {
                    FD_SET(cltfd, &read_fds);

                    printf("Connected client ip: %s, port: %d.\n",
                            inet_ntoa(clt_addr.sin_addr), ntohs(clt_addr.sin_port));
                }
            }
            /* stdin. */
            else if (FD_ISSET(0, &read_fds)) {
                fgets(usr_buf, DATA_BUFLEN, stdin);

                printf("User command: %s\n", usr_buf);

                if (!strncmp("quit", usr_buf, 4)) {
                    FD_ZERO(&read_fds);
                    FD_ZERO(&write_fds);
                    FD_ZERO(&except_fds);

                    printf("Server will exit.\n");

                    break;
                }
            }
            else {
                for (i = 0; i < MAX_CONNECT; i++) {
                    /* Out of band data. */
                    if ((0 < cltfds[i]) && (FD_ISSET(cltfds[i], &except_fds))) {
                        recv(cltfds[i], usr_buf, DATA_BUFLEN, MSG_OOB);

                        printf("Out of band data: %s.\n", usr_buf);
                    }

                    /* Receive data. */
                    if ((0 < cltfds[i]) && (FD_ISSET(cltfds[i], &read_fds))) {
                        ret = read_from_client(cltfds, MAX_CONNECT, i);
                        
                        if (0 < ret) {
                            FD_SET(cltfds[i], &write_fds);
                        }
                    }

                    /* Send data. */
                    if ((0 < cltfds[i]) && (FD_ISSET(cltfds[i], &write_fds))) {
                        write_to_client(cltfds, MAX_CONNECT, i);

                        FD_CLR(cltfds[i], &write_fds);
                    }
                }
            }
        }
        else if (0 == ret) {
            timeout_function();
            continue;
        }
        else {
            printf("Error in select.\n");
            break;
        }
    }
    
    close(serfd);

    return 0;

err_start:
    return -1;
}
