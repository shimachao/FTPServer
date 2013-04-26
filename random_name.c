#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <malloc.h>
#include "random_name.h"

char* random_name(char *suffix)
{
	time_t now;
	struct tm *timenow;
	char *time_str, *str_ret;
	int length;
	//
	time (&now);
	timenow = localtime (&now);
	time_str = asctime (timenow);
	length = strlen (time_str) + strlen (suffix) + 1;
	str_ret = (char *)malloc (length);
	bzero(str_ret,length);
	strcpy (str_ret, time_str);
	str_ret[strlen(time_str)-1] = '\0';
	strcat (str_ret, suffix);
	return str_ret;
}
