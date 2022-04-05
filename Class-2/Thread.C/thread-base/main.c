/**
 * C base process example.
 * 
 * License - MIT.
*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>


/**
 * thread_function - Thread function.
*/
void *thread_function(void *param)
{
    printf("Parameter: %s.\n", (char *)param);

    for (int i = 0; i < 5; i++) {
        printf("Child thread running.\n");

        sleep(1);
    }

    return (void *)0;
}


/**
 * Main function.
*/
int main(void)
{
    int ret = -1;
    pthread_t tid;
    char param[] = "To be NO.1";

    /* Create thread. */
    ret = pthread_create(&tid, NULL, thread_function, &param);

    if (0 > ret) {
        printf("Error in pthread_create.\n");
        goto err_create;
    }

    /* Wait child thread to end. */
    ret = pthread_join(tid, NULL);

    if (0 != ret) {
        printf("Error in pthread_join.\n");
        goto err_create;
    }

    printf("Main thread to end.\n");

    return 0;

err_create:
    return -1;
}

