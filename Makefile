objects = ftpserver.o recv_file.o mysocket.o access_to_mysql.o random_name.o md5_encrypt.o
server: ${objects}
	gcc ${objects} -Wall -std=gnu99 -O0 -o server -lmysqlclient -lcrypto -lpthread
random_name.o:random_name.c
ftpserver.o: myerror.h mysocket.h recv_file.h
recv_file.o: recv_file.h mysocket.h myerror.h
mysocket.o: mysocket.h myerror.h
access_to_mysql.o: access_to_mysql.h access_to_mysql.c
	gcc -c -Wall access_to_mysql.c -I/usr/include/mysql -L/usr/lib/mysql 
md5_encrypt.o:md5_encrypt.h md5_encrypt.c
	gcc -c -std=gnu99 md5_encrypt.c
.PHONY: clean
clean:
	-rm *.o server 

