# Makefile.
CC = gcc
CFLAGS = -Wall -g -O0

SRC1 = tcp-client.c
SRC2 = tcp-server.c
SRC3 = udp-client.c
SRC4 = udp-server.c

OBJ1 = tcp-client
OBJ2 = tcp-server
OBJ3 = udp-client
OBJ4 = udp-server

$(OBJ1) : $(SRC1)
	$(CC) $(CFLAGS) -o $(OBJ1) $(SRC1)
	$(CC) $(CFLAGS) -o $(OBJ2) $(SRC2) -lpthread
	$(CC) $(CFLAGS) -o $(OBJ3) $(SRC3)
	$(CC) $(CFLAGS) -o $(OBJ4) $(SRC4) -lpthread

clean:
	$(RM) $(OBJ1) $(OBJ2) $(OBJ3) $(OBJ4) *.o *.*.sw?
