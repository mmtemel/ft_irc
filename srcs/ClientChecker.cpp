#include "../headers/Channel.hpp"
#include "../headers/Client.hpp"
#include "../headers/Server.hpp"

int Server::client_nick_check(std::string nickname)
{
	std::vector<Client>::iterator it = this->clients_.begin();
	std::vector<Client>::iterator ite = this->clients_.end();
	for (; it != ite; it++)
	{
		if(it->getNickName() == nickname)
			return (1);
	}
	return(0);
}

int Server::client_ret(std::string nickname)
{
	std::vector<Client>::iterator it = this->clients_.begin();
	std::vector<Client>::iterator ite = this->clients_.end();
	for (int i = 0; it != ite; it++, i++)
	{
		if(it->getNickName() == nickname)
			return (i);
	}
	return (-1);
}

int Server::client_ret(int fd)
{
	std::vector<Client>::iterator it = this->clients_.begin();
	std::vector<Client>::iterator ite = this->clients_.end();
	for (int i = 0; it != ite; it++, i++)
	{
		if(it->getFd() == fd)
			return (i);
	}
	return (-1);
}
