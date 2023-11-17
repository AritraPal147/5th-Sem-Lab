#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

void start_client() {
    int client_socket;
    struct sockaddr_in server_address;

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(12345);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
        perror("Error connecting to server");
        exit(EXIT_FAILURE);
    }

    printf("Connected to server\n");

	char text[1024];
    printf("Enter a text: ");
    scanf("%s", text);
    send(client_socket, text, sizeof(text), 0);

    int ascii_values[strlen(text)];
    recv(client_socket, ascii_values, sizeof(ascii_values), 0);

    printf("Recieved ASCII values: ");
    for (int i = 0; i < strlen(text); i++) {
        printf("%d", ascii_values[i]);
    }
    
    printf("\nDecoded ASCII values: ");
    for (int i = 0; i < strlen(text); i++) {
        printf("%c", (char)ascii_values[i]);
    }
    printf("\n");

    close(client_socket);
}

int main() {
    start_client();
    return 0;
}
