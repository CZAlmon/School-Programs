CFLAGS = -Wall
CPPFLAGS = -Wall

all: server_fixed mcput mcget mcdel mclist

csapp.h:
	wget http://csapp.cs.cmu.edu/2e/ics2/code/include/csapp.h

csapp.c:
	wget http://csapp.cs.cmu.edu/2e/ics2/code/src/csapp.c

csapp.o: csapp.h csapp.c

server_fixed: server_fixed.cpp csapp.o 
	g++ $(CPPFLAGS) server_fixed.cpp csapp.o -g -lpthread -o server

mcput: mcput.cpp csapp.o 
	g++ $(CPPFLAGS) mcput.cpp csapp.o -g -lpthread -o mcput

mcget: mcget.cpp csapp.o
	g++ $(CPPFLAGS) mcget.cpp csapp.o -g -lpthread -o mcget

mcdel: mcdel.cpp csapp.o
	g++ $(CPPFLAGS) mcdel.cpp csapp.o -g -lpthread -o mcdel

mclist: mclist.cpp csapp.o
	g++ $(CPPFLAGS) mclist.cpp csapp.o -g -lpthread -o mclist

.PHONY: clean
clean:
	/bin/rm -rf csapp.h csapp.c *.o server mcput mcget mcdel mclist
