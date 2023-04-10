/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketClient.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtemel <mtemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 18:42:31 by mtemel            #+#    #+#             */
/*   Updated: 2023/04/10 17:04:52 by mtemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <iomanip>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <sys/select.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstdio>

#define PORT 9909

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	struct sockaddr_in srv;
	// fd_set fr, fw, fe;
	int nRet;

	//initialize the socket
	int nClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	std::cout << "socket fd: "<< nClientSocket << std::endl;
	if(nClientSocket < 0)
		std::cout << "\033[1;31mSocket initialization failed!\033[0m" << std::endl;
	else
		std::cout << "\033[1;32mSocket initialized successfully!\033[0m" << std::endl;

	//initialize the environment for sockaddr structure
	srv.sin_family = AF_INET;
	srv.sin_port = htons(PORT);
	// srv.sin_addr.s_addr = INADDR_ANY;
	srv.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(&(srv.sin_zero), 0, 8);

	nRet = connect(nClientSocket, (struct sockaddr*) &srv, sizeof(srv));
	std::cout << "connect returns: " << nRet << std::endl;
	if(nRet == -1)
		std::cout << "\033[1;31mconnection failed!\033[0m" << std::endl;
	else
	{
		std::cout << "\033[1;32mconnection succeeded!\033[0m" << std::endl;
		char buff[255] = {0,};
		std::string line;
		recv(nClientSocket, buff, 255, 0);
		std::cout << "Press any key to see the received message from server:";
		std::getchar(); //getchar();
		std::cout << "\033[1;36m" << buff << "\033[0m" << std::endl;
		
		//latest part
		std::cout << "\033[1;33mNow send your message:" <<std::endl;
		while(1)
		{
			std::getline(std::cin, line); //fgets(buff, 255, stdin);
			send(nClientSocket, (const char*)(line.c_str()), 255, 0);
			std::cout << "Press any key to see the received message from server:";
			getchar();
			std::cout << "\033[1;36m" << buff << "\033[0m" << std::endl;
			std::cout << "\033[1;34mNow send your next message: \033[0m" << std::endl;
		}
	}


	// //about the blocking vs non-blocking sockets
	// nRet = fcntl(nClientSocket, F_SETFL, fcntl(nClientSocket, F_GETFL, 0) | O_NONBLOCK);
	// std::cout << "fcntl returns: " << nRet << std::endl;
	// if(nRet == -1)
	// 	std::cout << "\033[1;31mfcntl failed!\033[0m" << std::endl;
	// else
	// 	std::cout << "\033[1;32mfcntl succeeded!\033[0m" << std::endl;

	// //setsockopt
	// const int opt = 1;
	// nRet = setsockopt(nClientSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	// std::cout << "setsockopt returns: " << nRet << std::endl;
	// if(nRet != 0)
	// 	std::cout << "\033[1;31msetsockopt failed!\033[0m" << std::endl;
	// else
	// 	std::cout << "\033[1;32msetsockopt succeeded!\033[0m" << std::endl;

	// //bind the socket to the local port
	// nRet = bind(nClientSocket, (sockaddr*)&srv, sizeof(sockaddr));
	// std::cout << "bind returns: "<< nRet << std::endl;
	// if(nRet < 0)
	// 	std::cout << "\033[1;31mBinding failed!\033[0m" << std::endl;
	// else
	// 	std::cout << "\033[1;32mBinded successfully!\033[0m" << std::endl;

	// //listen the request from client (queue for requests)
	// nRet = listen(nClientSocket, 5);
	// std::cout << "listen returns: "<< nRet << std::endl;
	// if(nRet < 0)
	// 	std::cout << "\033[1;31mStrating to listen local port failed!\033[0m" << std::endl;
	// else
	// 	std::cout << "\033[1;32mStarted listening local port successfully!\033[0m" << std::endl;

	// int nMaxFd = nClientSocket;
	// struct timeval tv;
	// tv.tv_sec = 1;
	// tv.tv_usec = 1;

	// while (1)
	// {
	// 	FD_ZERO(&fw);
	// 	FD_ZERO(&fr);
	// 	FD_ZERO(&fe);

	// 	FD_SET(nClientSocket, &fr);
	// 	FD_SET(nClientSocket, &fe);

	// 	std::cout << "Before select call:" << fr.fds_bits << std::endl;

	// 	//Keep waiting for new requests and proceed as per the request
	// 	nRet = select(nMaxFd + 1, &fr, &fw, &fe, &tv);
	// 	if(nRet > 0)
	// 	{
	// 		//when someone connects or communicate with a message over a dedicated connection
	// 	}
	// 	else if(nRet == 0)
	// 	{
	// 		//no connection or any communication request made or none of the socket descriptors ar ready
	// 		std::cout << "Nothing on port: "<<PORT<<std::endl;
	// 	}
	// 	else
	// 	{
	// 		//it failed and your application should show some useful message
	// 		std::cout << "\033[1;31mFailed...\033[0m"<<std::endl;
	// 	}
	// 	std::cout << "After select call:" << fr.fds_bits << std::endl;
	// 	sleep(2);
	// }
}