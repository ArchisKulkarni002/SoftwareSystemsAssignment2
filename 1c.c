/*
============================================================================
Name : 1c.c
Author : Archis Kulkarni
Description : Write a separate program (for each time domain) to set a interval timer in 10sec and 
10micro second 
a. ITIMER_REAL 
b. ITIMER_VIRTUAL 
c. ITIMER_PROF 
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
    signal(SIGPROF, timer_handler);

    // set timer for 10 sec and 10 microseconds
    timer.it_value.tv_sec = 10;
    timer.it_value.tv_usec = 10;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;

    // add the timer
    int status=setitimer(ITIMER_PROF, &timer, NULL);
    if (status == -1) {
        perror("timer setting failed");
        exit(EXIT_FAILURE);
    }

    long lolz=0;
    while (1)
    {
        lolz++;   
    }
    

}
/*
 ./a.out
Interval done!
^C
 */