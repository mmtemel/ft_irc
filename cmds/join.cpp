#include "../headers/Server.hpp"
#include "../headers/Client.hpp"
#include "../headers/Channel.hpp"

void Server::join(std::string buffer, int fd)
{
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
	while (my_vec.size() > i)
	{
		if (my_vec[i][0] != '#' && my_vec[i][0] != '&')
		{
			std::cerr << "\033[1;91mError couldn't connect the channel..\033[0m" << std::endl;
			continue;
		}
		/* Channel creation as much as channel size.*/

		int flag = 0;
		unsigned int idx = 0;
		while(idx < channels_.size())
		{
			if (channels_[idx].getchannelName() == my_vec[i])
				flag = 1;
			idx++;
		}

		if (flag == 0)
		{
			Channel c(my_vec[i]);

			c.setchannelAdminFd(this->client_ret(fd)->getFd());
			std::cout << "\033[1;92mAdmin_fd : \033[0m" << c.getchannelAdminFd() << std::endl;
			c._clientsFd.push_back(fd);
			this->channels_.push_back(c);

			std::string b = ":" + this->client_ret(fd)->getPrefixName() + " JOIN " + my_vec[i] + "\r\n";
			send(fd, b.c_str(), b.size(), 0);
		}
		else
		{
			idx = 0;
			while(idx < channels_.size())
			{
				if (channels_[idx].getchannelName() == my_vec[i])
				{
					channels_[idx]._clientsFd.push_back(fd);
					channels_[idx].setClientCount(channels_[idx].getchannelUserCount() + 1);
					std::cout << "\033[1;92mAdmin_fd : \033[0m" << channels_[idx].getchannelAdminFd() << std::endl;
				}
				idx++;
			}
			std::string b = ":" + this->client_ret(fd)->getPrefixName() + " JOIN " + my_vec[i] + "\r\n";
			send(fd, b.c_str(), b.size(), 0);
		}
		this->flag = 1; // two /server localhost 4242.
		unsigned int j = 0;
		int	fdTemp;
		while (j < channels_.size() && channels_[j].getchannelName() == my_vec[0])
		{
			unsigned int k = 0;
			while (k < channels_[j]._clientsFd.size())
			{
				if (channels_[j]._clientsFd[k] != fd)
				{
					fdTemp = channels_[j]._clientsFd[k];
					std::string b = ":" + this->client_ret(fd)->getPrefixName() + " JOIN " + my_vec[i] + "\r\n";
					send(fdTemp, b.c_str(), b.size(), 0);
					b.clear();
				}
				k++;
			}
			j++;
		}
		i++;
	}
	std::cerr << "\033[1;96mNumber of channel:\033[0m" << this->channels_.size() << std::endl;
	buffer.clear();
}
