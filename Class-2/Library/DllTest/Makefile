CC = gcc

CFLAGS1 = -shared -fPIC
CFLAGS2 = -Wall -g -O0

SRC0 = calculate.c
OBJ0 = calculate.so

SRC1 = main.c
OBJ1 = dlltest

all:
	$(CC) $(CFLAGS1) -o $(OBJ0) $(SRC0)
	$(CC) $(CFLAGS2) -o $(OBJ1) $(SRC1) -ldl

clean:
	$(RM) $(OBJ0) $(OBJ1) *.o *.*.sw? *.so
