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
		
	public:
		Channel(std::string channelName);
		~Channel();
		std::vector<Client> channelClients;

		Client getAdmin();
		void setAdmin(Channel);

		//int getchannelCount();
		void doAdmin();
		Client getchannelAdmin();
		std::string getchannelName();
};

#endif
