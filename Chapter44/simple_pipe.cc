
#include <iostream>
#include <sys/wait.h>
#include "lib/tlpi_hdr.h"

using namespace std;

#define BUF_SIZE 10

int main(int argc, char *argv[]) {
    int pfd[2];
    char buf[BUF_SIZE];
    if(argc < 2 ) 
        errExit("input invalid param");

    if(pipe(pfd) == -1)
        errExit("error pipe");

    switch (fork())
    {
    case -1:
        cout << "error fork\n";
        break;
    
    case 0: // child process
        if (close(pfd[1]) == -1)
            errExit("close-child");
            
        for(;;) {
            size_t numRead = read(pfd[0], buf, BUF_SIZE);
            if(numRead == -1)
                errExit("read");
            if(numRead == 0)
                break;  /* End-of-file */
            
            if (write(STDOUT_FILENO, buf, numRead) != numRead)
                fatal("child - partial/failed write");
        }
        write(STDOUT_FILENO, "\n", 1);
        if(close(pfd[0]) == -1)
            errExit("close");

        _exit(EXIT_SUCCESS);
        break;
    default: // parent process
        if(close(pfd[0]) == -1) 
            errExit("close-parent");
        if (write(pfd[1], argv[1], strlen(argv[1])) != strlen(argv[1]))
            fatal("parent - partial/failed write");
        
        if (close(pfd[1]) == -1) 
            errExit("close");
        
        wait(NULL);
        exit(EXIT_SUCCESS);
        break;
    }
    return 0;
}