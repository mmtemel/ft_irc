/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_v2.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtemel <mtemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 01:04:41 by mtemel            #+#    #+#             */
/*   Updated: 2023/04/29 01:27:36 by mtemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <netinet/in.h>
#include <netdb.h>

void error(const char *msg)
{
	perror(msg);
	exit(0);
}

int main(int argc, char *argv[])
{
	int sockfd, portno, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	
	char buffer[256];
	if (argc < 3)
	{
		fprintf(stderr, "usage %s hostname pot\n", argv[0]);
		exit(1);
	}
	portno = atoi(argv[2]);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		error("Error opening socket.");
	}

	server = gethostbyname(argv[1]);
	if(server == NULL)
		fprintf(stderr, "Error, no such host");

	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(portno);
	if(connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		error("Conneciton failed");
	
	while(1)
	{
		bzero(buffer, 255);
		fgets(buffer, 255, stdin);
		n = write(sockfd, buffer, strlen(buffer));
		if(n < 0)
			error("Error on writing");

		bzero(buffer, 255);
		n = read(sockfd, buffer, 255);
		if(n < 0)
			error("Error on reading");
		printf("Server: %s", buffer);

		int l = strncmp("Bye", buffer, 3);
		if(l == 0)
			break;
	}

	close(sockfd);
	return (0);
}