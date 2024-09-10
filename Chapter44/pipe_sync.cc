#include <iostream>
#include <sys/wait.h>
#include "lib/tlpi_hdr.h"
#include "lib/curr_time.h"

using namespace std;

int main(int argc, char *argv[]) {
    if(argc < 2) 
        errExit("input invalid param");
    int pfd[2];
    int dummy = 0;
    if(pipe(pfd) == -1) {
        errExit("pipe");
    }

    for(int i = 1; i < argc; i++) {
        switch (fork())
        {
        case -1:
            errExit("fork");
            break;
        case 0: // child process
        {
            if(close(pfd[0]) == -1) // read end is unused
                errExit("close");
            int sleep_time = atoi(argv[i]);
            sleep(sleep_time);
            printf("%s Child %d (PID=%ld) closing pipe\n", currTime("%T"), i, (long) getpid());
            if(close(pfd[1] == -1)) 
                errExit("close");
            
            exit(EXIT_SUCCESS);
        }
        default:
            break;
        }
    }

    if (close(pfd[1]) == -1) // write end is unused
        errExit("close");

    if(read(pfd[0], &dummy, 1) == -1)
        fatal("parent didn't get EOF");
    
    printf("%s Parent ready to go\n", currTime("%T"));
    
    exit(EXIT_SUCCESS);
}