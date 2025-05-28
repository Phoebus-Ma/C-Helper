# Makefile
CC = gcc
CFLAGS = -Wall -g -O0

SRC = main.c sequence-queue.c

OBJ = sequeue-test

$(OBJ) : $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) $(OBJ) *.o *.*.sw?
