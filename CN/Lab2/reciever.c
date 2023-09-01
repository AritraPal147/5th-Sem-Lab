#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

// contrary

int main(int argv, char *  argc[]) {
	char *ip = argc[1];
	int port = atoi(argc[2]);
	int server_sock, client_sock;
	struct sockaddr_in server_addr, client_addr;
	socklen_t addr_size;
	char buffer[1024];
	int n;
	
	server_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (server_sock < 0) {
		perror("[-]Socket Error");
		exit(1);
	}
	printf("[+]TCP server socket created.\n");

	memset(&server_addr, '\0', sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = port;
	server_addr.sin_addr.s_addr = inet_addr(ip);

	n = bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
	if (n<0) {
		perror("[-]Bind Error");
		exit(1);
	}
	printf("[+]Bind to the port number: %d\n", port);

	listen(server_sock, 5);
	printf("Listening...\n");

	addr_size = sizeof(client_addr);
	client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);
	printf("[+]Client connected.\n");
		
	char exit[1024] = "exit";
	do {
		bzero(buffer, 1024);
		recv(client_sock, buffer, sizeof(buffer), 0);
		printf("Recieved Message: %s\n", buffer);
	} while (strcmp(exit, buffer) != 0);
	
	bzero(buffer, 1024);
	close(client_sock);
	printf("[+]Client disconnected.\n\n");

	return 0;
}
