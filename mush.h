#ifndef MUSH_H
#define MUSH_H

struct process {
    int inputfile;
    int outputfile;
    char** argv;
    struct process* next;
};

#include "builtins.h"
#include "parseline.h"
#include "stage.h"
#include "child_funcs.h"
#include "pipe_funcs.h"
#include "io.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

/* FUNCTIONS */
void run_interactive(struct commandline* cmd);

void run_batch_processing(struct commandline* cmd, char* argv[]);

void stage_loop(struct process* processes);

void wait_all(struct child_pid_node* list);

void cleanup(struct process* processes);

void safe_close(int fd);

void set_pipes(struct process* processes);

struct process* stage_to_process(struct stage* stages);

int open_input_fd(struct stage** curr, struct stage* stages);

int open_output_fd(struct stage** curr, struct stage* stages);

char** nodelist_to_stringlist(struct stage* s);

int process_list_size(struct process* processes);

struct child_pid_node* add_child_pid(struct child_pid_node* tail,
                                     pid_t child_pid);

#endif