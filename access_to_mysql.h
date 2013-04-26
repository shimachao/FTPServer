#ifndef _ACCESS_TO_MYSQL
#define _ACCESS_TO_MYSQL

int init_connect_mysql();

int user_verify(char *name,char *password);

int insert_video_record(char *name,int userid);

#endif

