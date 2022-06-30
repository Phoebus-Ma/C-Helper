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
#include <sys/timerfd.h>

#include <sys/un.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>


#define MAX_CONNECT                 8
#define MAX_BUFF_SIZE               128
#define EPOLL_TIMEOUT               10000   /* ms. */
#define SOCKET_PATH                 "/tmp/testepoll.sock"

/**
 * SET_EPOLL_CTL - epoll_ctl.
*/
#define SET_EPOLL_CTL(EPOLL_FD, OPT, EVENT_OBJ, OBJ_FD, EVENT)  \
        do {                                                    \
            EVENT_OBJ.data.fd   = OBJ_FD,                       \
            EVENT_OBJ.events    = (EVENT),                      \
            epoll_ctl(EPOLL_FD, (OPT), OBJ_FD, &EVENT_OBJ);     \
        } while (0)


#ifdef SOCKET_NO_BLOCK
/**
 * set_socket_no_bloking - Set socket no bloking.
*/
int set_socket_no_bloking(int fd)
{
    int flags = fcntl(fd, F_GETFL, NULL);

    if (flags < 0) {
        printf("Error in fcntl get.\n");
        return -1;
    }

    flags |= O_NONBLOCK;

    if (fcntl(fd, F_SETFL, flags) < 0) {
        printf("Error in fcntl set.\n");
        return -1;
    }

    return 0;
}
#endif /* SOCKET_NO_BLOCK */

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
    if (listen(ser_fd, MAX_CONNECT - 1) < 0) {
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
    int i       = -1;
    int len     = -1;
    int num     = -1;
    int serfd   = -1;
    int cltfd   = -1;
    int epofd   = -1;
    int status  = 0;

    char buf[MAX_BUFF_SIZE + 1] = { 0 };

    struct sockaddr_un cltaddr;
    struct epoll_event *events, tmpevent;

    /* Start socket unix server. */
    serfd = start_server();

    if (0 > serfd) {
        printf("Error in start_server.\n");
        status = -1;
        goto out_start;
    }

#ifdef SOCKET_NO_BLOCK
    /* Set socket no bloking */
    set_socket_no_bloking(serfd);
#endif /* SOCKET_NO_BLOCK */

    /* Create epoll instance. */
    epofd = epoll_create(MAX_CONNECT);

    if (0 > epofd) {
        printf("Error in epoll_create.\n");
        status = -1;
        goto out_epoll;
    }

    /* Create read event for server fd. */
    SET_EPOLL_CTL(epofd, EPOLL_CTL_ADD, tmpevent, serfd, EPOLLIN);

    /* Alloc events memory space. */
    events = calloc(MAX_CONNECT, sizeof(struct epoll_event));

    if (NULL == events) {
        printf("Error in calloc.\n");
        status = -1;
        goto out_event;
    }

    printf("TCP Sever running.\n");
    printf("Communication node: %s.\n", SOCKET_PATH);
    printf("Press CTRL+C to quit!\n\n");

    while (1)
    {
        /* Wait epoll events. */
        num = epoll_wait(epofd, events, MAX_CONNECT, EPOLL_TIMEOUT);

        if (0 > num) {
            printf("Error in epoll_wait.\n");
            status = -1;
            goto out_calloc;
        }

        for (i = 0; i < num; i++) {

            /* Server events. */
            if (serfd == events[i].data.fd) {

                /* Server hang up or error. */
                if (events[i].events & EPOLLHUP || events[i].events & EPOLLERR) {
                    printf("Server error.\n");
                    status = -1;
                    goto out_calloc;
                }

                /* Accept client */
                len = sizeof(cltaddr);
                
                cltfd = accept(serfd, (struct sockaddr*)&cltaddr, (socklen_t *)&len);
                
                if (0 > cltfd) {
                    printf("Error in accept.\n");
                    status = -1;
                    goto out_calloc;
                }

#ifdef SOCKET_NO_BLOCK
                /* Set socket no bloking */
                set_socket_no_bloking(cltfd);
#endif /* SOCKET_NO_BLOCK */

                /* Add a read event. */
                SET_EPOLL_CTL(epofd, EPOLL_CTL_ADD, tmpevent, cltfd, EPOLLIN);
            }

            /* Client events. */
            else if (events[i].events & EPOLLIN) {
                status = read(events[i].data.fd, buf, MAX_BUFF_SIZE);

                if (0 > status) {
                    printf("Error in read.\n");

                    SET_EPOLL_CTL(epofd, EPOLL_CTL_DEL, tmpevent, events[i].data.fd, EPOLLIN);
                    close(events[i].data.fd);
                }
                else if (0 == status) {
                    printf("Client exit.\n");

                    SET_EPOLL_CTL(epofd, EPOLL_CTL_DEL, tmpevent, events[i].data.fd, EPOLLIN);
                    close(events[i].data.fd);
                }
                else {
                    if (!strcmp("Quit!!!", buf)) {
                        write(events[i].data.fd, "OK", strlen("OK"));

                        SET_EPOLL_CTL(epofd, EPOLL_CTL_DEL, tmpevent, events[i].data.fd, EPOLLIN);
                        close(events[i].data.fd);
                    }

                    printf("From client %d Recv: %s.\n", events[i].data.fd, buf);

                    write(cltfd, "OK", strlen("OK"));
                }
            }
        }

        sleep(1);
    }

out_calloc:
    SET_EPOLL_CTL(epofd, EPOLL_CTL_DEL, tmpevent, serfd, EPOLLIN);

out_event:
    free(events);

out_epoll:
    close(serfd);

out_start:
    unlink(SOCKET_PATH);

    return status;
}
