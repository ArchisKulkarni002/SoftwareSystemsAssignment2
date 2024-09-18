/*
============================================================================
Name : 12.c
Author : Archis Kulkarni
Description : Write a program to create an orphan process. Use kill system call to send SIGKILL signal to 
the parent process from the child process.
Date: 17-09-2024
============================================================================
*/
#include<sys/types.h>
#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>

int main(){
    
    // we fork the process and create a new child process, 
    pid_t pid=fork();

    // then we write the child and parent process ids

    // child process continues to be there for user ip, after killing parent
    if(pid==0){
        printf("Child process id: %d exiting now\n", getpid());
        printf("Child killing parent now\n");

        int status = kill(getppid(), SIGKILL);
        // if theres an error
        if (status==-1)
        {
            perror("error while killing");
            exit(EXIT_FAILURE);
        }

// run while loop so it does not terminate and becomes zombie
        while (1)
        {
            /* code */
        }
        
    }

    // parent process killed and exits before child does, creating orphan
    else if(pid>0){
        printf("Parent process id: %d\n", getpid());
        printf("Parent ded now, bye bye");

        // exit(0);
    }
       
}

/*
SoftwareSystemsAssignment2/a.out
Parent process id: 51343
Parent ded now, bye byeChild process id: 51344 exiting now
Child killing parent now

cat /proc/51344/status | grep State
State:  R (running)
*/