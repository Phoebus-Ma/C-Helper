/**
 * C use process System V semaphore communication example.
 * 
 * License - MIT.
*/

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <sys/types.h>


union semun
{
    int             val;
    struct semid_ds *buf;
    unsigned short  *array;
    struct seminfo  *__buf;
};


/**
 * sem_post - .
*/
int sem_post(int sem_id)
{
    struct sembuf sem_buf;

    sem_buf.sem_op  = -1;
    sem_buf.sem_num = 0;
    sem_buf.sem_flg = SEM_UNDO;

    if (0 > semop(sem_id, &sem_buf, 1))
        return -1;

    return 0;
}

/**
 * sem_wait - .
*/
int sem_wait(int sem_id)
{
    struct sembuf sem_buf;

    sem_buf.sem_op  = 1;
    sem_buf.sem_num = 0;
    sem_buf.sem_flg = SEM_UNDO;

    if (0 > semop(sem_id, &sem_buf, 1))
        return -1;

    return 0;
}

/**
 * sem_init - Initialize System V semaphore.
*/
int sem_init(int sem_id)
{
    union semun sem;

    sem.val = 1;

    if (0 > semctl(sem_id, 0, SETVAL, sem))
        return -1;

    return 0;
}

/**
 * sem_clear - Clean System V semaphore.
*/
int sem_clear(int sem_id)
{
    if (0 > semctl(sem_id, 0, IPC_RMID))
        return -1;

    return 0;
}

/**
 * Main function.
*/
int main(void)
{
    int status  = 0;
    int sem_id  = -1;
    pid_t pid   = -1;

    /* Create semaphore. */
    sem_id = semget((key_t)1314, 1, 0664 | IPC_CREAT);

    if (0 > sem_id) {
        printf("Error in semget.\n");
        goto out_semget;
    }

    /* Initialize semaphore. */
    if (sem_init(sem_id)) {
        printf("Error in sem_init.\n");
        status = -1;
        goto out_seminit;
    }

    pid = fork();

    if (0 > pid) {
        printf("Error in fork.\n");
        status = -1;
        goto out_seminit;
    }
    /* Child process. */
    else if (0 == pid) {
        for (int i = 0; i < 5; i++)
        {
            if (0 > sem_post(sem_id)) {
                printf("Error in sem_post.\n");
                goto out_seminit;
            }

            printf("Child process active.\n");

            if (0 > sem_wait(sem_id)) {
                printf("Error in sem_wait.\n");
                goto out_seminit;
            }
        }

        exit(0);
    }
    /* Parent process. */
    else {
        for (int i = 0; i < 5; i++)
        {
            if (0 > sem_post(sem_id)) {
                printf("Error in sem_post.\n");
                goto out_seminit;
            }

            printf("Parent process active.\n");

            if (0 > sem_wait(sem_id)) {
                printf("Error in sem_wait.\n");
                goto out_seminit;
            }
        }

        /* Wait for child process to end. */
        wait(NULL);
    }

out_seminit:
    sem_clear(sem_id);

out_semget:
    return status;
}
