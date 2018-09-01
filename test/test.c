#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

void client_test() {
	// Create the socket
	int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd < 0) {
		printf("Fail to crete the socket!");
	}
	// Set the server address
	struct sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(struct sockaddr_in));
	server_addr.sin_family = AF_INET;
	if (inet_pton(AF_INET, "127.0.0.1", &(server_addr.sin_addr)) < 0) {
		printf("Fail to execute inet_pton\n");
	}
	uint16_t host_port = 3000;
	uint16_t network_port = htons(host_port);
	server_addr.sin_port = network_port;
	if (connect(socket_fd, (struct sockaddr *) &server_addr, sizeof(struct sockaddr_in)) < 0) {
		printf("Fail to connect\n");
	}
	
	char* buff = "set d1irection right ttt";
	if (write(socket_fd, buff, strlen(buff)) < 0) {
		printf("Fail to write\n");
	}
	sleep(10);
	buff = "Set apple red";
	if (write(socket_fd, buff, strlen(buff)) < 0) {
		printf("Fail to write\n");
	}
}

int main(int argc, char* argv[]) {
	client_test();
}