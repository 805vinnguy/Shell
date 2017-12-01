#ifndef CHILD_FUNCS_H
#define CHILD_FUNCS_H

#include "mush.h"
#include "parseline.h"
#include "stage.h"
#include <unistd.h>

/* FUNCTIONS */
pid_t safe_fork(void);

int child_exec(pid_t child_pid, struct stage* st);

#endif