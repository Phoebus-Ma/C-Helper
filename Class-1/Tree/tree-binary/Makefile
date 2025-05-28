# Makefile
CC = gcc
CFLAGS = -Wall -g -O0

SRC = main.c binary-tree.c

OBJ = bintree-test

$(OBJ) : $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) $(OBJ) *.o *.*.sw?
