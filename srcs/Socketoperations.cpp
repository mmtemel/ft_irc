#include "../headers/Channel.hpp"
#include "../headers/Client.hpp"
#include "../headers/Server.hpp"

void	Server::socketOperations()
{
	int opt = 1;
	/* Create a socket */
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		std::cerr << "Socket Failed" << std::endl;
		exit(1);
	}
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
		std::cerr << "fcntl couldn't connect..." << std::endl;
		exit(1);
	}
}

void	Server::socketOperations2(char **argv)
{
	(void)argv;

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
