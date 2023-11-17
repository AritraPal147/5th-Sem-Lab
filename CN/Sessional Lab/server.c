#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>

void handle_client(int client_socket) {

	char text[1024];
    recv(client_socket, text, sizeof(text), 0);
    printf("Received text from client: %s\n", text);

    int ascii_values[strlen(text)];
    for (int i = 0; i < strlen(text); i++) 
        ascii_values[i] = (int)text[i];
        
    send(client_socket, ascii_values, sizeof(ascii_values), 0);

    close(client_socket);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t client_address_len = sizeof(client_address);

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(12345);
   	server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
        perror("Error binding socket");
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 5) == -1) {
        perror("Error listening for connections");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port 12345\n");

    while (1) {
        client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_address_len);
        if (client_socket == -1) {
            perror("Error accepting connection");
            continue;
        }

        printf("Connection from %s\n", inet_ntoa(client_address.sin_addr));
        handle_client(client_socket);
    }

    close(server_socket);

    return 0;
}
