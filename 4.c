/*
============================================================================
Name : 4.c
Author : Archis Kulkarni
Description : Write a program to measure how much time is taken to execute 100 getppid ( ) 
system call. Use time stamp counter. 
Date: 17-09-2024
============================================================================
*/
#include<time.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>

unsigned long long getTime(){
	unsigned long long dst;
     __asm__ __volatile__ ("rdtsc":"=A" (dst));
     return dst; 
}

int main(){
	time_t time1=getTime();
    for (int i = 0; i < 100; i++)
    {
        getppid();
    }
    

	time_t time2=getTime();

	double cpuspeed = 3.0e6;
	long double timeval = (time2-time1)/cpuspeed;

	printf("cpu cycles taken by pid: %ld\n", (time2-time1));
	printf("miliseconds taken by pid: %Lf\n", timeval);
}

/* ./a.out
cpu cycles taken by pid: 34481
miliseconds taken by pid: 0.011494 */