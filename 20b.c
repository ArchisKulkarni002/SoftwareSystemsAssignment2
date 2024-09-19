/*
============================================================================
Name : 20b.c
Author : Archis Kulkarni
Description : Write two programs so that both can communicate by FIFO -Use one way communication. 
Date: 18-09-2024
============================================================================
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
    char buffer[1024];

    int status = mkfifo("samplefifo", 0666);
    if (status == -1) {
        perror("file creation failed");
    }

    int fd=open("samplefifo", O_WRONLY);
    if (fd == -1) {
        perror("opening failed");
        exit(EXIT_FAILURE);
    }

    // send data to the pipe
    ssize_t bytesWritten = write(fd, "Hello there!", strlen("Hello there!"));
    if (bytesWritten == -1) {
        perror("writing failed");
        exit(EXIT_FAILURE);
    }

    printf("Process writing the data: Hello there!\n");

    return 0;
}

/*
./b.out
file creation failed: File exists
Process writing the data: Hello there!
*/
