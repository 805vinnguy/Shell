CC=gcc
CFLAGS=-Wall -pedantic -g -O3
all: mush clean

mush: mush.o parseline.o stage.o builtins.o

mush.o: mush.c

parseline.o: parseline.c

stage.o: stage.c

builtins.o: builtins.c

clean:
	-rm *.o