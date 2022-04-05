CC = gcc
CFLAGS = -Wall -g -O0

SRC = main.c singlelist.c

OBJ = singlelist-test

$(OBJ) : $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) $(OBJ) *.o *.*.sw?
