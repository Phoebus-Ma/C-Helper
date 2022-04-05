/**
 * C thread semaphore example.
 * 
 * License - MIT.
*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>


#define THRD_COUNT                  2


/* Define global var. */
sem_t thrd_sem;


/**
 * thread_func2 - Thread function 2.
*/
void *thread_func2(void *param)
{
    int i = 0;

    /* Step 1. */
    for (i = 0; i < 3; i++) {
        printf("Thread func2 running.\n");

        sleep(1);
    }

    sem_post(&thrd_sem);

    return 0;
}


/**
 * thread_func1 - Thread function 1.
*/
void *thread_func1(void *param)
{
    int i = 0;

    /* Step 2. */
    sem_wait(&thrd_sem);

    for (i = 0; i < 5; i++) {
        printf("Thread func1 running.\n");

        sleep(1);
    }

    return (void *)0;
}


/**
 * Main function.
*/
int main(void)
{
    int i = 0;
    pthread_t tid[THRD_COUNT];

    void *(*thread_func[THRD_COUNT])(void *) = {
        thread_func1,
        thread_func2,
    };

    /* Initialize semaphore. */
    sem_init(&thrd_sem, 0, 0);

    /* Create multi thread. */
    for (i = 0; i < THRD_COUNT; i++) {
        if (0 != pthread_create(&tid[i], NULL, thread_func[i], NULL)) {
            printf("Error in pthread_create.\n");
            goto err_create;
        }
    }

    /* Wait all thread to end. */
    for (i = 0; i < THRD_COUNT; i++) {
        if (0 != pthread_join(tid[i], NULL)) {
            printf("Error in pthread_join.\n");
            goto err_create;
        }
    }

    printf("Main thread to end.\n");

    return 0;

err_create:
    return -1;
}

