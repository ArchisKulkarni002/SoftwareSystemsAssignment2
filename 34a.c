/*
============================================================================
Name : 34a.c
Author : Archis Kulkarni
Description :    Write a program to create a concurrent server. 
a. use fork 
b. use pthread_create
Date: 21-09-2024
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>


int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // set socket options
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    // configure address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);
    
    // bind
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // listen to the requests
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", 8080);
    
    while (1) {
        // accept new connection
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }

        // fork a new process to handle the client
        if (fork() == 0) {
            // In child process
            close(server_fd);
            char buffer[1024];
            int valread;

            while ((valread = read(new_socket, buffer, 1024)) > 0) {
                printf("Received: %s", buffer);
                send(new_socket, buffer, valread, 0); // Echo back
                memset(buffer, 0, 1024);
            }

            printf("Client disconnected.\n");
            close(new_socket);
            exit(0); 
        }
        close(new_socket); 
    }

    return 0;
}






/*
./a.out
Server listening on Port 8080
Received: GET / HTTP/1.1
Content-Type: text/plain
User-Agent: PostmanRuntime/7.33.0
Accept: *\/*
Postman-Token: 8d72d362-eefd-4a6d-922a-0af0ccfb425d
Host: 127.0.0.1:8080
Accept-Encoding: gzip, deflate, br
Connection: keep-alive
Content-Length: 14

Hello there!
Client disconnected.
*/
