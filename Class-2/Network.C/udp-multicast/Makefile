# Makefile.
CC = gcc
CFLAGS = -Wall -g -O0

SRC1 = udp-client.c
SRC2 = udp-server.c

OBJ1 = udp-client
OBJ2 = udp-server

all:
	$(CC) $(CFLAGS) -o $(OBJ1) $(SRC1)
	$(CC) $(CFLAGS) -o $(OBJ2) $(SRC2)

clean:
	$(RM) $(OBJ1) $(OBJ2) *.o *.*.sw?
