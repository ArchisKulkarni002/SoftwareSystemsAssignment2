/*
============================================================================
Name : 10c.c
Author : Archis Kulkarni
Description : Write a separate program using sigaction system call to catch the following signals. 
   a. SIGSEGV 
   b. SIGINT 
c. SIGFPE
Date: 20-09-2024
============================================================================
*/
#include <signal.h>
#include <stdio.h>
#include<stdlib.h>

// this function will be called instead when we there is interrupt
void handler(){
    printf("Floating point error, you tried some illegal operation!\n");
    exit(0);
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

// test fpe
    printf("Generating a floating point error\n");
    int a = 1, b = 0;
    printf("%d\n", a / b);
               
}

/*
 ./a.out
Generating a floating point error
Floating point error, you tried some illegal operation!
*/