#include "../headers/Channel.hpp"
#include "../headers/Client.hpp"
#include "../headers/Server.hpp"

void Server::write_send(int fd, std::string message)
{
	int send_ret = send(fd, message.c_str(), message.size(), 0);
		std::cout<<"\033[1;93mMessage to send:*\033[0m"<<message<<"*"<<std::endl;
	if(send_ret < 0)
		std::cerr<<"\033[1;91mFailed to send message!\033[0m"<<std::endl;
}