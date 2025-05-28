/**
 * C thread condition example.
 * 
 * License - MIT.
*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>


#define MAX_THRD_COUNT                      2

pthread_mutex_t thrd_mutex;
pthread_cond_t thrd_cond;

static int temp_value = 0;

/**
 * thread_func2 - Thread function 2.
*/
void *thread_func2(void *param)
{
    for (int i = 0; i < 10; i++) {
        pthread_cond_wait(&thrd_cond, &thrd_mutex);

        temp_value = 0;
        printf("[%s] temp_value: %d.\n", __func__, temp_value);
    }

    return (void *)0;
}

/**
 * thread_func1 - Thread function 1.
*/
void *thread_func1(void *param)
{
    for (int i = 0; i < 10; i++) {
        pthread_mutex_lock(&thrd_mutex);

        for (int j = 0; j < 101; j++) {
            temp_value++;

            if (100 < temp_value) {
                printf("[%s] temp_value: %d.\n", __func__, temp_value);
                pthread_cond_signal(&thrd_cond);
            }
        }

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

    /* Initailize condition. */
    pthread_cond_init(&thrd_cond, NULL);

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
    /* Destory condition. */
    pthread_cond_destroy(&thrd_cond);

    /* Destory mutex. */
    pthread_mutex_destroy(&thrd_mutex);

    return status;
}
