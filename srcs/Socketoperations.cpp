#include "../headers/Channel.hpp"
#include "../headers/Client.hpp"
#include "../headers/Server.hpp"

void	Server::socketOperations()
{
	/* Create a socket */
	if ((server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
	{
		std::cerr << "Socket Failed" << std::endl;
		exit(1);
	}
	int opt = 1;
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR , &opt, sizeof(opt)) < 0)
	{
		std::cerr << "Setsockopt couldn't connect..." << std::endl;
		exit(1);
	}
	if (setsockopt(server_fd, IPPROTO_TCP, TCP_NODELAY, &opt, sizeof(opt)) < 0)
	{
		std::cerr << "Setsockopt couldn't connect..." << std::endl;
		exit(1);
	}
	if (fcntl(server_fd, F_SETFL, O_NONBLOCK) < 0)
	{
		std::cerr << "Setsockopt couldn't connect..." << std::endl;
		exit(1);
	}
}

void	Server::socketOperations2(char **argv)
{
	address.sin_family = AF_INET; //IPV4
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(atoi(argv[1]));

	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
	{
		std::cerr << "Error binding to port " << std::endl;
		close(server_fd);
		exit(1);
	}

	if (listen(server_fd, MAX_USR) < 0)
	{
		std::cerr << "listen failed" << std::endl;
		close(server_fd);
		exit(1);
	}
	pollfds.push_back((pollfd){server_fd, POLLIN, 0});
}
