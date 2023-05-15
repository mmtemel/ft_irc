#include "../headers/Server.hpp"
#include "../headers/Client.hpp"
#include "../headers/Channel.hpp"

void Server::quit(std::string str, int fd)
{
	if (this->flag == 0)
	{
		//There is no join
		std::cerr << "\033[1;91mError: " << this->client_ret(fd)->getNickName() << " is leaving with message\033[0m" << std::endl;
		exit(1);
	}

	std::vector<std::string> my_vec;
	unsigned int i = 0;

	while (buffer.size() > i)
	{
		std::string command = "";
		while (i < buffer.size() && (buffer[i] != ' ' && buffer[i] != '\r' && buffer[i] != '\n'))
			command += buffer[i++];
		while (i < buffer.size() && (buffer[i] == ' ' || buffer[i] == '\r' || buffer[i] == '\n'))
			i++;
		my_vec.push_back(command);
	}

	i = 0;
	bool flag = false;
	my_vec[1] = my_vec[1].substr(1); //cut the :

	while (this->channels_.size() > i)
	{
		if (this->channels_[i].getchannelName() == my_vec[1])
		{
			flag = true;
			break;
		}
		i++;
	}

	if (this->client_ret(fd) && flag == true)
	{
		std::cout << "\033[1;91m" << this->client_ret(fd)->getNickName() << " is leaving with message\033[0m" << std::endl;

		// Get index of the client to remove
		unsigned int index = 0;
		for (; index < this->clients_.size(); index++)
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
						this->channels_[x]._clientsFd.erase(this->channels_[x]._clientsFd.begin() + k); // Kanaldan kullanıcıyı sil
						this->channels_[x]._clientsFd.pop_back();
						this->channels_.erase(this->channels_.begin() + x);
						std::cout << "Burada mi3" << std::endl;
						break;
					}
					else // change to client admin
					{
						this->channels_[x].setchannelAdminFd(this->channels_[x]._clientsFd[1]);
						this->channels_[x]._clientsFd.erase(this->channels_[x]._clientsFd.begin() + k);  // Kanaldan kullanıcıyı sil
					}
					this->channels_[x].setClientCount(this->channels_[x].getchannelUserCount() - 1);
				}
				else // user set
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
		//close(fd);
	}
	else
	{
		std::cerr << "\033[1;91mError...\033[0m" << std::endl;
		return;
	}
}
