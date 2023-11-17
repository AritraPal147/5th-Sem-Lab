// Client.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12349
#define MAX_BUFFER_SIZE 1024

void receive_file(int socket) {
    char buffer[MAX_BUFFER_SIZE];
    size_t bytesRead;

    FILE *file = fopen("received_file.txt", "wb");
    if (!file) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }

    while ((bytesRead = recv(socket, buffer, sizeof(buffer), 0)) > 0) {
        fwrite(buffer, 1, bytesRead, file);
    }

    fclose(file);
}

int main() {
    int clientSocket;
    struct sockaddr_in serverAddr;

    // Create socket
    if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Change to the server's IP address

    // Connect to the server
    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Error connecting to server");
        exit(EXIT_FAILURE);
    }

    printf("Connected to server\n");

    // Request the file from the server
    send(clientSocket, "send.txt", strlen("send.txt"), 0);

    // Receive the file from the server
    receive_file(clientSocket);

    printf("File received successfully\n");

    // Close the socket
    close(clientSocket);

    return 0;
}

