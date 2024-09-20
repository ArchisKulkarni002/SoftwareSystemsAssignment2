/*
============================================================================
Name : 24.c
Author : Archis Kulkarni
Description : Write a program to create a message queue and print the key and message queue id.
Date: 19-09-2024
============================================================================
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>


int main() {
    // well use the ftok function to generate a key for the queue
    key_t key = ftok("24.c",65);
    if (key == -1) {
        perror("ftok failed");
        exit(EXIT_FAILURE);
    }
    printf("The generated key is: %d\n",key);

// we generate a message queue, use of IPC_CREAT is important
    int id=msgget(key, 0666 | IPC_CREAT);
    if (id==-1)
    {
        perror("message queue creation failed");
        exit(EXIT_FAILURE);
    }
    printf("The generated message queue id is: %d\n",id);    
    
}

/*
  ./a.out
The generated key is: 1092630638
The generated message queue id is: 0

ipcs -q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages
0x4120386e 0          linuxboi   666        0            0
*/
