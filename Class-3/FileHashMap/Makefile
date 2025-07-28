CC = gcc
CFLAGS = -Wall -g -O0

SRC = main.c

OBJ = log_reader

$(OBJ) : $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) $(OBJ) *.o *.*.sw?
