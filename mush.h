#ifndef MUSH_H
#define MUSH_H

#include "builtins.h"
#include "parseline.h"
#include "stage.h"
#include "child_funcs.h"
#include "pipe_funcs.h"
#include "io.h"
#include <stdio.h>

struct process {
    int inputfile;
    int outputfile;
    char** argv;
    struct process* next;
};

/* FUNCTIONS */
void run_interactive(struct commandline* cmd);

/* void run_batch_processing(struct commandline* cmd, char* argv[]);
 */
void stage_loop(struct stage* stages);

struct process* stage_to_process(struct stage* stages);

int open_input_fd(struct stage** curr, struct stage* stages);

int open_output_fd(struct stage** curr, struct stage* stages);

char** nodelist_to_stringlist(struct stage* s);

#endif