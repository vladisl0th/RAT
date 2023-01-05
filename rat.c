#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUFFER_SIZE 256

int main(int argc, char *argv[])
{
	if (argc < 3) {
		fprintf(stderr, "Usage: %s [IP] [PORT]\n", argv[0]);
		exit(1);
	}

	char *host = argv[1];
	int port = atoi(argv[2]);

	int sockfd;
	struct sockaddr_in serv_addr;

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("Error creating socket");
		exit(1);
	}

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);

	if (inet_pton(AF_INET, host, &serv_addr.sin_addr) <= 0) {
		perror("Error converting address");
		exit(1);
	}

	if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		perror("Error connecting to host");
		exit(1);
	}

	printf("Connected to %s:%d\n", host, port);

	char buffer[BUFFER_SIZE];

	while (1) {
		printf("Enter command: ");
		fgets(buffer, BUFFER_SIZE, stdin);

		if (send(sockfd, buffer, strlen(buffer), 0) < 0) {
			perror("Error sending command");
			break;
		}

		int n = recv(sockfd, buffer, BUFFER_SIZE, 0);
		if (n < 0) {
			perror("Error receiving response");
			break;
		} else if (n == 0) {
			printf("Connection closed by host.\n");
			break;
		}

		printf("Response:\n%.*s\n", n, buffer);
	}

	close(sockfd);

	return 0;
}
