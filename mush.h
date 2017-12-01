#ifndef MUSH_H
#define MUSH_H

#include "builtins.h"
#include "parseline.h"
#include "stage.h"
#include "child_funcs.h"
#include "io.h"
#include <stdio.h>

struct child_pid_node {
    pid_t pid;
    struct child_pid_node* next;
};

/* FUNCTIONS */
void stage_loop(struct stage* stages);

#endif