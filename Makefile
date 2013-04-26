objects = ftpserver.o recv_file.o mysocket.o access_to_mysql.o
server: ${objects}
	gcc ${objects} -Wall -std=gnu99 -O0 -o server -lmysqlclient -lpthread
ftpserver.o: myerror.h mysocket.h recv_file.h
recv_file.o: recv_file.h mysocket.h myerror.h
mysocket.o: mysocket.h myerror.h
access_to_mysql.o: access_to_mysql.h access_to_mysql.c
	gcc -c -Wall access_to_mysql.c -I/usr/include/mysql -L/usr/lib/mysql 
.PHONY: clean
clean:
	-rm *.o server wait_user_login

