/*
============================================================================
Name : 31b.c
Author : Archis Kulkarni
Description :  Write a program to create a semaphore and initialize value to the semaphore. 
a. create a binary semaphore 
b. create a counting semaphore
Date: 21-09-2024
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

union semun {
    int val;               
    struct semid_ds *buf; 
    unsigned short *array; 
};


int main() {
    // create a binary semaphore
    int id = semget(12345, 1, IPC_CREAT | 0744);
    if (id == -1) {
        perror("semget failed");
        exit(EXIT_FAILURE);
    }

    // initialize the counting semaphore to 10
    union semun arg;
    arg.val = 10; 

    int status=semctl(id, 0, SETVAL, arg);
    if (status == -1) {
        perror("semctl failed");
        exit(EXIT_FAILURE);
    }
    printf("Counting semaphore initialized to 10.\n");
}




/*
./a.out
Counting semaphore initialized to 10.

ipcs -s -i 1

Semaphore Array semid=1
uid=1000         gid=1000        cuid=1000       cgid=1000
mode=0744, access_perms=0744
nsems = 1
otime = Not set
ctime = Sat Sep 21 15:02:56 2024
semnum     value      ncount     zcount     pid
0          10         0          0          219752
*/
