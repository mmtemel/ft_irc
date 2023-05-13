#include "../headers/Channel.hpp"

Channel::Channel(std::string channelName) : clientCount(1)
{
	this->channelName = channelName;
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

// void Channel::addUser(Server& server, Client c)
// {
// 	// Kullanıcı zaten kanalda mı diye kontrol et
// 	for (std::vector<Client>::iterator it = server.clients_.begin(); it != server.clients_.end(); ++it)
// 	{
// 		if (it->getNickName() == c.getNickName())
// 		{
// 			std::cerr << "\033[1;91mError: User " << c.getNickName() << " is already in channel " << this->channelName << "\033[0m" << std::endl;
// 			return;
// 		}
// 	}

// 	// Kanala kullanıcıyı ekle
// 	server.clients_.push_back(c);
// 	clientCount++;

// 	// Kullanıcıya JOIN mesajı gönder
// 	std::string joinMessage = ":" + this->channelAdmin + "!localhost JOIN " + this->channelName + "\r\n";
// 	send(c.getFd(), joinMessage.c_str(), joinMessage.size(), 0);

// 	// Kanaldaki tüm kullanıcılara USER mesajı gönder
// 	std::string userMessage = ":" + c.getNickName() + "!localhost USER " + this->channelName + "\r\n";
// 	for (std::vector<Client>::iterator it = server.clients_.begin(); it != server.clients_.end(); ++it)
// 	{
// 		if (it->getNickName() != c.getNickName())
// 		{
// 			send(it->getFd(), userMessage.c_str(), userMessage.size(), 0);
// 		}
// 	}

// 	// Kanala eklenen kullanıcının bilgilerini server log'una yazdır
// 	std::cerr << "\033[1;96m" << c.getNickName() << " joined channel " << this->channelName << "\033[0m" << std::endl;
// }

// std::vector<Client> Channel::getUsers()
// {
// 	return users_;
// }

// bool Channel::findUser(std::string nickname)
// {
//     for (std::vector<Client>::iterator it = users_.begin(); it != users_.end(); ++it) {
//         if (it->getNickName() == nickname) {
//             return true;
//         }
//     }
//     return false;
// }


