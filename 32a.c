/*
============================================================================
Name : 32a.c
Author : Archis Kulkarni
Description :   Write a program to implement semaphore to protect any critical section. 
a. rewrite the ticket number creation program using semaphore 
b. protect shared memory from concurrent write access 
c. protect multiple pseudo resources ( may be two) using counting semaphore 
d. remove the created semaphore   
Date: 22-09-2024
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>

int id;
int ticket_number = 0;

void wait(int id) {
    struct sembuf p = {0, -1, 0}; 
    semop(id, &p, 1);
}

void signal(int id) {
    struct sembuf v = {0, 1, 0}; 
    semop(id, &v, 1);
}

void *createTicket(void *arg) {
    for (int i = 0; i < 3; i++) {
        wait(id);         
        // critical section
        ticket_number++;
        printf(" Random generated ticket number is: %d\n", ticket_number);
        
        signal(id); 
        sleep(1); 
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // create semaphore
    id = semget(1234, 1, IPC_CREAT | 0666);
    semctl(id, 0, SETVAL, 1); 

    // create multiple threads to simulate parallel access
    pthread_create(&thread1, NULL, createTicket, NULL);
    pthread_create(&thread2, NULL, createTicket, NULL);

    // wait for threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // remove semaphore
    semctl(id, 0, IPC_RMID); 
}

/*
./a.out
 Random generated ticket number is: 1
 Random generated ticket number is: 2
 Random generated ticket number is: 3
 Random generated ticket number is: 4
 Random generated ticket number is: 5
 Random generated ticket number is: 6
*/
