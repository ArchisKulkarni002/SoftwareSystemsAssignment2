/*
============================================================================
Name : 13b.c
Author : Archis Kulkarni
Description : Write two programs: first program is waiting to catch SIGSTOP signal, the second program 
will send the signal (using kill system call). Find out whether the first program is able to catch 
the signal or not.
Date: 17-09-2024
============================================================================
*/
#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>


int main(int argc, char* argv[]){

    int status = kill(atoi(argv[1]), SIGKILL);
    printf("Killing process %d\n",atoi(argv[1]));
    // if theres an error
    if (status==-1)
    {
        perror("error while killing");
        exit(EXIT_FAILURE);
    }
        
}

/*

*/