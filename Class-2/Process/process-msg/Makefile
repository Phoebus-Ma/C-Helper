# Makefile.
CC = gcc
CFLAGS = -Wall -g -O0

SRC = main.c

OBJ = process-msg

$(OBJ) : $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) $(OBJ) *.o *.*.sw?
