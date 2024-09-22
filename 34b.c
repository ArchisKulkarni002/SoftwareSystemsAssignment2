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
#include <pthread.h>


void *handle_client(void *arg) {
    int client_socket = *(int *)arg;
    char buffer[1024];
    int valread;

    while ((valread = read(client_socket, buffer, 1024)) > 0) {
        printf("Received: %s", buffer);
        send(client_socket, buffer, valread, 0); // Echo back
        memset(buffer, 0, 1024);
    }

    printf("Client disconnected.\n");
    close(client_socket);
    return NULL;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    pthread_t tid;

    // create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // set socket options
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    // Configure address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);
    
    // bind
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // listen
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

        // create a new thread to handle the client
        if (pthread_create(&tid, NULL, handle_client, (void *)&new_socket) != 0) {
            perror("pthread_create");
            close(new_socket);
        }
        pthread_detach(tid);
    }

    return 0;
}

/*
./a.out
Server listening on port 8080
Received: GET / HTTP/1.1
Content-Type: text/plain
User-Agent: PostmanRuntime/7.33.0
Accept: *\/*
Postman-Token: 29588beb-2d58-40ae-b13a-0b22039530b2
Host: 127.0.0.1:8080
Accept-Encoding: gzip, deflate, br
Connection: keep-alive
Content-Length: 14

Hello there!
Client disconnected.
Received: GET / HTTP/1.1
Content-Type: text/plain
User-Agent: PostmanRuntime/7.33.0
Accept: *\/*
Postman-Token: a76e8f32-9d3c-4525-91e0-f4298e26c338
Host: 127.0.0.1:8080
Accept-Encoding: gzip, deflate, br
Connection: keep-alive
Content-Length: 14

Hello there!
Client disconnected.
*/
