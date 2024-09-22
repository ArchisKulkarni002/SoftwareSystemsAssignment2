/*
============================================================================
Name : 33.c
Author : Archis Kulkarni
Description :   Write a program to communicate between two machines using socket.
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
    char buffer[1024] = {0};
    
    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    
    // Forcefully attaching socket to the 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    
    // Configure the address structure
    address.sin_family = AF_INET; // IPv4
    address.sin_addr.s_addr = INADDR_ANY; // Any address
    address.sin_port = htons(8080); // 8080 number
    
    // Bind the socket to the address
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    
    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    
    printf("Server listening on Port %d\n", 8080);
    
    // Accept incoming connections
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    
    // Communicate with the client
    while (1) {
        memset(buffer, 0, 1024);
        int valread = read(new_socket, buffer, 1024);
        if (valread <= 0) {
            printf("Client disconnected.\n");
            break;
        }
        printf("Received: %s", buffer);
        send(new_socket, buffer, valread, 0); // Echo back the message
    }
    
    // Cleanup
    close(new_socket);
    close(server_fd);
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
