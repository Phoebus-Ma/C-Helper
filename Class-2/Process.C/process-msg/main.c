/**
 * C use process System V message queue communication example.
 *
 * License - MIT.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>


#define MAX_DATA_LEN                    128

typedef struct msgbuf {
    long mytype;
    char mtext[MAX_DATA_LEN + 1];
} MSGBUF, *LPMSGBUF;


/**
 * msg_queue_send - Send message to queue.
 */
int msg_queue_send(int msg_id, int id, char *write_buf, int len)
{
    MSGBUF msg_buf;

    if ((0 > msg_id) || (MAX_DATA_LEN < len))
        return -1;

    msg_buf.mytype = id;
    strncpy(msg_buf.mtext, write_buf, len);

    return msgsnd(msg_id, &msg_buf, strlen(msg_buf.mtext), 0);
}

/**
 * msg_queue_receive - Receive message from queue.
*/
#define msg_queue_receive(msg_id, id, msg_buf)          \
    do {                                                \
        msgrcv(msg_id, &msg_buf, MAX_DATA_LEN, id, 0);  \
    } while (0)

/**
 * msg_queue_create - Create system v message queue.
 */
int msg_queue_create(key_t msg_key)
{
    int msg_id = -1;

    if (0 > msg_key)
        return -1;

    msg_id = msgget(msg_key, IPC_CREAT | 0664);

    return msg_id;
}

/**
 * msg_queue_delete - Delete system v message queue.
 */
int msg_queue_delete(int msg_id)
{
    if (0 > msg_id)
        return -1;

    return msgctl(msg_id, IPC_RMID, NULL);
}

/**
 * Main function.
 */
int main(void)
{
    int msg_id      = -1;
    pid_t pid       = -1;
    key_t msg_key   = -1;

    MSGBUF msg_buf;
    memset(&msg_buf, 0, sizeof(msg_buf));

    msg_key = ftok(".", 0x0D);

    if (0 > msg_key) {
        printf("Errorr in ftok.\n");
        goto out_ftok;
    }

    msg_id = msg_queue_create(msg_key);

    if (0 > msg_id) {
        printf("Error in msg_queue_create.\n");
        goto out_ftok;
    }

    pid = fork();

    if (0 > pid) {
        printf("Error in fork.\n");
        goto out_fork;
    }
    /* Child process. */
    else if (0 == pid) {
        msg_queue_receive(msg_id, 7, msg_buf);
        printf("Child process read: %s.\n", msg_buf.mtext);

        printf("Child process write: Nihao.\n");
        msg_queue_send(msg_id, 8, "Nihao", 5 + 1);

        exit(0);
    }
    /* Parent process. */
    else {
        printf("Parent process write: Hello.\n");
        msg_queue_send(msg_id, 7, "Hello", 5 + 1);

        msg_queue_receive(msg_id, 8, msg_buf);
        printf("Parent process read: %s.\n", msg_buf.mtext);
    }

out_fork:
    msg_queue_delete(msg_id);

out_ftok:
    return 0;
}
