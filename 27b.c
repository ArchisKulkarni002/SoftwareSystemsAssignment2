/*
============================================================================
Name : 27.c
Author : Archis Kulkarni
Description :  Write a program to receive messages from the message queue. 
a. with 0 as a flag 
b. with IPC_NOWAIT as a flag
Date: 19-09-2024
============================================================================
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// we will define simple struct for a message
struct message{
    long msg_type;
    char msg_text[1024];
};

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

    // create first message
    struct message mymsg;  

    // receive the message to queue
    int msgrtn=msgrcv(id, &mymsg, sizeof(mymsg.msg_text), 0,IPC_NOWAIT);
    if (msgrtn == -1) {
        perror("msgrcv failed");
        exit(EXIT_FAILURE);
    }

    printf("Message received: %s\n", mymsg.msg_text);
    
}

/*
./a.out
The generated key is: 1092630638
The generated message queue id is: 0
Message received: Hello there General Kenobi!

 ./a.out
The generated key is: 1092630638
The generated message queue id is: 0
msgrcv failed: No message of desired type


ipcs -q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages
0x4120386e 0          linuxboi   666        1024         0
*/
