/*
============================================================================
Name : 21b.c
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

    int fd=open("samplefifo", O_WRONLY);
    int fd1=open("samplefifo1", O_RDONLY);
    if (fd == -1 || fd1 == -1) {
        perror("opening failed");
        exit(EXIT_FAILURE);
    }


    // send data to the pipe
    ssize_t bytesWritten = write(fd, "Hello there from process2!", strlen("Hello there from process2!"));
    if (bytesWritten == -1) {
        perror("writing failed");
        exit(EXIT_FAILURE);
    }

    printf("Process writing the data: Hello there process2!\n");

    // read from the fifo
    ssize_t bytes = read(fd1, buffer, sizeof(buffer) - 1);
    if (bytes == -1) {
        perror("reading failed");
        exit(EXIT_FAILURE);
    }

    // terminate and display the read data
    buffer[bytes] = '\0';
    printf("Process read the data from fifo2: %s\n", buffer);

    return 0;
}

/*
./b.out
file exists probably: File exists
file exists probably: File exists
Process writing the data: Hello there process2!
Process read the data from fifo2: Hello there from process1!
*/
