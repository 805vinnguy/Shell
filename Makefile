CC=gcc
CFLAGS=-Wall -pedantic -g -O3
all: mush clean

mush: mush.o parseline.o stage.o builtins.o child_funcs.o io.o pipe_funcs.o

mush.o: mush.c

parseline.o: parseline.c

stage.o: stage.c

builtins.o: builtins.c

child_funcs.o: child_funcs.c

io.o: io.c

pipe_funcs.o: pipe_funcs.c

clean:
	-rm *.o