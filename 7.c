/*
============================================================================
Name : 7.c
Author : Archis Kulkarni
Description : Write a simple program to print the created thread ids. 
Date: 17-09-2024
============================================================================
*/
#include <pthread.h>
#include <stdio.h>


void printThread(){ 
    printf("Thread has an id of %ld\n", pthread_self()); 
}
int main (){  

    // create 3 threads. we send a number to the function as an argument and print i
    pthread_t mythread1; 
    pthread_t mythread2; 
    pthread_t mythread3;

    //we add the respective threads, and the thread function which the threads will run 
    pthread_create(&mythread1, NULL, (void *) printThread,NULL);     
    pthread_create(&mythread2, NULL, (void *) printThread,NULL);     
    pthread_create(&mythread3, NULL, (void *) printThread,NULL);

    // waiting main function till the threads to finish processing(getting incorrect output without this) 
    pthread_join(mythread1, NULL);
    pthread_join(mythread2, NULL);
    pthread_join(mythread3, NULL);

}
