CC = gcc
AR = ar

CFLAGS1 = -c
CFLAGS2 = crv
CFLAGS3 = -Wall -g -O0

SRC0 = calculate.c
OBJ0 = calculate.o

SRC1 = calculate.o
OBJ1 = libcalculate.a

SRC2 = main.c
OBJ2 = libtest

all:
	$(CC) $(CFLAGS1) -o $(OBJ0) $(SRC0)
	$(AR) $(CFLAGS2) -o $(OBJ1) $(SRC1)
	$(CC) $(CFLAGS3) -o $(OBJ2) $(SRC2) -L. -lcalculate

clean:
	$(RM) $(OBJ0) $(OBJ1) $(OBJ2) *.o *.*.sw? *.a
