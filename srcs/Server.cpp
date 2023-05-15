/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasinsensoy <yasinsensoy@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 22:16:32 by yasinsensoy       #+#    #+#             */
/*   Updated: 2023/05/14 01:36:02 by yasinsensoy      ###   ########.fr       */
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
	this->my_port = std::stoi(argv[1]);
	this->my_password = argv[2];
	this->flag = 0;
}

void	Server::loop()
{
	std::string message;
	while (1)
	{
		poll(pollfds.begin().base(), pollfds.size(), 1000);
		for (size_t i = 0 ; i <  pollfds.size() ; i++)
		{
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
	buffer.clear();
	int	addr_len = sizeof(address);
	this->new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t *)&addr_len);
	std::cout << "New socket: " << this->new_socket << std::endl;
	if (this->new_socket < 0)
	{
		std::cerr << "Accept failed" << std::endl;
		close(this->new_socket);

	}
	else
	{
		this->pollfds.push_back((pollfd){this->new_socket, POLLIN, 0});
		this->user_count++;
		std::map<int, std::string>::iterator it;
		it = cap_ls.begin();
		std::string str;
		while (it != cap_ls.end())
		{
			str.append('/' + it->second + "\n");
			++it;
		}
		send(this->new_socket, str.c_str(), str.size(), 0);
	}
}
