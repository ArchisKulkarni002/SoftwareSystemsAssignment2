/*
============================================================================
Name : 2.c
Author : Archis Kulkarni
Description : Write a program to print the system resource limits. Use getrlimit system call. 
Date: 17-09-2024
============================================================================
*/
#include<sys/resource.h>
#include<stdio.h>
#include<stdlib.h>


void findRlimit(const char *resource_name, int resource) {
    struct rlimit lim;
    // check if getrlimit has errors
    int status=getrlimit(resource, &lim);
    if ( status== -1) {
        perror("getrlimit");
        exit(EXIT_FAILURE);
    }
    printf("%s: soft limit: %ld hard limit: %ld\n", resource_name,lim.rlim_cur,lim.rlim_max);
}

int main(){

    findRlimit("size of a file", RLIMIT_FSIZE);
    findRlimit("number of file descriptors", RLIMIT_NOFILE);
    findRlimit("number of processes", RLIMIT_NPROC);
    findRlimit("amount of resident set size", RLIMIT_AS);
    findRlimit("amount of memory", RLIMIT_DATA);
    findRlimit("amount of stack size", RLIMIT_STACK);
    findRlimit("size of nice value", RLIMIT_NICE);
    findRlimit("size message queues", RLIMIT_MSGQUEUE);
}

/*
 ./a.out
size of a file: soft limit: -1 hard limit: -1
number of file descriptors: soft limit: 1024 hard limit: 1048576
number of processes: soft limit: 31127 hard limit: 31127
amount of resident set size: soft limit: -1 hard limit: -1
amount of memory: soft limit: -1 hard limit: -1
amount of stack size: soft limit: 8388608 hard limit: -1
size of nice value: soft limit: 0 hard limit: 0
size message queues: soft limit: 819200 hard limit: 819200
 */