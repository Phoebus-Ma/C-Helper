# Makefile.
CC = gcc
CFLAGS = -Wall -g -O0

SRC1 = tcp-server.c
SRC2 = tcp-client.c

OBJ1 = tcp-server
OBJ2 = tcp-client

all:
	$(CC) $(CFLAGS) -o $(OBJ1) $(SRC1)
	$(CC) $(CFLAGS) -o $(OBJ2) $(SRC2)

clean:
	$(RM) $(OBJ1) $(OBJ2) *.o *.*.sw?
