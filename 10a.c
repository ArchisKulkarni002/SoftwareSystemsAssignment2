/*
============================================================================
Name : 10a.c
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

// this function will be called instead when we there is segmentation fault
void handler(){
    printf("Segmentation fault, check yo code!\n");
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

// test segmentation fault
    printf("Generating segment fault\n");
    int *ptr = NULL;
    *ptr = 42;
            
}

/*
./a.out
Generating segment fault
Segmentation fault, check yo code!
*/