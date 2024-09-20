/*
============================================================================
Name : 26.c
Author : Archis Kulkarni
Description : Write a program to send messages to the message queue. Check $ipcs -q
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
    mymsg.msg_type=1;
    strcpy(mymsg.msg_text,"Hello there General Kenobi!");  

    // send the message to queue
    int msgrtn=msgsnd(id, &mymsg, sizeof(mymsg.msg_text), 0);
    if (msgrtn == -1) {
        perror("msgsnd failed");
        exit(EXIT_FAILURE);
    }

    printf("Message sent: %s\n", mymsg.msg_text);
    
}

/*
./a.out
The generated key is: 1092630638
The generated message queue id is: 0
Message sent: Hello there General Kenobi!


ipcs -q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages
0x4120386e 0          linuxboi   666        1024         1
*/
