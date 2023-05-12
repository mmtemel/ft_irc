#include "../headers/Server.hpp"
#include "../headers/Client.hpp"
#include "../headers/Channel.hpp"

void Server::pass(std::string buffer, int fd)
{
	// There is no need to send message to server from hexchat.
	(void)fd;
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
	if (my_vec.empty())
	{
		std::cerr << "\033[1;95mError: Missing password!\033[0m" << std::endl;
		return;
	}
	if (my_vec[0] != this->my_password)
	{
		std::cerr << "\033[1;95mError: Wrong Password!\033[0m" << std::endl;
		return;
	}
	else
	{
		std::cout << "\033[1;92mRight: Pass Command\033[0m" << std::endl;
		return;
	}
}
