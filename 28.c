/*
============================================================================
Name : 25.c
Author : Archis Kulkarni
Description : Write a program to change the exiting message queue permission. (use msqid_ds structure) 
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
    
    // we get the info of msgs using msgctl into msqui_ds struct
    struct msqid_ds buffer;
    int status=msgctl(id, IPC_STAT, &buffer);
    if (status==-1)
    {
        perror("getting info on messages failed");
        exit(EXIT_FAILURE);
    }

    // set the permissions
    buffer.msg_perm.mode = 0665;
    int status1=msgctl(id, IPC_SET, &buffer);
    if (status1==-1)
    {
        perror("setting info on messages failed");
        exit(EXIT_FAILURE);
    }

    //print the required values
    printf("Updated permissions: %o\n",buffer.msg_perm.mode); 
    
}

/*
 ./a.out
The generated key is: 1092630638
The generated message queue id is: 0
Updated permissions: 665

--Before--
ipcs -q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages
0x4120386e 0          linuxboi   666        0            0


--After--
 ipcs -q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages
0x4120386e 0          linuxboi   665        0            0
*/
