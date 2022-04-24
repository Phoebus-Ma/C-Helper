# Makefile.
CC = gcc
CFLAGS = -Wall -g -O0

SRC0 = main.c
SRC1 = showenv.c

OBJ0 = process-exec
OBJ1 = showenv

all:
	$(CC) $(CFLAGS) -o $(OBJ0) $(SRC0)
	$(CC) $(CFLAGS) -o $(OBJ1) $(SRC1)

clean:
	$(RM) $(OBJ0) $(OBJ1) *.o *.*.sw?
