/*
============================================================================
Name : 14.c
Author : Archis Kulkarni
Description : Write a simple program to create a pipe, write to the pipe, read from pipe and display on 
the monitor.
Date: 18-09-2024
============================================================================
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int pipefd[2];
    pid_t pid;

    char buffer[1024];

    // first we create a pipe
    int status=pipe(pipefd);
    if (status == -1) {
        perror("pipe failed");
        exit(EXIT_FAILURE);
    }

    // create a child process
    pid = fork();
    if (pid == -1) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // close the write end of the pipe at fd1
        close(pipefd[1]);

        // read from the pipe at fd0
        ssize_t bytes = read(pipefd[0], buffer, sizeof(buffer) - 1);
        if (bytes == -1) {
            perror("reading failed");
            exit(EXIT_FAILURE);
        }
        // terminate and display the read data
        buffer[bytes] = '\0';
        printf("Process read the data: %s\n", buffer);

        // close the read end of the pipe at fd0
        close(pipefd[0]);

        exit(EXIT_SUCCESS);
    } else { 
        // close the read end of the pipe at fd0
        close(pipefd[0]);
        // send data to the pipe
        ssize_t bytesWritten = write(pipefd[1], "Hello there!", strlen("Hello there!"));
        if (bytesWritten == -1) {
            perror("writing failed");
            exit(EXIT_FAILURE);
        }

        printf("Process writing the data: Hello there!\n");

        // close the write end of the pipe at fd1
        close(pipefd[1]);
    }

    return 0;
}
