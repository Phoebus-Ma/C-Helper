/**
 * Module Name:
 *      main.c
 * 
 * Abstract:
 *      EasyJson Test.
 * 
 * License - MIT
*/

#include <stdio.h>
#include <string.h>

#include "easyjson.h"


#define EASYJSON_LIGHT_KEY                  "light"
#define EASYJSON_PRIORITY_KEY               "priority"
#define EASYJSON_PREEMPT_KEY                "preempt"
#define EASYJSON_REPEAT_KEY                 "repeat"
#define EASYJSON_REQUEST_KEY                "request"

#define LED_PARAM_NUM                       (5 - 1)
#define SEND_LEN                            EASYJSON_MAX_LENGTH + 123
#define CMD_DATA                            "{\"light\":%d, \"priority\":%d, \"preempt\":%d, \"repeat\":%d, \"request\":\"%s\"}"


typedef struct _LED_PROPERTY {
    int ledparam[LED_PARAM_NUM];
    char request[EASYJSON_MAX_LENGTH];
} LED_PROPERTY, *PLED_PROPERTY;

/**
 * easyjson_packaging - 
*/
int easyjson_packaging(char *send_buf)
{
    sprintf(send_buf, CMD_DATA, 1, 2, 3, 4, "led test");

    return 0;
}

/**
 * easyjson_parsing - 
*/
int easyjson_parsing(char *request_data, PLED_PROPERTY pled)
{
    easy_json_object_get_string(request_data,   EASYJSON_REQUEST_KEY,   pled->request);
    easy_json_object_get_int(request_data,      EASYJSON_LIGHT_KEY,     &pled->ledparam[0]);
    easy_json_object_get_int(request_data,      EASYJSON_PRIORITY_KEY,  &pled->ledparam[1]);
    easy_json_object_get_int(request_data,      EASYJSON_PREEMPT_KEY,   &pled->ledparam[2]);
    easy_json_object_get_int(request_data,      EASYJSON_REPEAT_KEY,    &pled->ledparam[3]);

    return 0;
}

int main(void)
{
    char sendbuf[SEND_LEN] = {0};
    LED_PROPERTY led_property;

    memset(&led_property, 0, sizeof(led_property));

    easyjson_packaging(sendbuf);
    easyjson_parsing(sendbuf, &led_property);

    printf("Receive LED command:\n\tlight: %d\n\tpriority: %d\n\tpreempt: %d\n\trepeat: %d\n\trequest: %s.\n",
            led_property.ledparam[0],
            led_property.ledparam[1],
            led_property.ledparam[2],
            led_property.ledparam[3],
            led_property.request);

    return 0;
}
