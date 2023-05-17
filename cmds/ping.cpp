#include "../headers/Server.hpp"
#include "../headers/Client.hpp"
#include "../headers/Channel.hpp"

void Server::ping(std::string buffer, int fd)
{
	std::vector<std::string> my_vec;
	unsigned int i = 0;
	while (buffer.size() > i)
	{
		std::string command = "";
		while (i < buffer.size() && (buffer[i] != ' ' && buffer[i] != '\r' && buffer[i] != '\n'))
			command += buffer[i++];
		while (i < buffer.size() && (buffer[i] == ' ' || buffer[i] == '\r' || buffer[i] == '\n'))
			i++;
		my_vec.push_back(command);
	}
	if (my_vec.size() > 0)
	{
		std::string b = ":" + this->client_ret(fd)->getPrefixName() + " PONG " + my_vec[0] + "\r\n";
		send(fd, b.c_str(), b.size(), 0);
	}
}
