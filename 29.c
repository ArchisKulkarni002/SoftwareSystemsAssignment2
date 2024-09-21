/*
============================================================================
Name : 29.c
Author : Archis Kulkarni
Description : Write a program to remove the message queue.
Date: 20-09-2024
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
    
    // we remove message queue using msgctl 
    int status=msgctl(id, IPC_RMID, NULL);
    if (status==-1)
    {
        perror("removing message queue failed");
        exit(EXIT_FAILURE);
    }

    //print the required values
    printf("Removed message queue id: %d\n",id); 
    
}

/*
./a.out
The generated key is: 1092630638
The generated message queue id is: 0
Removed message queue id: 0

--Before--
ipcs -q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages
0x4120386e 0          linuxboi   665        0            0


--After--
  ipcs -q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages

*/
