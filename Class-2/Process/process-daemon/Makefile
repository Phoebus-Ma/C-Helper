# Makefile.
CC = gcc
CFLAGS = -Wall -g -O0

SRC = main.c

OBJ = process-daemon

$(OBJ) : $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) $(OBJ) *.o *.*.sw?
