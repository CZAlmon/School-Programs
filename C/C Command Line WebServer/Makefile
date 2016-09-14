CC = gcc
FLAGS = -Wall
LIBS = -pthread
OBJS = TCPEchoServer-Fork
SRCS = TCPEchoServer-Fork.c


all: clean TCPEchoServer-Fork

TCPEchoServer-Fork : TCPEchoServer-Fork.o
	$(CC) $(FLAGS) $(LIBS) -o TCPEchoServer-Fork TCPEchoServer-Fork.c AcceptTCPConnection.c CreateTCPServerSocket.c DieWithError.c HandleTCPClient.c TCPEchoServer.h

clean:
	rm -f $(OBJS) *.o
