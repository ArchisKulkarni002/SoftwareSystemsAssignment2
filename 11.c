/*
============================================================================
Name : 11.c
Author : Archis Kulkarni
Description :  Write a program to ignore a SIGINT signal then reset the default act of the SIGINT signal -  
use sigaction system call.
Date: 17-09-2024
============================================================================
*/
#include <signal.h>
#include <stdio.h>
#include<stdlib.h>

// this function will be called instead when we press ctrl+c in running program
void handler(){
    printf("I see you again tried to stop the program, but we changed that logic, Again!\n");
}
int main (){  

    struct sigaction act;
    act.sa_handler=handler;
    //we make a signal call to change the default behaviour of SIGINT
    // now pressing ctrl+c does not stop the program
    int result= sigaction(SIGINT, &act, NULL);
    
    // if theres an error
    if (result==-1)
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
