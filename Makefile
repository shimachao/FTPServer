objects = ftpserver.o recv_file.o mysocket.o
server: ${objects}
	gcc ${objects} -Wall -std=gnu99 -O0 -o server -lpthread
ftpserver.o: myerror.h mysocket.h recv_file.h
recv_file.o: recv_file.h mysocket.h myerror.h
mysocket.o: mysocket.h myerror.h
.PHONY: clean
clean:
	-rm *.o server

