#ifndef PIPE_FUNCS_H
#define PIPE_FUNCS_H

#include "mush.h"
#include "parseline.h"
#include "stage.h"
#include "child_funcs.h"
#include "io.h"
#include "builtins.h"
#include <unistd.h>

#define READ_END 0
#define WRITE_END 1

struct pipe_node {
    int pipe_io[2];
    struct pipe_node* next;
};

/* FUNCTIONS */
void safe_pipe(int pipefd[2]);

struct pipe_node* make_pipe(void);

struct pipe_node* make_pipeline(struct stage* stages);

#endif