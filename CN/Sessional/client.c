#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_BUFFER_SIZE 1024

void start_client() {
    int client_socket;
    struct sockaddr_in server_address;
    char buffer[MAX_BUFFER_SIZE];

    // Create socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Initialize server address structure
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(12345);

    // Convert IP address from string to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0) {
        perror("Error converting IP address");
        exit(EXIT_FAILURE);
    }

    // Connect to the server
    if (connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
        perror("Error connecting to server");
        exit(EXIT_FAILURE);
    }

    printf("Connected to server\n");

    printf("Enter text to send to server: ");
    fgets(buffer, MAX_BUFFER_SIZE, stdin);

    // Send data to the server
    send(client_socket, buffer, strlen(buffer), 0);

    // Receive and print the encrypted data from the server
    ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
    if (bytes_received < 0) {
        perror("Error receiving data from server");
        exit(EXIT_FAILURE);
    }

    buffer[bytes_received] = '\0';
    printf("Encrypted data received from server: %s\n", buffer);

    close(client_socket);
}

int main() {
    start_client();
    return 0;
}
