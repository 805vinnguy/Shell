#ifndef CHANGEWORKDIR_H
#define CHANGEWORKDIR_H

#include "mush.h"
#include "parseline.h"
#include "stage.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void my_cd(struct node* list);

void safe_system(char* command);

void safe_cd(char* path);

void my_exit(struct commandline* cmd);

#endif