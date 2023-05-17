#include "../headers/Server.hpp"
#include "../headers/Client.hpp"
#include "../headers/Channel.hpp"

void Server::nick_change(std::string buffer, int fd)
{
	std::string command = "";
	unsigned int i = 0;
	while (i < buffer.size() && (buffer[i] > 32))
		command += buffer[i++]; //first ->command
	if (this->client_ret(fd) && !this->client_nick_check(command))
	{
		std::string b = ":" + this->client_ret(fd)->getPrefixName()+" NICK "+command+"\r\n";
		send(fd, b.c_str(), b.size(), 0);
		this->client_ret(fd)->setNickName(command);
		buffer.clear();
	}
	else
	{
		std::cout << "\033[1;92mThere is some user has the same nickname or user doesn't exist!\033[0m" << std::endl;
		std::string b = ":" + this->client_ret(fd)->getPrefixName()+" NOTICE "+ this->client_ret(fd)->getNickName() +" This nick is already in use: "+command+"\r\n";
		send(fd, b.c_str(), b.size(), 0);
	}
}

void Server::nick_first(std::string command_n, std::string buffer, int fd)
{
	std::vector<std::string> my_vec;
	my_vec.push_back(command_n);
	unsigned int i = 0;
	while (buffer.size() > i)
	{
		std::string command = "";
		std::string args = "";
		while (i < buffer.size() && (buffer[i] > 32))
			command += buffer[i++];
		while (i < buffer.size() && (buffer[i] < 33))
			i++;
		my_vec.push_back(command);
	}
	if (my_vec.size() < 3)
		this->is_nick_first = 1;
	i = 0;
	while (my_vec.size() > i)
	{
		if (my_vec[i] == "NICK")
		{
			this->temp_nick = my_vec[i + 1];
			if(this->client_nick_check(temp_nick) == 1)
			{
				std::cout<<"\033[1;91mNICK IS ALREADY IN THE SERVER!\033[0m\n";
				quit("Nick is already in use!", fd);
				break;
			}
		}
		else if (my_vec[i] == "USER")
		{
			if (!this->client_nick_check(this->temp_nick) && my_vec.size() > i+4)
			{
				Client c(fd,my_vec[i+1],my_vec[i+2],my_vec[i+3],my_vec[i+4],this->temp_nick);
				this->clients_.push_back(c);
				std::cout<<"\033[1;92mNEW USER CREATED AND ADDED TO THE VEC!\033[0m\n";
			}
			else
				std::cout << "Nickname exists!" << std::endl;
		}
		i++;
	}
	my_vec.clear();
	this->is_nick_first = 0;
}
