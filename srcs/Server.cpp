/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtemel <mtemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 22:16:32 by yasinsensoy       #+#    #+#             */
/*   Updated: 2023/05/02 16:11:57 by mtemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Channel.hpp"
#include "../headers/Client.hpp"
#include "../headers/Server.hpp"

Server::Server(int argc, char **argv)
{
	this->appointment(argc, argv);
	std::cout << "Starting IRC server on port " << std::endl;

	this->socketOperations();
	this->socketOperations2(argv);

	this->cap_ls[0] = "ADD";
	this->cap_ls[1] = "NICK";
	this->cap_ls[2] = "JOIN";
	this->cap_ls[3] = "QUIT";
	this->cap_ls[4] = "CAP";
}

Server::~Server(){}

void  Server::appointment(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cerr << "Usage: ./ircserv <port number> <password>" << std::endl;
		exit(1);
	}
	this->my_port = std::atoi(argv[1]);
	this->my_password = argv[2];
}

void	Server::socketOperations()
{
	/* Create a socket */
	if ((this->server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
	{
		std::cerr << "Socket Failed" << std::endl;
		exit(1);
	}
	int opt = 1;
	if (setsockopt(this->server_fd, SOL_SOCKET, SO_REUSEADDR , &opt, sizeof(opt)) < 0)
	{
		std::cerr << "Setsockopt couldn't connect..." << std::endl;
		exit(1);
	}
}

void	Server::socketOperations2(char **argv)
{
	this->address.sin_family = AF_INET; //IPV4
	this->address.sin_addr.s_addr = INADDR_ANY;
	this->address.sin_port = htons(atoi(argv[1]));

	if (bind(this->server_fd, (struct sockaddr *)&this->address, sizeof(this->address)) < 0)
	{
		std::cerr << "Error binding to port " << std::endl;
		close(this->server_fd);
		exit(1);
	}

	if (listen(this->server_fd, MAX_USR) < 0)
	{
		std::cerr << "listen failed" << std::endl;
		close(this->server_fd);
		exit(1);
	}
	this->pollfds.push_back((pollfd){this->server_fd, POLLIN, 0});
}

void	Server::loop()
{
	std::string message;
	while (1)
	{
		poll(this->pollfds.begin().base(), this->pollfds.size(), -1);
		for (size_t i = 0 ; i < this->pollfds.size() ; i++)
		{
			if (this->pollfds[i].revents & POLLIN)
			{
				if (this->pollfds[i].fd == pollfds[0].fd)
				{
					this->newClient();
					break ;
				}
				this->executeCommand(this->pollfds[i].fd);
			}
		}
	}
}

void	Server::newClient()
{
	this->buffer.clear();
	int	addr_len = sizeof(address);
	this->new_socket = accept(this->server_fd, (struct sockaddr*)&this->address, (socklen_t *)&addr_len);
	if (this->new_socket < 0)
	{
		std::cerr << "Accept failed" << std::endl;
		close(this->server_fd);
		exit(1);
	}
	this->pollfds.push_back((pollfd){this->new_socket, POLLIN, 0});
	std::map<int, std::string>::iterator it;
	it = this->cap_ls.begin();
	while (it != this->cap_ls.end())
	{
		// std::cout << "The nick: " << this->my_nick << std::endl;
		std::string str = "/";
		str += it->second += "\r\n";
		send(this->new_socket, str.c_str(), str.size(), 0);
		++it;
	}
}

void	Server::executeCommand(int fd)
{
	while (this->buffer.find("\r\n"))
	{
		this->buffer.clear();
		char buff[BUFFER_SIZE];
		memset(buff, 0, BUFFER_SIZE);
		int bytes_received = recv(fd, buff, BUFFER_SIZE, 0);
		if (bytes_received < 0)
		{
			std::cerr << "Receive failed" << std::endl;
			return ;
		}
		this->buffer = std::string(buff);
		while (this->buffer.size() > 0)
		{
			std::string command = "";
			std::string args = "";
			unsigned int i = 0;
			while (i < this->buffer.size() && (this->buffer[i] != ' ' && this->buffer[i] != '\r' && this->buffer[i] != '\n'))
				command += this->buffer[i++]; //first ->command
			while (i < this->buffer.size() && (this->buffer[i] == ' ' || this->buffer[i] == '\r' || this->buffer[i] == '\n'))
				i++;
			while (i < this->buffer.size())
				args += this->buffer[i++]; //the line ->arg
			// while (i < this->buffer.size() && (this->buffer[i] != ' ' && this->buffer[i] != '\r' && this->buffer[i] != '\n'))
			// 	args += this->buffer[i++]; //second ->arg
			// while (i < this->buffer.size() && (this->buffer[i] == ' ' || this->buffer[i] == '\r' || this->buffer[i] == '\n'))
			// 	i++;
			this->parser(command, args);
			this->buffer.erase(0, i);
		}
	}
}

void	Server::parser(std::string command, std::string args)
{
	std::cout << "Command: " << "*" << command << "*" << std::endl;
		std::cout << "Args: " <<"*" << args << "*" << std::endl;
	if (command == "NICK")
	{
		this->nick(*this, args);
	}
	if (!strncmp(this->cap_ls[0].c_str(), command.c_str(), 3))
		this->add(*this, args);
	if (!strncmp(this->cap_ls[2].c_str(), command.c_str(), 4))
		this->join(*this, args);
	if (!strncmp(this->cap_ls[3].c_str(), command.c_str(), 4))
		this->quit(*this, args);
	if (command == "CAP")
		this->cap(*this, args);
}


void Server::cap(Server &server, std::string line)
{
	(void)server;
	std::vector<std::string> commands;

	unsigned int i = 0;
	while (i < line.size())
	{
		std::string command = "";
		std::string args = "";
		while (i < line.size() && (line[i] != ' ' && line[i] != '\r' && line[i] != '\n'))
			command += line[i++]; //first ->command
		while (i < line.size() && (line[i] == ' ' || line[i] == '\r' || line[i] == '\n'))
			i++;
		commands.push_back(command);
		std::cout << "\033[1;95mAfter while cap!\033[0m" << std::endl;
	}
	i = -1;
	while (++i < commands.size())
	{
		std::cout << "\033[1;95m" << commands[i] << "\033[0m" << std::endl;
		if(commands[i] == "USER" || commands[i] == "NICK")
			this->parser(commands[i], commands[i+1]);
	}
	
}

void Server::add(Server &server, std::string line)
{
	(void)server;
	std::vector<std::string> tokens;
	std::istringstream iss(line);
	std::string token;

	while (std::getline(iss, token, ' ')) //Space parsing
		tokens.push_back(token);
	if (tokens.size() <= 1)
		return;
	Client new_client;
	for (unsigned int i = 0; i < tokens.size(); i++)
	{
		new_client.client_name = tokens[i];
		this->clients_.push_back(new_client);
	}
}

void Server::nick(Server &server, std::string str)
{
	(void)server;
	unsigned int i = 0;
	std::string command = "";
	while (i < str.size() && (str[i] != ' ' && str[i] != '\r' && str[i] != '\n'))
		command +=str[i++]; //first ->command
	str.clear();
	this->my_nick = command;
	/* :yasin!localhost NICK :ali */
	std::string b = ":" + this->old_nick + "!localhost NICK " + command + "\r\n";
	// std::string b = ":" + str +"!localhost NICK " + "mtemel" + "\r\n";
	// std::string b = "NICK " + str + "\r\n";
	std::cout << "string to send: " << b << "to: " << this->new_socket << ", old nick: " << this->old_nick << std::endl;
	send(this->new_socket, b.c_str(), b.size(), 0);
	this->old_nick.clear();
	this->old_nick = command;
	command.clear();
}

void Server::join(Server &server, std::string line)
{
	std::cout << "join line : *" << line << "*" << std::endl;
	(void)server;
	std::vector<std::string> commands;
	unsigned int i = 0;
	while (i < line.size())
	{
		std::string command = "";
		while (i < line.size() && (line[i] != ' ' && line[i] != '\r' && line[i] != '\n'))
			command += line[i++]; //first ->command
		while (i < line.size() && (line[i] == ' ' || line[i] == '\r' || line[i] == '\n'))
			i++;
		commands.push_back(command);
		// std::cout << "\033[1;95mAfter while cap!\033[0m" << std::endl;
	}
	i = -1;
	std::cout << "command size: " << commands.size() << std::endl;
	while (++i < commands.size())
	{
		std::cout << "\033[1;95m" << commands[i] << "\033[0m" << std::endl;
		if(commands[i][0] != '#' &&	commands[i][0] != '&')
		{
			std::cout << "\033[1;91m" << "Channel name error: " << commands[i] <<"! Must start with '#' or '&'. Try #"<< commands[i] << "\033[0m" << std::endl;
			continue;
		}
		commands[i] = commands[i].substr(1, commands[i].size() - 1);
		std::string a = ":"+ this->my_nick +"!localhost JOIN " + commands[i] + "\r\n";
		std::cout << "string to send: " << a << "to: " << this->new_socket << ", old nick: " << this->old_nick << std::endl;
		send(this->new_socket, a.c_str(), a.size(), 0);
	}
	commands.clear();
}

void Server::quit(Server &server, std::string str)
{
	(void)server;
	(void)str;
	std::cout << "\033[1;91mLeaving...\033[0m" << std::endl;
		exit(1);
}
