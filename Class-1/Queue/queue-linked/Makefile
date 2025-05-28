# Makefile
CC = gcc
CFLAGS = -Wall -g -O0

SRC = main.c linked-queue.c

OBJ = linkqueue-test

$(OBJ) : $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) $(OBJ) *.o *.*.sw?
