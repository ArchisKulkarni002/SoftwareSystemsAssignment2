/*
============================================================================
Name : 25.c
Author : Archis Kulkarni
Description : Write a program to print a message queue's  (use msqid_ds and ipc_perm structures) 
a. access permission 
b. uid, gid 
c. time of last message sent and received    
d. time of last change in the message queue 
d. size of the queue 
f. number of messages in the queue  
g. maximum number of bytes allowed  
h. pid of the msgsnd and msgrcv 
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

    //print the required values
    printf("Permissions: %d\n",buffer.msg_perm.mode); 
    printf("UID: %d\n",buffer.msg_perm.uid); 
    printf("GID: %d\n",buffer.msg_perm.gid); 
    printf("Last message sent: %ld\n",buffer.msg_stime); 
    printf("Last message received: %ld\n",buffer.msg_rtime); 
    printf("Size of message queue: %ld\n",buffer.msg_cbytes); 
    printf("Number of messages queue: %ld\n",buffer.msg_qnum); 
    printf("Number of bytes allowed: %ld\n",buffer.msg_qbytes); 
    printf("Last process to send message: %d\n",buffer.msg_lspid); 
    printf("Last process to receive message: %d\n",buffer.msg_lrpid); 
    
}

/*
  ./a.out
./a.out
The generated key is: 1092630638
The generated message queue id is: 0
Permissions: 438
UID: 1000
GID: 1000
Last message sent: 0
Last message received: 0
Size of message queue: 0
Number of messages queue: 0
Number of bytes allowed: 16384
Last process to send message: 0
Last process to receive message: 0


ipcs -q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages
0x4120386e 0          linuxboi   666        0            0
*/
