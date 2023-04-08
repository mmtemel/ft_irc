/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketServer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtemel <mtemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 23:54:03 by mtemel            #+#    #+#             */
/*   Updated: 2023/04/08 19:22:19 by mtemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <sys/select.h>
#include <unistd.h>
#include <fcntl.h>

#define PORT 9909

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	struct sockaddr_in srv;
	fd_set fr, fw, fe;
	int nRet;

	//initialize the socket
	int nsocket = socket(AF_INET, SOCK_STREAM, 0);
	std::cout << "socket fd: "<< nsocket << std::endl;
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

	//about the blocking vs non-blocking sockets
	nRet = fcntl(nsocket, F_SETFL, fcntl(nsocket, F_GETFL, 0) | O_NONBLOCK);
	std::cout << "fcntl returns: " << nRet << std::endl;
	if(nRet == -1)
		std::cout << "\033[1;31mfcntl failed!\033[0m" << std::endl;
	else
		std::cout << "\033[1;32mfcntl succeeded!\033[0m" << std::endl;

	//setsockopt
	const int opt = 1;
	nRet = setsockopt(nsocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	std::cout << "setsockopt returns: " << nRet << std::endl;
	if(nRet != 0)
		std::cout << "\033[1;31msetsockopt failed!\033[0m" << std::endl;
	else
		std::cout << "\033[1;32msetsockopt succeeded!\033[0m" << std::endl;

	//bind the socket to the local port
	nRet = bind(nsocket, (sockaddr*)&srv, sizeof(sockaddr));
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

	int nMaxFd = nsocket;
	struct timeval tv;
	tv.tv_sec = 1;
	tv.tv_usec = 1;

	while (1)
	{
		FD_ZERO(&fw);
		FD_ZERO(&fr);
		FD_ZERO(&fe);

		FD_SET(nsocket, &fr);
		FD_SET(nsocket, &fe);

		// std::cout << "Before select call:" << fr.fds_bits << std::endl;

		//Keep waiting for new requests and proceed as per the request
		nRet = select(nMaxFd + 1, &fr, &fw, &fe, &tv);
		if(nRet > 0)
		{
			//when someone connects or communicate with a message over a dedicated connection
			std::cout << "\033[1;32mSome client on port!\033[0m" << std::endl;
			if (FD_ISSET(nsocket, &fe))
				std::cout << "\033[1;33mThere is an exception!\033[0m" << std::endl;
			else if (FD_ISSET(nsocket, &fw))
				std::cout << "\033[1;34mReady to write something!\033[0m" << std::endl;
			else if (FD_ISSET(nsocket, &fr))
				std::cout << "\033[1;35mReady to read. Something new came up at the port!\033[0m" << std::endl;
		}
		else if(nRet == 0)
		{
			//no connection or any communication request made or none of the socket descriptors ar ready
			std::cout << "Nothing on port: "<<PORT<<std::endl;
		}
		else
		{
			//it failed and your application should show some useful message
			std::cout << "\033[1;31mFailed...\033[0m"<<std::endl;
		}
		// std::cout << "After select call:" << fr.fds_bits << std::endl;
		sleep(2);
	}

}