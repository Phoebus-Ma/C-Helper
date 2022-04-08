CC = gcc
CFLAGS = -Wall -g -O0

SRC = main.c disk-test.c

OBJ = easyDisk-Test

$(OBJ) : $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ -lpthread

clean:
	$(RM) $(OBJ) *.o *.*.sw?