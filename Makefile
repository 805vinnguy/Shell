CC=gcc
CFLAGS=-Wall -pedantic -g -O3
all: mush clean

mush: mush.o

mush.o: mush.c

clean:
	-rm *.o