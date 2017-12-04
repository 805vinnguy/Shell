#include "io.h"

int safe_dup2(int oldfd, int newfd) {
    if( (dup2(oldfd, newfd)) == -1) {
        perror("dup2");
        exit(1);
    }
    return newfd;
}