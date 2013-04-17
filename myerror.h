#ifndef _MY_ERROR_H_
#define _MY_ERROR_H_
#include <stdio.h>
#include <error.h>
#define print_error_location() fprintf(stderr,"-->%s,%s,%d,",__FILE__,__FUNCTION__,__LINE__)
#endif
