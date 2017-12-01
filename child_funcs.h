#ifndef CHILD_FUNCS_H
#define CHILD_FUNCS_H

#include "mush.h"
#include "parseline.h"
#include "stage.h"
#include "io.h"
#include <unistd.h>
#include <stdio.h>

#define EXIT_CHILD 2

struct child_pid_node {
    pid_t pid;
    struct child_pid_node* next;
};

/* FUNCTIONS */
pid_t safe_fork(void);

struct child_pid_node* make_child_pid_node(pid_t child_pid);

int child_exec(pid_t child_pid, struct stage* st);

#endif