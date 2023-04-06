/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketServer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtemel <mtemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 23:54:03 by mtemel            #+#    #+#             */
/*   Updated: 2023/04/07 02:31:12 by mtemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>

#define PORT 9909

int main(int argc, char **argv)
{
	struct sockaddr_in srv;

	//initialize the socket
	int nsocket = socket(AF_INET, SOCK_STREAM, 0);
	std::cout << "socket: "<< nsocket << std::endl;
	if(nsocket < 0)
		std::cout << "\033[1;31mSocket initialization failed!\033[0m" << std::endl;
	else
		std::cout << "\033[1;32mSocket initialized successfully!\033[0m" << std::endl;

	//initialize the environment for sockaddr structure
	srv.sin_family = AF_INET;
	srv.sin_port = htons(PORT);
	// srv.sin_addr.s_addr = INADDR_ANY;
	srv.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(&(srv.sin_zero), 0, 8);

	//bind the socket to the local port
	int nRet = bind(nsocket, (sockaddr*)&srv, sizeof(sockaddr));
	std::cout << "bind returns: "<< nRet << std::endl;
	if(nRet < 0)
		std::cout << "\033[1;31mBinding failed!\033[0m" << std::endl;
	else
		std::cout << "\033[1;32mBinded successfully!\033[0m" << std::endl;

	//listen the request from client (queue for requests)
	nRet = listen(nsocket, 5);
	std::cout << "listen returns: "<< nRet << std::endl;
	if(nRet < 0)
		std::cout << "\033[1;31mStrating to listen local port failed!\033[0m" << std::endl;
	else
		std::cout << "\033[1;32mStarted listening local port successfully!\033[0m" << std::endl;
}