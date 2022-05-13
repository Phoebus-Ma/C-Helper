/**
 * C thread spin lock example.
 * 
 * License - MIT.
*/

#include <stdio.h>

#include <unistd.h>
#include <pthread.h>


#define MAX_THRD_COUNT                      2

pthread_spinlock_t thrd_spin;

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
        pthread_spin_lock(&thrd_spin);

        calc_formula(pthread_self(), 5, 6);

        pthread_spin_unlock(&thrd_spin);

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
        pthread_spin_lock(&thrd_spin);

        calc_formula(pthread_self(), 7, 8);

        pthread_spin_unlock(&thrd_spin);

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

    /* Initialize spin lock. */
    pthread_spin_init(&thrd_spin, PTHREAD_PROCESS_PRIVATE);

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

    /* Destory spin lock. */
    pthread_spin_destroy(&thrd_spin);

err_create:
    return status;
}
