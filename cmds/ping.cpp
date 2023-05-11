#include "../headers/Server.hpp"
#include "../headers/Client.hpp"
#include "../headers/Channel.hpp"

void Server::ping(std::string buffer, int fd)
{
	std::vector<std::string> my_vec;
	std::string command = "";
	unsigned int i = 0;
	while (buffer.size() > i)
	{
		std::string command = "";
		while (i < buffer.size() && (buffer[i] != ' ' && buffer[i] != '\r' && buffer[i] != '\n'))
			command += buffer[i++]; //first ->command
		while (i < buffer.size() && (buffer[i] == ' ' || buffer[i] == '\r' || buffer[i] == '\n'))
			i++;
		my_vec.push_back(command);
	}
	if (my_vec.size() != 1) // it's not just /ping , have to go privmsg.
		privmsg(buffer, fd);
	else
	{
		std::string b = ":" + this->clients_[this->client_ret(fd)].getNickName() + "!localhost PONG " + my_vec[0] + "\r\n";
		this->write_send(fd, b);
	}
}