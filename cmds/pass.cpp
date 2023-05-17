#include "../headers/Server.hpp"
#include "../headers/Client.hpp"
#include "../headers/Channel.hpp"

void Server::pass(std::string buffer, int fd)
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
	if (my_vec.size()>0)
	{
		this->pass_fd[fd] = my_vec[0];
	}
	if (my_vec.empty() || my_vec[0] != this->my_password)
	{
		std::cerr << "\033[1;91mError: Password Problems...!\033[0m" << std::endl;
		// quit("WRONG PASS", fd);
	}
	else
		std::cout << "\033[1;92mRight: Pass Command\033[0m" << std::endl;
	return;
}
