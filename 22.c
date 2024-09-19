/*
============================================================================
Name : 22.c
Author : Archis Kulkarni
Description : Write a program to wait for data to be written into FIFO within 10 seconds, use select 
system call with FIFO. 
Date: 18-09-2024
============================================================================
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include<sys/select.h>


int main() {

    char buffer[1024];

// make fifo if not exists
    int status = mkfifo("samplefifo", 0666);
    if (status == -1) {
        perror("file exists probably");
    }

// adding non block to stop blocking the process
    int fd=open("samplefifo", O_RDONLY|O_NONBLOCK);
    if (fd == -1) {
        perror("opening failed");
        exit(EXIT_FAILURE);
    }

    //declare read fd set
	fd_set readfs;
	//remove all fds from sets and add fd to it
	FD_ZERO(&readfs);
	FD_SET(fd,&readfs);

	//declare time interval
	struct timeval timeout;
	timeout.tv_sec=10;
	timeout.tv_usec=0;

	//perform select call
	int returnvalue=select(fd+1,&readfs,NULL,NULL,&timeout);


	//print messages based on returned value
	if(returnvalue==0){printf("10 sec Timeout reached! Try again.\n");}
	else if(returnvalue==-1){printf("There was an error! Try again.\n");}
	else{
        // read from the fifo
        ssize_t bytes = read(fd, buffer, sizeof(buffer) - 1);
        if (bytes == -1) {
            perror("reading failed");
            exit(EXIT_FAILURE);
        }

        // terminate and display the read data
        buffer[bytes] = '\0';
        printf("Process read the data: %s\n", buffer);
        printf("%d file descriptors were modified.\n",returnvalue);
    }

    

    return 0;
}

/*
./a.out
file exists probably: File exists
10 sec Timeout reached! Try again.

 ./a.out
file exists probably: File exists
Process read the data: Hello there!
1 file descriptors were modified.
*/
