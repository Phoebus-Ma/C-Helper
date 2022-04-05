/**
 * C base file example.
 * 
 * License - MIT.
*/

#include <stdio.h>
#include <string.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>


#define _FILE_NAME                  "test.txt"


/**
 * read_test - Read data from file.
*/
int read_test(char *file_name)
{
    int fd = -1;
    char buf[128] = { 0 };

    fd = open(file_name, O_RDONLY);

    if (fd < 0) {
        printf("Error in open: %s.\n", __func__);
        goto err_open_r;
    }

    read(fd, buf, 128 - 1);

    printf("The data: %s.\n", buf);

    close(fd);

    return 0;

err_open_r:
    return -1;
}


/**
 * write_test - Write data to file.
*/
int write_test(char *file_name)
{
    int fd = -1;
    char buf[] = "To be NO.1";

    fd = open(file_name, O_WRONLY | O_CREAT);

    if (fd < 0) {
        printf("Error in open file: %s.\n", __func__);

        goto err_open_w;        
    }

    write(fd, buf, strlen(buf));

    if (close(fd) < 0)
        printf("Error in close: %s.\n", __func__);

    return 0;

err_open_w:
    return -1;
}


/**
 * Main function.
*/
int main(void)
{
    /* Example 1: Write file. */
    write_test(_FILE_NAME);

    /* Example 2: Read file. */
    read_test(_FILE_NAME);

    return 0;
}

