#include "../headers/Server.hpp"
#include "../headers/Client.hpp"
#include "../headers/Channel.hpp"

void Server::ping(Server &server, std::string buffer, int fd)
{
	std::vector<std::string> my_vec;
	std::string command = "";
	int i = 0;
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
		privmsg(server, buffer, fd);
	else
	{
		std::string b = ":" + this->temp_nick + "!localhost PONG " + my_vec[1] + "\r\n";
		send(fd, b.c_str(), b.size(), 0);
	}
}