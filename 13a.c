/*
============================================================================
Name : 13a.c
Author : Archis Kulkarni
Description : Write two programs: first program is waiting to catch SIGSTOP signal, the second program 
will send the signal (using kill system call). Find out whether the first program is able to catch 
the signal or not.
Date: 17-09-2024
============================================================================
*/
#include<sys/types.h>
#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>

// this function will be called instead when we press ctrl+c in running program
void handler(){
    printf("I see you tried to stop the program, but we changed that logic!\n");
}

int main(){

    //we make a signal call to change the default behaviour of SIGSTOP
    // now pressing ctrl+c does not stop the program
    __sighandler_t result= signal(SIGSTOP, handler);
    
    // if theres an error
    if (result==SIG_ERR)
    {
        perror("signal error");
        exit(EXIT_FAILURE);
    }

    printf("Current process id is: %d", getpid());
    
    while (1)
    {
        /* code */
    }
           
}

/*
./a.out
signal error: Invalid argument
*/