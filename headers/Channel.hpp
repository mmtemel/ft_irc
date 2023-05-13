#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include "../headers/Server.hpp"
#include "../headers/Client.hpp"

class Client;

class Server;

class Channel
{
	private:
		int clientCount;
		std::string channelName;
		int channelAdminFd;
		//std::string	k;
		//int l;
		//bool n;
	public:
		Channel(std::string channelName);
		~Channel();

		std::vector<int> _clientsFd;

		int getchannelAdminFd();
		std::string getchannelName();

		void setchannelAdminFd(int adminFd) {this->channelAdminFd = adminFd;}

		void addUser(Server &server,Client c);
};

#endif
