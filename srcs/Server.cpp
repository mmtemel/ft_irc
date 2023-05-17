/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtemel <mtemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 22:16:32 by yasinsensoy       #+#    #+#             */
/*   Updated: 2023/05/17 13:51:51 by mtemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Channel.hpp"
#include "../headers/Client.hpp"
#include "../headers/Server.hpp"

Server::Server(int argc, char **argv)
{
	appointment(argc, argv);
	std::cout << "\033[1;94mStarting IRC server on port \033[0m" << std::endl;

	socketOperations();
	socketOperations2(argv);

	cap_ls[0] = "NICK";
	cap_ls[1] = "JOIN";
	cap_ls[2] = "QUIT";
	cap_ls[3] = "CAP";
	cap_ls[4] = "KICK";
	cap_ls[5] = "PING";
	cap_ls[6] = "PASS";
	cap_ls[7] = "BOT";
	cap_ls[8] = "MODE";
	cap_ls[9] = "KILL";
	cap_ls[10] = "USER";

	this->is_nick_first = 0;
}

Server::~Server()
{
	std::vector<Client>::iterator it = clients_.begin();
	while (it != clients_.end())
	{
		delete(&(*it));
		++it;
	}
	clients_.clear();
}

void  Server::appointment(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cerr << "Arg Error." << std::endl;
		exit(1);
	}
	
	this->my_port = std::atoi(argv[1]);
	this->my_password = argv[2];
	
	this->flag = 0;

	memset((char *)&address, 0, sizeof(address));
	address.sin_family = AF_INET; //IPV4
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(this->my_port);
}

void	Server::loop()
{
	std::string message;
	while (1)
	{
		if(0 > poll(pollfds.begin().base(), pollfds.size(), -1))
			std::cout << "poll fail" << std::endl;
		for (size_t i = 0 ; i <  pollfds.size() ; i++)
		{
			if (pollfds[i].revents & POLLHUP)
			{
				quit("Disconnected ()", pollfds[i].fd);
				break;
			}
			if (pollfds[i].revents & POLLIN)
			{
				if (pollfds[i].fd == pollfds[0].fd)
				{
					newClient();
					break ;
				}
				executeCommand(pollfds[i].fd);
			}
		}
	}
}

void	Server::newClient()
{
	int	addr_len = sizeof(address);
	this->new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t *)&addr_len);
	// std::cout << "New socket: " << this->new_socket << std::endl;
	if (this->new_socket < 0)
	{
		std::cerr << "Accept failed" << std::endl;
		close(this->new_socket);
		return;
	}
	else
		this->pollfds.push_back((pollfd){this->new_socket, POLLIN, 0});
}
