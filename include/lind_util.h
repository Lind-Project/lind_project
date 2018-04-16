/*
 * lind_util.h
 *
 *  Created on: June 16, 2014
 *      Author: Ali Gholami, Benson Tsai
 */

#include <stdlib.h>
#include <limits.h>
#include <error.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define LIND_PATH_MAX 4096

char *trim(char * str);
char *get_substring(char *string, int position, int length);
const char *get_lind_config();
