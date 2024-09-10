#include <iostream>
#include <sys/wait.h>
#include "lib/tlpi_hdr.h"
#include "lib/curr_time.h"

using namespace std;

int main(int argc, char *argv[]) {
    int pfd[2];
    if(pipe(pfd) == -1) {
        errExit("pipe");
    }

    switch (fork())
    {
    case -1:
        errExit("fork");
        break;
    case 0: // child process
        {
            if(close(pfd[0]) == -1) 
                errExit("close");
            dup2(pfd[1], STDOUT_FILENO);
            printf("hello world kiki\n");
            exit(EXIT_SUCCESS);
        }
        break;
    default:
        {
            close(pfd[1]); 
            size_t numRead = 0;
            char buff[32];
            numRead = read(pfd[0], buff, 32);
            if (numRead > 0) {
                buff[numRead] = '\0';  // Null-terminate the string
                printf(" parent : %s", buff);
            }
        }
        break;
    }

    exit(EXIT_SUCCESS);
}