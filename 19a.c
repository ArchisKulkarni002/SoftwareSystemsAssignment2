/*
============================================================================
Name : 19.c
Author : Archis Kulkarni
Description :  Create a FIFO file by 
a. mknod command 
b. mkfifo command 
c. use strace command to find out, which command (mknod or mkfifo) is better. 
c. mknod system call 
d. mkfifo library function  
Date: 22-09-2024
============================================================================
*/
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(){
	int status = mknod("somefile",S_IFIFO|S_IRWXU, 0);
	if(status==-1){
		perror("fifo creation failed");
	}
	printf("fifo created.");
}


/*
./a.out
fifo created.
*/
