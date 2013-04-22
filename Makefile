objects = ftpserver.o mypthread.o mysocket.o
server: ${objects}
	gcc ${objects} -Wall -std=gnu99 -O0 -o server -lpthread
ftpserver.o: myerror.h mysocket.h mypthread.h
mypthread.o: mypthread.h mysocket.h myerror.h
mysocket.o: mysocket.h myerror.h
.PHONY: clean
clean:
	rm *.o server

