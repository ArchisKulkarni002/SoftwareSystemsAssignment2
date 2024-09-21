/*
============================================================================
Name : 8d.c
Author : Archis Kulkarni
Description : Write a separate program using signal system call to catch the following signals. 
   a. SIGSEGV 
   b. SIGINT 
   c. SIGFPE 
   d. SIGALRM (use alarm system call) 
   e. SIGALRM (use setitimer system call) 
   f. SIGVTALRM (use setitimer system call) 
   g. SIGPROF (use setitimer system call)
Date: 20-09-2024
============================================================================
*/
#include <signal.h>
#include <stdio.h>
#include<stdlib.h>
#include<unistd.h>

// this function will be called instead when there is an alarm timeout
void handler(){
    printf("Alarm timed offf!\n");
    exit(0);
}
int main (){  
    //we make a signal call to change the default behaviour of SIGINT
    // now pressing ctrl+c does not stop the program
    __sighandler_t result= signal(SIGALRM, handler);
    
    // if theres an error
    if (result==SIG_ERR)
    {
        perror("signal error");
        exit(EXIT_FAILURE);
    }

// test fpe
    printf("Setting up alarm\n");
    alarm(5);
    while (1)
    {
        /* code */
    }
               
}

/*
./a.out
Setting up alarm
Alarm timed offf!
*/