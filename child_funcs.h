#ifndef CHILD_FUNCS_H
#define CHILD_FUNCS_H

#include "mush.h"
#include "parseline.h"
#include "stage.h"
#include "io.h"
#include <unistd.h>
#include <stdio.h>

#define EXIT_CHILD 2

/* FUNCTIONS */
pid_t safe_fork(void);

int child_exec(pid_t child_pid, struct stage* st);

#endif