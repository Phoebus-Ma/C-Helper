CC = gcc
CFLAGS = -Wall -g -O0

SRC = main.c singlylist.c

OBJ = singlylist-test

$(OBJ) : $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) $(OBJ) *.o *.*.sw?