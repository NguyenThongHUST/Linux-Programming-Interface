#include <iostream>
#include <sys/wait.h>
#include "lib/tlpi_hdr.h"


using namespace std;

int main() {
    FILE *fp = popen("sort", "w");
    if(fp == nullptr)
        errExit("popen");
    
    fprintf(fp, "banana\n");
    fprintf(fp, "apple\n");
    fprintf(fp, "cut\n");

    int status = pclose(fp);
    if (status == -1) {
        errExit("pclose");
    } else {
        if (WIFEXITED(status)) {
            printf("Command exited with status %d\n", WEXITSTATUS(status));
        }
    }

    exit(EXIT_SUCCESS);
}