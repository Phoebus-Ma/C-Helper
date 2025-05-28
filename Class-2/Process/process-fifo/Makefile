# Makefile.
CC = gcc
CFLAGS = -Wall -g -O0

SRC = main.c

OBJ0 = process-fifo
OBJ1 = test_fifo

all:
	$(CC) $(CFLAGS) -o $(OBJ0) $(SRC)

clean:
	$(RM) $(OBJ0) $(OBJ1) *.o *.*.sw?
