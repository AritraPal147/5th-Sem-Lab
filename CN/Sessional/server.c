#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>
#define MAX_BUFFER_SIZE 1024

void handle_client(int client_socket) {
    char buffer[MAX_BUFFER_SIZE];
    ssize_t bytes_received;

    bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
    if (bytes_received < 0) {
        perror("Error receiving data from client");
        exit(EXIT_FAILURE);
    }

    buffer[bytes_received] = '\0';
	printf("Recieved Message: %s", buffer);
    
    for (int i = 0; i < bytes_received; i++) 
        buffer[i] = buffer[i] + 1;

    send(client_socket, buffer, strlen(buffer), 0);

    close(client_socket);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t client_address_len = sizeof(client_address);

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Initialize server address structure
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(12345);

    // Bind the socket
    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
        perror("Error binding socket");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_socket, 5) == -1) {
        perror("Error listening for connections");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port 12345\n");

    while (1) {
        // Accept a connection from the client
        client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_address_len);
        if (client_socket == -1) {
            perror("Error accepting connection");
            continue;
        }

        printf("Connection from %s\n", inet_ntoa(client_address.sin_addr));

        // Handle client communication
        handle_client(client_socket);
    }

    close(server_socket);

    return 0;
}
