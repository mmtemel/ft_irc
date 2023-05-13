#include "../headers/Channel.hpp"

Channel::Channel(std::string channelName) : clientCount(1)
{
	this->channelName = channelName;
	this->k = false;
	this->l = false;
	this->n = false;
}

Channel::~Channel() {}

std::string Channel::getchannelName()
{
	return (this->channelName);
}

int Channel::getchannelAdminFd()
{
	return (this->channelAdminFd);
}


