#include "../headers/Server.hpp"
#include "../headers/Client.hpp"
#include "../headers/Channel.hpp"

void Server::privmsg(std::string buffer, int fd)
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
	i = 0;
	while(i < my_vec.size())
	{
		std::cout << my_vec[i++] << std::endl;
	}

	size_t found = my_vec[1].find("PING");
	if (found == std::string::npos)
	{
		//my_vec[1] = my_vec[1].substr(1, my_vec[1].size()-1);
		std::cerr << "There is no Ping command, message:*\033[1;96m" << my_vec[1] << "\033[0m*" << std::endl;
		// std::string b = ":" + this->client_ret(fd)->getNickName() + "!localhost MSG " + my_vec[1] + "\r\n";
		std::string b = ":" + my_vec[0] + "!localhost " + my_vec[1] + "\r\n";
	}
	else
	{
		std::string b = ":" + this->clients_[this->client_ret(fd)].getNickName() + "!localhost PONG " + my_vec[2] + "\r\n";
		this->write_send(fd, b);
	}
}
