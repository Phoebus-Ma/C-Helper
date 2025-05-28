/**
 * C thread spin lock example.
 * 
 * License - MIT.
*/

#include <stdio.h>
#include <time.h>

#include <unistd.h>
#include <pthread.h>


#define MAX_THRD_COUNT                      3

static int var_value = 0;
pthread_rwlock_t thrd_rwlock;

/**
 * thread_func3 - Thread function 3.
*/
void *thread_func3(void *param)
{
    printf("Thread 3 start.\n");

    pthread_rwlock_rdlock(&thrd_rwlock);

    printf("Thread 3: %d.\n", var_value);

    sleep(3);
    printf("Thread 3 end.\n");
    pthread_rwlock_unlock(&thrd_rwlock);

    return (void *)0;
}

/**
 * thread_func2 - Thread function 2.
*/
void *thread_func2(void *param)
{
    printf("Thread 2 start.\n");

    pthread_rwlock_rdlock(&thrd_rwlock);

    printf("Thread 2: %d.\n", var_value);

    sleep(3);

    printf("Thread 2 end.\n");
    pthread_rwlock_unlock(&thrd_rwlock);

    return (void *)0;
}

/**
 * thread_func1 - Thread function 1.
*/
void *thread_func1(void *param)
{
    printf("Thread 1 start.\n");

    pthread_rwlock_wrlock(&thrd_rwlock);

    var_value = 100;

    sleep(5);

    printf("Thread 1 end.\n");
    pthread_rwlock_unlock(&thrd_rwlock);

    return (void *)0;
}

/**
 * Main function.
*/
int main(void)
{
    int i = 0;
    int status = 0;
    pthread_t tid[MAX_THRD_COUNT];

    void *(*thread_func[MAX_THRD_COUNT])(void *) = {
        thread_func1,
        thread_func2,
        thread_func3,
    };

    /* Initialize rwlock. */
    pthread_rwlock_init(&thrd_rwlock, NULL);

    /* Create multi thread. */
    for (i = 0; i < MAX_THRD_COUNT; i++) {
        if (0 != pthread_create(&tid[i], NULL, thread_func[i], NULL)) {
            printf("Error in pthread_create.\n");
            status = -1;
            goto err_create;
        }
    }

    /* Wait all thread to end. */
    for (i = 0; i < MAX_THRD_COUNT; i++) {
        if (0 != pthread_join(tid[i], NULL)) {
            printf("Error in pthread_join.\n");
            status = -1;
            goto err_create;
        }
    }

    /* Destory rwlock. */
    pthread_rwlock_destroy(&thrd_rwlock);

err_create:
    return status;
}
