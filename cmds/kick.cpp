#include "../headers/Server.hpp"
#include "../headers/Client.hpp"
#include "../headers/Channel.hpp"

void Server::kick(std::string buffer, int fd)
{
	// /kick #channel_name user_name
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

	this->channel_ok = 0;

	if (my_vec.size() < 3){
		std::cerr << "\033[1;91mWrong command format. Especially: /kick #channel user_name\033[0m" << std::endl;
		return;
	}

	// Get index of the client to remove (we found index for inside the channels.)
	unsigned int index = 0;
	while (this->channels_.size() > index)
	{
		if (this->channels_[index].getchannelAdminFd() == fd && this->channels_[index].getchannelName() == my_vec[1])
		{
			this->channel_ok = 1;
			break;
		}
		index++;
	}

	if (!this->channel_ok){
		std::cerr << "\033[1;91mYou are not an admin or you are trying to kick someone from a different channel.\033[0m" << std::endl;
		return;
	}

	my_vec[2] = my_vec[2].substr(1); //-> Remove the # character

	int kick_fd = -1;
	for (unsigned int s = 0; s < this->clients_.size(); s++)
	{
		if (this->clients_[s].getNickName() == my_vec[2])
		{
			kick_fd = this->clients_[s].getFd();
			break;
		}
	}

	// Check if user exists
	if (kick_fd == -1){
		std::cerr << "\033[1;91mUser not found.\033[0m" << std::endl;
		return;
	}

	// Check if the admin is trying to kick himself
	if (kick_fd == fd){
		std::cerr << "\033[1;91mYou can't kick yourself.\033[0m" << std::endl;
		return;
	}

	//Channel ok admin check
	if (this->channel_ok == 1)
	{
			//searching user to clients.
			std::cout << "***" << std::endl;
			unsigned int m = 0;
			while (this->channels_[index]._clientsFd.size() > m)
			{
				if (this->channels_[index]._clientsFd[m] == kick_fd)
				{
					this->channels_[index]._clientsFd.erase(this->channels_[index]._clientsFd.begin() + m);
					this->channels_[index].setClientCount(this->channels_[index].getchannelUserCount() - 1);
				}
				m++;
			}
	}
	std::string msg = ":" + this->client_ret(fd)->getNickName() + " KICK " + my_vec[1] + " " + my_vec[2] + " :Speaking English\r\n";
	send(fd, msg.c_str(), msg.size(), 0);
	std::cout << "\033[1;92mKicked succesfully...\033[0m" << std::endl;
	std::cout << this->client_ret(fd)->getNickName() << " Kicked " << my_vec[2] << " from the channel." << std::endl;
	buffer.clear();
}
