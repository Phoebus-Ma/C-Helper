# Makefile.
CC = gcc
CFLAGS = -Wall -g -O0

SRC = main.c

OBJ = thread-spin

$(OBJ) : $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ -lpthread

clean:
	$(RM) $(OBJ) *.o *.*.sw?
