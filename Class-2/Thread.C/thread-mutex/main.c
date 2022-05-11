/**
 * C thread mutex lock example.
 * 
 * License - MIT.
*/

#include <stdio.h>

#include <unistd.h>
#include <pthread.h>


#define MAX_THRD_COUNT                      2

pthread_mutex_t thrd_mutex;

/**
 * calc_formula - Calculate data.
*/
int calc_formula(pthread_t tid, int x, int y)
{
    printf("Tid: %ld using calculate resource.\n", tid);

    printf("Result: %d.\n", x * y);

    return 0;
}

/**
 * thread_func2 - Thread function 2.
*/
void *thread_func2(void *param)
{
    for (int i = 0; i < 3; i++) {
        pthread_mutex_lock(&thrd_mutex);

        calc_formula(pthread_self(), 5, 6);

        sleep(3);

        pthread_mutex_unlock(&thrd_mutex);

        sleep(1);
    }

    return (void *)0;
}

/**
 * thread_func1 - Thread function 1.
*/
void *thread_func1(void *param)
{
    for (int i = 0; i < 3; i++) {
        pthread_mutex_lock(&thrd_mutex);

        calc_formula(pthread_self(), 7, 8);

        sleep(2);

        pthread_mutex_unlock(&thrd_mutex);

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
    int status = 0;
    pthread_t tid[MAX_THRD_COUNT];

    void *(*thread_func[MAX_THRD_COUNT])(void *) = {
        thread_func1,
        thread_func2,
    };

    /* Initialize mutex. */
    pthread_mutex_init(&thrd_mutex, NULL);

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

err_create:
    /* Destory mutex. */
    pthread_mutex_destroy(&thrd_mutex);

    return status;
}
