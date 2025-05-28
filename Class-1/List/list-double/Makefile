# Makefile
CC = gcc
CFLAGS = -Wall -g -O0

SRC = main.c double-list.c

OBJ = doulist-test

$(OBJ) : $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) $(OBJ) *.o *.*.sw?
