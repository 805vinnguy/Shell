#ifndef IO_H
#define IO_H

#define INPUT_STDIN "original stdin"
#define OUTPUT_STDOUT "original stdout"
#define INPUT_PIPE "pipe from stage"
#define OUTPUT_PIPE "pipe to stage"

#include "mush.h"
#include "parseline.h"
#include "builtins.h"
#include "stage.h"
#include "child_funcs.h"
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

/* FUNCTIONS */
int get_input(struct stage* st);

int safe_dup2(int oldfd, int newfd);

#endif