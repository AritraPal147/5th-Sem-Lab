#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
	char *ip = argv[1];
	int port = atoi(argv[2]);
	int sock;
	struct sockaddr_in addr;
	socklen_t addr_size;
	char buffer[1024];
	int n;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0){
		perror("[-]Socket error");
		exit(1);
	}
	printf("[+]TCP server socket created.\n");
	memset(&addr, '\0', sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = port;
	addr.sin_addr.s_addr = inet_addr(ip);
	connect(sock, (struct sockaddr*)&addr, sizeof(addr));
	printf("Connected to the server.\n");

	//bzero(buffer, 1024);
	//strcpy(buffer, "HELLO, THIS IS CLIENT.");
	//printf("Enter a number: ");
	//scanf("%s", buffer); 
	//send(sock, buffer, strlen(buffer), 0);
	char exit[1024] = "exit";
	do {
		bzero(buffer, 1024);
		//strcpy(buffer, "HELLO, THIS IS CLIENT.");
		printf("Enter Message to be sent: ");
		scanf("%s", buffer); 
		send(sock, buffer, strlen(buffer), 0);
	} while (strcmp(exit, buffer) != 0);

	//bzero(buffer, 1024);
	//recv(sock, buffer, sizeof(buffer), 0);
	//printf("Sum: %s\n", buffer);
	//sendData(sock);
	close(sock);
	printf("Disconnected from the server.\n");
	return 0;
}
