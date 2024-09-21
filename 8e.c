/*
============================================================================
Name : 8e.c
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>


void timer_handler(int signum) {
    printf("Interval done!\n");
}

int main(){

     struct itimerval timer;

    // set up signal handler
    signal(SIGALRM, timer_handler);

    // set timer for 10 sec and 10 microseconds
    timer.it_value.tv_sec = 10;
    timer.it_value.tv_usec = 10;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;

    // add the timer
    int status=setitimer(ITIMER_REAL, &timer, NULL);
    if (status == -1) {
        perror("timer setting failed");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        /* code */
    }
    

}
/*
 ./a.out
Interval done!
^C
 */