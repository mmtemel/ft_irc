/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_v2.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtemel <mtemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 23:25:43 by mtemel            #+#    #+#             */
/*   Updated: 2023/04/29 01:34:26 by mtemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <netinet/in.h>

void error(const char *msg)
{
	perror(msg);
	exit(1);
}

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		fprintf(stderr, "Port No not provided. Program terminated\n");
		exit(1);
	}
	int sockfd, newsockfd, portno, n;
	char buffer[255];

	struct sockaddr_in serv_addr, cli_addr;
	socklen_t clilen;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		error("Error opening socket.");
	}

	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = atoi(argv[1]);

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);

	if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		error("Binding failed");

	listen(sockfd, 5);
	clilen = sizeof(cli_addr);

	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	if(newsockfd < 0)
		error("Error on accept");

	while(1)
	{
		bzero(buffer, 255);
		n = read(newsockfd, buffer, 255);
		if(n < 0)
			error("Error on reading");
		printf("client: %s\n", buffer);
		bzero(buffer, 255);
		fgets(buffer, 255, stdin);

		n = write(newsockfd, buffer, strlen(buffer));
		if(n < 0)
			error("Error on writing");

		int l = strncmp("Bye", buffer, 3);
		if(l == 0)
			break;
	}

	// int num1, num2, answer, choice;
	
	close(newsockfd);
	close(sockfd);
	return (0);
}