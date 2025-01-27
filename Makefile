CC = gcc
CCFLAGS = -Wall -Wextra -Wvla -Werror -std=c99
FILES = ex3.c
TARGET = matrix_lib.o

matrix_lib: ex3.c ex3.h
	$(CC) $(CCFLAGS) -c $(FILES) -o $(TARGET)

clean:
	rm -f *.o
