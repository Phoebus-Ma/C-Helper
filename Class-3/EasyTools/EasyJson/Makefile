CC = gcc
CFLAGS = -Wall -g -O0

SRC = main.c easyjson.c

OBJ = easyJson

$(OBJ) : $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) $(OBJ) *.o *.*.sw?