/**
 * Module Name:
 *      easy_json.c
 * 
 * Abstract:
 *      EasyJson API.
 * 
 * License - MIT
*/

#include "easyjson.h"


char str_buf[EASYJSON_MAX_LENGTH + 256] = {0};
char dest_pos[EASYJSON_MAX_LENGTH + 128] = {0};

/**
 * easy_json_object_get_string - get string data by json object.
*/
int easy_json_object_get_string(char *str, char *key, char *dest)
{
    char *token;
    char *delims = {"{,}"};
    char keybuf[64] = {0};
    int status = -1;
    int i = 0;

    if (!strstr(str, key))
        return status;

    memcpy(str_buf, str, strlen(str));
    char *str_pos = str_buf;

    while((token = strsep(&str_pos, delims)) != NULL)
    {
        if(*token == 0)
            continue;

        sscanf(token, "%63[^:]", keybuf);

        if(strstr(keybuf, key)) {
            sscanf(token, "%*[^:]:%[^~]", dest_pos);
            i = 0;
            while(' ' == dest_pos[i])
                i++;

            if('"' == dest_pos[i])
                memcpy(dest, dest_pos + i + 1, strlen(dest_pos) - i - 2);
            else
                memcpy(dest, dest_pos + i, strlen(dest_pos) - i);

            dest_pos[0] = 0;
            status = 0;
        }
    }

    str_buf[0] = 0;

    return status;
}

/**
 * easy_json_object_get_int - get int data by json object.
*/
int easy_json_object_get_int(char *str, char *key, int *num)
{
    int status  = -1;
    char num_buf[32] = {0};

    if(!easy_json_object_get_string(str, key, num_buf)) {
        if(strspn(num_buf, "-0123456789") == strlen(num_buf)) {
            *num = atoi(num_buf);
            status = 0;
        }
    }

    return status;
}
