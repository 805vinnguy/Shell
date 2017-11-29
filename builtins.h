#ifndef CHANGEWORKDIR_H
#define CHANGEWORKDIR_H

#include "mush.h"
#include "parseline.h"
#include "stage.h"
#include <unistd.h>

void my_cd(char* path);

void my_exit(struct commandline* cmd);

#endif