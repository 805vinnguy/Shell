#ifndef CHILD_FUNCS_H
#define CHILD_FUNCS_H

#include <unistd.h>
#include <stdio.h>

struct child_pid_node {
    pid_t pid;
    struct child_pid_node* next;
};

#include "mush.h"
#include "parseline.h"
#include "stage.h"
#include "io.h"
#include "pipe_funcs.h"

#define EXIT_CHILD -1

/* FUNCTIONS */
pid_t safe_fork(void);

struct child_pid_node* make_child_pid_node(pid_t child_pid);

#endif