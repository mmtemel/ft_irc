#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include "../headers/Server.hpp"
#include "../headers/Client.hpp"

class Client;

class Channel
{
	private:
		int clientCount;
		std::string channelName;
		std::string channelAdmin;
		//std::string	k;
		//int l;
		//bool n;
	public:
		Channel(std::string channelName);
		~Channel();
		//Client channelAdmin;
		//std::vector<Client> channelClients;
		//Client getAdmin();

		//int getchannelCount();
		void doAdmin();
		std::string getchannelAdmin();
		std::string getchannelName();
};

#endif
