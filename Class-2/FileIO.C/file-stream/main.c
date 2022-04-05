/**
 * C base stream file example.
 * 
 * License - MIT.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define _FILE_NAME                      "test.txt"


/**
 * fscanf_test - Stream fscanf data from data.
*/
int fscanf_test(char *file_name)
{
    FILE *fp = NULL;
    int number = -1;
    char buf[32] = { 0 };

    fp = fopen(file_name, "r");

    if (NULL == fp) {
        printf("Error in fopen: %s.\n", __func__);
        goto err_open_s;
    }

    fscanf(fp, "%s%d", buf, &number);

    printf("The buf: %s, number: %d.\n", buf, number);

    fclose(fp);

    return 0;

err_open_s:
    return -1;
}


/**
 * fprintf_test - Stream fprintf data to file.
*/
int fprintf_test(char *file_name)
{
    FILE *fp = NULL;

    fp = fopen(file_name, "w");

    if (NULL == fp) {
        printf("Error in fopen: %s.\n", __func__);
        goto err_open_p;
    }

    fprintf(fp, "%s %d\n", "Hello", 123);

    fclose(fp);

    return 0;

err_open_p:
    return -1;
}


/**
 * fgets_test - Stream fgets data from file.
*/
int fgets_test(char *file_name)
{
    FILE *fp = NULL;
    char buf[128] = { 0 };

    fp = fopen(file_name, "r");

    if (NULL == fp) {
        printf("Error in fopen: %s.\n", __func__);
        goto err_open_g;
    }

    fgets(buf, 127, fp);

    fputs(buf, stdout);

    fclose(fp);

    return 0;

err_open_g:
    return -1;
}


/**
 * fputs_test - Stream fputs data to file.
*/
int fputs_test(char *file_name)
{
    FILE *fp = NULL;
    char buf[] = "Hello, World.\n";

    fp = fopen(file_name, "w");

    if (NULL == fp) {
        printf("Error in fopen: %s.\n", __func__);
        goto err_open_p;
    }

    fputs(buf, fp);

    fclose(fp);

    return 0;

err_open_p:
    return -1;
}


/**
 * fread_test - Stream read data from file.
*/
int fread_test(char *file_name)
{
    FILE *fp = NULL;
    char buf[128] = { 0 };

    fp = fopen(file_name, "r");

    if (NULL == fp) {
        printf("Error in fopen: %s.\n", __func__);
        goto err_open_r;
    }

    fread(buf, 127, 1, fp);

    printf("Use fread get data: %s.\n", buf);

    fclose(fp);

    return 0;

err_open_r:
    return -1;
}


/**
 * fwrite_test - Stream write data to file.
*/
int fwrite_test(char *file_name)
{
    FILE *fp = NULL;
    char buf[] = "To be NO.1.\n";

    fp = fopen(file_name, "w");

    if (NULL == fp) {
        printf("Error in fopen: %s\n", __func__);
        goto err_open_w;
    }

    fwrite(buf, strlen(buf), 1, fp);

    fclose(fp);

    return 0;

err_open_w:
    return -1;
}


/**
 * Main function.
*/
int main(void)
{
    /* Example 1: Stream write test. */
    fwrite_test(_FILE_NAME);

    /* Example 2: Stream read test. */
    fread_test(_FILE_NAME);

    /* Example 3: Stream fputs test. */
    fputs_test(_FILE_NAME);

    /* Example 4: Stream fgets test. */
    fgets_test(_FILE_NAME);

    /* Example 5: Stream fprintf test. */
    fprintf_test(_FILE_NAME);

    /* Example 6: Stream fscanf test. */
    fscanf_test(_FILE_NAME);

    return 0;
}

