/*
============================================================================
Name : 16.c
Author : Archis Kulkarni
Description :  Write a program to send and receive data from parent to child vice versa. Use two way 
communication.
Date: 18-09-2024
============================================================================
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int pipefd[2], pipefd1[2];
    pid_t pid;

    char buffer[1024];

    // first we create a pipe
    int status=pipe(pipefd);
    if (status == -1) {
        perror("first pipe failed");
        exit(EXIT_FAILURE);
    }
    status=pipe(pipefd1);
    if (status == -1) {
        perror("second pipe failed");
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
        // close the read end of the pipe1 at fd0
        close(pipefd1[0]);

        // read from the pipe at fd0
        ssize_t bytes = read(pipefd[0], buffer, sizeof(buffer) - 1);
        if (bytes == -1) {
            perror("reading failed");
            exit(EXIT_FAILURE);
        }
        // terminate and display the read data
        buffer[bytes] = '\0';
        printf("Child Process read the data: %s\n", buffer);

        // send data to the pipe1
        ssize_t bytesWritten = write(pipefd1[1], "Hello there from pipe2!", strlen("Hello there from pipe2!"));
        if (bytesWritten == -1) {
            perror("writing failed");
            exit(EXIT_FAILURE);
        }

        printf("Child Process writing the data: Hello there from pipe2!\n");

        // close the read end of the pipe at fd0
        close(pipefd[0]);
        // close the write end of the pipe at fd1
        close(pipefd1[1]);

        exit(EXIT_SUCCESS);
    } else { 
        // close the read end of the pipe at fd0
        close(pipefd[0]);
        // close the wirte end of the pipe1 at fd1
        close(pipefd1[1]);

        // send data to the pipe
        ssize_t bytesWritten = write(pipefd[1], "Hello there from pipe1!", strlen("Hello there from pipe1!"));
        if (bytesWritten == -1) {
            perror("writing failed");
            exit(EXIT_FAILURE);
        }

        printf("Parent Process writing the data: Hello there from pipe1!\n");

        // read from the pipe1 at fd0
        ssize_t bytes = read(pipefd1[0], buffer, sizeof(buffer) - 1);
        if (bytes == -1) {
            perror("reading failed");
            exit(EXIT_FAILURE);
        }
        // terminate and display the read data
        buffer[bytes] = '\0';
        printf("Parent Process read the data: %s\n", buffer);

        // close the write end of the pipe at fd1
        close(pipefd[1]);
        // close the read end of the pipe1 at fd0
        close(pipefd1[0]);
    }

    return 0;
}

/*
./a.out
Parent Process writing the data: Hello there from pipe1!
Child Process read the data: Hello there from pipe1!
Child Process writing the data: Hello there from pipe2!
Parent Process read the data: Hello there from pipe2!
*/
