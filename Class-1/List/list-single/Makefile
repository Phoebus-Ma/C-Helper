# Makefile
CC = gcc
CFLAGS = -Wall -g -O0

SRC = main.c single-list.c

OBJ = sinlist-test

$(OBJ) : $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) $(OBJ) *.o *.*.sw?
