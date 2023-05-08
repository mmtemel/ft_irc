#include "../headers/Channel.hpp"

Channel::Channel(std::string channelName)
{
	this->channelName = channelName;
}

Channel::~Channel() {}

std::string Channel::getchannelName()
{
	return (this->channelName);
}

Client Channel::getchannelAdmin()
{
	std::vector<Client>::iterator it = this->channelClients.begin();
	return(*it);
}
