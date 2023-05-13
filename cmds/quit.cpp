#include "../headers/Server.hpp"
#include "../headers/Client.hpp"
#include "../headers/Channel.hpp"

void Server::quit(std::string str, int fd)
{
	if (this->flag == 0)
	{
		std::cout << "\033[1;91m" << this->client_ret(fd)->getNickName() << " is leaving with message\033[0m ";
		exit(1);
	}

	if (this->client_ret(fd))
	{
		std::cout << "\033[1;91m" << this->client_ret(fd)->getNickName() << " is leaving with message\033[0m ";

		// Quit message
		unsigned int i = 0;
		std::string command = "";
		while (i < str.size() && (str[i] != '\r' && str[i] != '\n'))
			command += str[i++];

		std::cout << command << std::endl;

		// Get index of the client to remove
		unsigned int index = 0;
		for (; index < this->clients_.size(); ++index)
			if (this->clients_[index].getFd() == fd)
				break;

		// Set the admin to the previous client if the current admin quits
		unsigned int x = 0;

		while (this->channels_.size() > x)
		{
			unsigned int k = 0;
			while (this->channels_[x]._clientsFd[k] == fd)
			{
				if (this->channels_[x].getchannelAdminFd() == fd) //Admin
				{
					if (this->channels_[x].getchannelUserCount() == 1) // kanalı sil
					{
						this->channels_[x].setchannelAdminFd(-1);
						this->channels_[x]._clientsFd.pop_back();

						this->channels_[x]._clientsFd.erase(this->channels_[x]._clientsFd.begin() + k); // Kanaldan kullanıcıyı sil
						this->channels_.erase(this->channels_.begin() + x);
					}
					else // Kanalın adminliği değişiyor
					{
						this->channels_[x]._clientsFd.erase(this->channels_[x]._clientsFd.begin() + k);  // Kanaldan kullanıcıyı sil
						this->channels_[x].setchannelAdminFd(this->channels_[x]._clientsFd[1]);
					}
					this->channels_[x].setClientCount(this->channels_[x].getchannelUserCount() - 1);
				}
				else //user
				{
					this->channels_[x]._clientsFd.erase(this->channels_[x]._clientsFd.begin() + k); // Kanaldan kullanıcıyı sil
					this->channels_[x].setClientCount(this->channels_[x].getchannelUserCount() - 1);
				}
				k++;
			}
			x++;
		}

		std::string msg = ":" + this->clients_[index].getPrefixName() + " QUIT :Quit: " + str;
		send(fd, msg.c_str(), msg.size(), 0);
		// Remove the client from the vector and close the connection
		this->clients_.erase(this->clients_.begin() + index);
		close(fd);

		// int prevAdminFd = this->channels_[index].getchannelAdminFd();
		// if (fd == prevAdminFd)
		// {
		// 	// Loop back to the last client if current admin is the first one
		// 	int newAdminIndex;
		// 	int newAdminFd;
		// 	if (index == 0) {
		// 		newAdminIndex = this->clients_.size() - 1;
		// 	} else {
		// 		newAdminIndex = index - 1;
		// 	}
		// 	newAdminFd = this->clients_[newAdminIndex].getFd();
		// 	this->channels_[index].setchannelAdminFd(newAdminFd);

		// 	std::cout << "\033[1;92mAdmin changed to\033[0m " << this->client_ret(newAdminFd)->getNickName() << std::endl;
		// }

		// std::cout << "Current number of clients: " << this->clients_.size() << std::endl;

		// If the channel has no clients left, close it
		// if (this->clients_.empty())
		// {
			// std::cout << "No clients left, closing the channel." << std::endl;
			// this->channels_.erase(this->channels_.begin() + index);
		// }
	}
	(void)str; // unused parameter warning
}
