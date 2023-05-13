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
		int limit;
		std::string key;
	public:
		Channel(std::string channelName);
		~Channel();

		std::vector<int> _clientsFd;
		bool	k;
		bool	l;
		bool	n;

		int getchannelAdminFd();
		int getchannelUserCount() {return (this->clientCount);};
		std::string getchannelName();

		void setchannelAdminFd(int adminFd) {this->channelAdminFd = adminFd;}
		void setClientCount(int i) {this->clientCount = i;}

		int getChannelLimit() {return (this->limit);}
		std::string getChannelKey() {return (this->key);}

		void setChannelLimit(int limit) {this->limit = limit;}
};

#endif
