/*
============================================================================
Name : 30b.c
Author : Archis Kulkarni
Description :  Write a program to create a shared memory. 
a. write some data to the shared memory 
b. attach with O_RDONLY and check whether you are able to overwrite. 
c. detach the shared memory 
d. remove the shared memory
Date: 21-09-2024
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    int id;
    key_t key = 1234;
    char *ptr;

    // create a shared memory segment
    id = shmget(key, 1024, IPC_CREAT | 0666);
    if (id < 0) {
        perror("shmget failed");
        exit(EXIT_FAILURE);
    }

    // attach the shared memory segment
    ptr = shmat(id, NULL, SHM_RDONLY);
    if (ptr == (char *)(-1)) {
        perror("shmat failed");
        exit(EXIT_FAILURE);
    }

    // write data to the shared memory
    const char *data = "Hello There!";
    strncpy(ptr, data, 1024);

    printf("Data written to shared memory: %s\n", ptr);

}



/*
./a.out
Segmentation fault

ipcs -m

------ Shared Memory Segments --------
key        shmid      owner      perms      bytes      nattch     status

0x000004d2 0          linuxboi   666        1024       0
*/
