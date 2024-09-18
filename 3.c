/*
============================================================================
Name : 3.c
Author : Archis Kulkarni
Description : Write a program to set (any one) system resource limit. Use setrlimit system call.   
Date: 17-09-2024
============================================================================
*/
#include<sys/resource.h>
#include<stdio.h>
#include<stdlib.h>
    

int main(){

    // set the limits for the resource
    struct rlimit lim;
    lim.rlim_cur=10;
    lim.rlim_max=100;

    // check if setrlimit has errors
    
    int status=setrlimit(RLIMIT_NOFILE, &lim);
    if ( status== -1) {
        perror("setrlimit");
        exit(EXIT_FAILURE);
    }
    printf("setting values to: soft limit: 10 hard limit: 100\n");


// check if getrlimit has errors
    int status1=getrlimit(RLIMIT_NOFILE, &lim);
    if ( status1== -1) {
        perror("getrlimit");
        exit(EXIT_FAILURE);
    }
    printf("getrlimit values: soft limit: %ld hard limit: %ld\n", lim.rlim_cur,lim.rlim_max);
}

/*
  ./a.out
setting values to: soft limit: 10 hard limit: 100
getrlimit values: soft limit: 10 hard limit: 100
 */