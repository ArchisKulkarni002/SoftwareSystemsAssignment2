/*
============================================================================
Name : 18.c
Author : Archis Kulkarni
Description :  Write a program to execute ls -l | wc. 
a. use dup 
b. use dup2 
c. use fcntl
Date: 21-09-2024
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];
    // create a pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // create  child process (ls)
    int cpid=fork();
    if ( cpid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (cpid == 0) {
        close(pipefd[0]);
        dup2(pipefd[1], 1);  
        close(pipefd[1]);
        execlp("ls", "ls", "-l", NULL);
    }

    // create  child process (grep)
    int cpid1=fork();
    int pipefd1[2];
    if (pipe(pipefd1) == -1) {
        perror("pipe2");
        exit(EXIT_FAILURE);
    }
    if ( cpid1 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (cpid1 == 0) {
        close(pipefd[1]);
        dup2(pipefd[0], 0);  
        close(pipefd[0]);

        close(pipefd1[0]);
        dup2(pipefd1[1], 1);  
        close(pipefd1[1]);
        execlp("grep", "grep", "^d", NULL);
    }

    // closing the write end of pipe
    close(pipefd1[1]); 
    dup2(pipefd1[0],0);   
    close(pipefd1[0]); 
    execlp("wc", "wc", NULL);
    perror("execlp wc");
    exit(EXIT_FAILURE);

    close(pipefd[0]);
    close(pipefd[1]);
    close(pipefd1[0]);
    close(pipefd1[1]);
    wait(NULL);

}


/*
./a.out
      0       0       0
*/
