/*
============================================================================
Name : 20a.c
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
        perror("file exists probably");
    }

    int fd=open("samplefifo", O_RDONLY);
    if (fd == -1) {
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
    printf("Process read the data: %s\n", buffer);

    return 0;
}

/*
./a.out
Process read the data: Hello there!
*/
