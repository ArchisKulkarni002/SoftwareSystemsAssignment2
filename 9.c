/*
============================================================================
Name : 9.c
Author : Archis Kulkarni
Description : Write a program to ignore a SIGINT signal then reset the default action of the SIGINT 
signal -  Use signal system call.
Date: 17-09-2024
============================================================================
*/
#include <signal.h>
#include <stdio.h>
#include<stdlib.h>

// this function will be called instead when we press ctrl+c in running program
void handler(){
    printf("I see you tried to stop the program, but we changed that logic!\n");
}
int main (){  
    //we make a signal call to change the default behaviour of SIGINT
    // now pressing ctrl+c does not stop the program
    __sighandler_t result= signal(SIGINT, handler);
    
    // if theres an error
    if (result==SIG_ERR)
    {
        perror("signal error");
        exit(EXIT_FAILURE);
    }

// run while loop to test ctrl+c change
    printf("Running a while loop\n");
    while (1)
    {
        /* code */
    }
    
    
}
