/**
 * Module Name:
 *      easy_json.h
 * 
 * Abstract:
 *      EasyJson API header.
 * 
 * License - MIT
*/

#ifndef __EASYJSON_H__
#define __EASYHSON_H__


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define EASYJSON_MAX_LENGTH                     1023


/* packaging */


/* parsing */
int easy_json_object_get_string(char *str, char *key, char *dest);
int easy_json_object_get_int(char *str, char *key, int *num);

#endif /* __EASYJSON_H__ */
