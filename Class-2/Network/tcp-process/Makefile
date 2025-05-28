# Makefile.
CC = gcc
CFLAGS = -Wall -g -O0

SRC1 = tcp-client.c
SRC2 = tcp-server.c

OBJ1 = tcp-client
OBJ2 = tcp-server

all:
	$(CC) $(CFLAGS) -o $(OBJ1) $(SRC1)
	$(CC) $(CFLAGS) -o $(OBJ2) $(SRC2)

clean:
	$(RM) $(OBJ1) $(OBJ2) *.o *.*.sw?
