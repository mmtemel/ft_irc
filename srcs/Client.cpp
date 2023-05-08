#include "../headers/Client.hpp"

Client::Client(int fd, std::string username,std::string hostname, std::string servername, std::string realname, std::string nickname)
{
	this->fd = fd;
	this->username = username;
	this->nickname = nickname;
	this->realname = realname;
	this->hostname = hostname;
	this->servername = servername;

	this->setStatus(1);
}

Client::~Client(){}