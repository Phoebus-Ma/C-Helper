# Makefile
CC = gcc
CFLAGS = -Wall -g -O0

SRC = main.c sequence-list.c

OBJ = seqlist-test

$(OBJ) : $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) $(OBJ) *.o *.*.sw?