/*
============================================================================
Name : 23.c
Author : Archis Kulkarni
Description : Write a program to print the maximum number of files can be opened within a process and  
size of a pipe (circular buffer).
Date: 18-09-2024
============================================================================
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main() {

    long PIPE_BUF, OPEN_MAX;
    PIPE_BUF=pathconf(".", _PC_PIPE_BUF);
    OPEN_MAX = sysconf(_SC_OPEN_MAX);
    printf("Pipe buffere limit: %ld\n", PIPE_BUF);
    printf("Number of files limit: %ld\n", OPEN_MAX);
}

/*
 ./a.out
Pipe buffere limit: 4096
Number of files limit: 1024
*/
