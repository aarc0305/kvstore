#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include "network.h"

#define BACKLOG 10
/* 
	Create the TCP socket using the address and the port.
	After that, return the file descriptor of the socket.
*/
int initTCPServer(char* address, int port) {

	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if ( fd < 0) {
		printf("There are something wrong when creating socket\n");
	}
	struct sockaddr_in saddr;
	memset(&saddr, 0, sizeof(struct sockaddr_in));
	saddr.sin_family = AF_INET;
	if (inet_pton(AF_INET, "127.0.0.1", &(saddr.sin_addr)) < 0) {
		printf("inet_pton failed!\n");
	}
	saddr.sin_port = htons(port);
	printf("saddr.sin_port: %d\n", saddr.sin_port);
	if (bind(fd, (struct sockaddr*) &saddr, sizeof(struct sockaddr_in)) == -1) {
		printf("Fail to bind the address!\n");
	}
	if (listen(fd, BACKLOG) < 0) {
		printf("Fail to listen.\n");
	}
	return fd;
}

void acceptTCPHandler(int fd) {
	wchar_t buff[1024] = {0};
    int cfd = accept(fd, NULL, NULL);
    printf("There is one client: %d\n", cfd);    
    while(recvfrom(cfd, buff, 1024, 0, NULL, NULL) > 0) {
      printf("%s\n", buff);
    }
    return;
}