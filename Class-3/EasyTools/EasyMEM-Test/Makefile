CC = gcc
CFLAGS = -Wall -g -O0

SRC = main.c mem-test.c mem-algo.c

OBJ = easyMEM-test

$(OBJ) : $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) $(OBJ) *.o *.*.sw?