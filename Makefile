objects = ftpserver.o recv_file.o mysocket.o access_to_mysql.o
server: ${objects}
	gcc ${objects} -Wall -std=gnu99 -O0 -o server -lmysqlclient -lpthread
ftpserver.o: myerror.h mysocket.h recv_file.h
recv_file.o: recv_file.h mysocket.h myerror.h
mysocket.o: mysocket.h myerror.h
access_to_mysql.o: access_to_mysql.h access_to_mysql.c
	gcc -c -Wall access_to_mysql.c -I/usr/include/mysql -L/usr/lib/mysql 
wati_user_login.o:wait_user_login.c access_to_mysql.h
	gcc -c -Wall wait_user_login.c
wait_user_login:access_to_mysql.o wait_user_login.o
	gcc -Wall access_to_mysql.o wait_user_login.o -std=gnu99 -lmysqlclient -o wait_user_login
.PHONY: clean
clean:
	-rm *.o server wait_user_login

