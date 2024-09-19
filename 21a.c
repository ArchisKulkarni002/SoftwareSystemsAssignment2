/*
============================================================================
Name : 21a.c
Author : Archis Kulkarni
Description : Write two programs so that both can communicate by FIFO -Use two way communications.
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
        perror("file exists probably");
    }
    status = mkfifo("samplefifo1", 0666);
    if (status == -1) {
        perror("file exists probably");
    }

    int fd=open("samplefifo", O_RDONLY);
    int fd1=open("samplefifo1", O_WRONLY);
    if (fd == -1 || fd1 == -1) {
        perror("opening failed");
        exit(EXIT_FAILURE);
    }

    // read from the fifo
    ssize_t bytes = read(fd, buffer, sizeof(buffer) - 1);
    if (bytes == -1) {
        perror("reading failed");
        exit(EXIT_FAILURE);
    }

    // terminate and display the read data
    buffer[bytes] = '\0';
    printf("Process read the data from fifo1: %s\n", buffer);

    // send data to the pipe
    ssize_t bytesWritten = write(fd1, "Hello there from process1!", strlen("Hello there from process1!"));
    if (bytesWritten == -1) {
        perror("writing failed");
        exit(EXIT_FAILURE);
    }

    printf("Process writing the data: Hello there process1!\n");

    return 0;
}

/*
./a.out
file exists probably: File exists
file exists probably: File exists
Process read the data from fifo1: Hello there from process2!
Process writing the data: Hello there process1!
*/
