# Makefile
CC = gcc
CFLAGS = -Wall -g -O0

SRC = main.c linked-stack.c

OBJ = linkedstack-test

$(OBJ) : $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) $(OBJ) *.o *.*.sw?