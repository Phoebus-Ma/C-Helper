/**
 * C use process shared memory communication example.
 * 
 * License - MIT.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/types.h>


/* 1 << 10 == 1024. */
#define MAX_SHARED_MEMLEN                   (1 << 10)


/**
 * connect_shared_mem - Map shared memory to process memory space.
 * 
 * @shm_id: [in], shared memory id.
 * @shm_buf: [Out], shared memory buf address.
*/
int connect_shared_mem(int shm_id, char **shm_buf)
{
    if (0 > shm_id) {
        *shm_buf = NULL;
        return -1;
    }

    *shm_buf = (char *)shmat(shm_id, NULL, 0);

    return 0;
}

/**
 * disconnect_shared_mem - Stripping shared memory from process memory space.
*/
int disconnect_shared_mem(char **shm_buf)
{
    int status = -1;

    if (NULL != shm_buf) {
        status = shmdt(*shm_buf);
        shm_buf = NULL;
    }

    return status;
}

/**
 * create_shared_mem - Create a shared memory.
*/
int create_shared_mem(key_t key)
{
    int shm_id = -1;

    shm_id = shmget(key, MAX_SHARED_MEMLEN, IPC_CREAT | 0664);

    return shm_id;
}

/**
 * delete_shared_mem - Delete an existing shared memory.
*/
int delete_shared_mem(int shm_id)
{
    int status = -1;

    if (0 < shm_id)
        status = shmctl(shm_id, IPC_RMID, NULL);

    return status;
}

/**
 * Main function.
*/
int main(void)
{
    int status  = 0;
    int shm_id  = -1;
    key_t key   = -1;
    pid_t pid   = -1;

    char *shm_buf = NULL;

    /* Create key. */
    key = ftok("./", 0x0E);

    if (0 > key) {
        printf("Error in ftok.\n");
        status = -1;
        goto out_ftok;
    }

    /* Create shared memory. */
    shm_id = create_shared_mem(key);

    if (0 > shm_id) {
        printf("Error in create_shared_mem.\n");
        status = -1;
        goto out_shmcreate;
    }

    pid = fork();

    if (0 > pid) {
        printf("Error in fork.\n");
        status = -1;
        goto out_shmcreate;
    }
    /* Child process. */
    else if (0 == pid) {
        if (0 > connect_shared_mem(shm_id, &shm_buf)) {
            printf("Error in sem_post.\n");
            goto out_shmcreate;
        }

        /* delay. */
        for (int i = 0; i < 0xfff; i++);
        
        printf("Child process receive: %s\n", shm_buf);

        sprintf(shm_buf, "Nihao from %d.", getpid());

        if (0 > disconnect_shared_mem(&shm_buf)) {
            printf("Error in sem_wait.\n");
            goto out_shmcreate;
        }

        exit(0);
    }
    /* Parent process. */
    else {
        if (0 > connect_shared_mem(shm_id, &shm_buf)) {
            printf("Error in sem_post.\n");
            goto out_shmcreate;
        }

        strncpy(shm_buf, "Hello.", 6 + 1);

        sleep(1);
        printf("Parent process receive: %s\n", shm_buf);

        if (0 > disconnect_shared_mem(&shm_buf)) {
            printf("Error in sem_wait.\n");
            goto out_shmcreate;
        }

        /* Wait for child process to end. */
        wait(NULL);
    }

out_shmcreate:
    delete_shared_mem(shm_id);

out_ftok:
    return status;
}
