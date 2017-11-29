#include "builtins.h"

void my_cd(char* path) {
    if(chdir(path) == -1) {
        perror("cd");
        /*PROMPT*/
    }
}

