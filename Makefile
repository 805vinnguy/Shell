CC=gcc
CFLAGS=-Wall -pedantic -g -O3
all: mush clean

mush: mush.o parseline.o stage.o

mush.o: mush.c

parseline.o: parseline.c

stage.o: stage.c

clean:
	-rm *.o