#ifndef MUSH_H
#define MUSH_H

#include "builtins.h"
#include "parseline.h"
#include "stage.h"
#include "child_funcs.h"
#include <stdio.h>

/* FUNCTIONS */
struct stage* parse(void);

void stage_loop(struct stage* stages);

#endif