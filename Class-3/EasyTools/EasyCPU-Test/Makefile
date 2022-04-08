CC = gcc
CFLAGS = -Wall -g -O0

SRC = main.c cpu-test.c

OBJ = easyCPU-Test

$(OBJ) : $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ -lpthread

clean:
	$(RM) $(OBJ) *.o *.*.sw?