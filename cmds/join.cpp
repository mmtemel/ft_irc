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

	if (my_vec.size() > 0 && my_vec[0][0] != '#')
	{
		std::cerr << "\033[1;91mError: channel name starts with #!\033[0m" << std::endl;
		std::string b = ":" + this->client_ret(fd)->getPrefixName()+" NOTICE "+ this->client_ret(fd)->getNickName() +" Error: channel name has to start with #!\r\n";
		send(fd, b.c_str(), b.size(), 0);
		b = ":" + this->client_ret(fd)->getPrefixName()+" NOTICE "+ this->client_ret(fd)->getNickName() +" Usage: /JOIN #channelname channelkey\r\n";
		send(fd, b.c_str(), b.size(), 0);
		return;
	}
	/* Channel creation as much as channel size.*/
	int flag = 0; //admin check flag 1 user flag 0 admin
	unsigned int idx = 0;
	while(idx < channels_.size())
	{
		if (channels_[idx].getchannelName() == my_vec[0])
			flag = 1;
		idx++;
	}
	if (flag == 0) // create channel you are the admin
	{
		Channel c(my_vec[0]);
		c.setchannelAdminFd(this->client_ret(fd)->getFd());
		std::cout << "\033[1;92mAdmin_fd : \033[0m" << c.getchannelAdminFd() << std::endl;
		c._clientsFd.push_back(fd);
		this->channels_.push_back(c);
		std::string b = ":" + this->client_ret(fd)->getPrefixName() + " JOIN " + my_vec[0] + "\r\n";
		send(fd, b.c_str(), b.size(), 0);
		if(my_vec.size() > 1)
		{
			for (size_t x = 0; x < this->channels_.size(); x++)
			{
				if(this->channels_[x].getchannelName() == my_vec[0])
				{
					this->channels_[x].k = true;
					this->channels_[x].setChannelKey(my_vec[1]);
					std::cout<<"YOU CREATED CHANNEL "<<this->channels_[x].getchannelName()<<" WITH K MODE! THIS CHANNEL HAS PASSWORD!\n";
					std::string b = ":" + this->client_ret(fd)->getPrefixName()+" NOTICE "+ this->client_ret(fd)->getNickName() +" YOU CREATED CHANNEL "+this->channels_[x].getchannelName()+" WITH K MODE! THIS CHANNEL HAS PASSWORD!\r\n";
					send(fd, b.c_str(), b.size(), 0);
				}
			}
		}
	}
	else //channel already exist
	{
		idx = 0;
		while(idx < channels_.size())
		{
			if (channels_[idx].getchannelName() == my_vec[0])
			{
				if(channels_[idx].l == true && channels_[idx].getChannelLimit() <= channels_[idx].getchannelUserCount()) //l user limit
				{
					std::cout<<"CHANNEL IS FULL, TRY ANOTHER TIME OR CONTACT WITH ADMIN!\n";
					std::string b = ":" + this->client_ret(fd)->getPrefixName()+" NOTICE "+ this->client_ret(fd)->getNickName() +" CHANNEL IS FULL, TRY ANOTHER TIME OR CONTACT WITH ADMIN!\r\n";
					send(fd, b.c_str(), b.size(), 0);
					return;
				}
				else if(channels_[idx].k == true && (my_vec.size() < 2 || channels_[idx].getChannelKey() != my_vec[1]))
				{
					std::cout<<"WRONG KEY, THIS CHANNEL IS PASSWORD PROTECTED!\n";
					std::string b = ":" + this->client_ret(fd)->getPrefixName()+" NOTICE "+ this->client_ret(fd)->getNickName() +" WRONG KEY, THIS CHANNEL IS PASSWORD PROTECTED!\r\n";
					send(fd, b.c_str(), b.size(), 0);
					return;
				}
				else
				{
					channels_[idx]._clientsFd.push_back(fd);
					channels_[idx].setClientCount(channels_[idx].getchannelUserCount() + 1);
					std::cout << "\033[1;92mAdmin_fd : \033[0m" << channels_[idx].getchannelAdminFd() << std::endl;
				}
			}
			idx++;
		}
		std::string b = ":" + this->client_ret(fd)->getPrefixName() + " JOIN " + my_vec[0] + "\r\n";
		send(fd, b.c_str(), b.size(), 0);
	}
	this->flag = 1; // two /server localhost 4242.
	unsigned int j = 0;
	int	fdTemp;
	while (j < channels_.size() && channels_[j].getchannelName() == my_vec[0]) //what is this while ???
	{
		unsigned int k = 0;
		while (k < channels_[j]._clientsFd.size())
		{
			if (channels_[j]._clientsFd[k] != fd)
			{
				fdTemp = channels_[j]._clientsFd[k];
				std::string b = ":" + this->client_ret(fd)->getPrefixName() + " JOIN " + my_vec[0] + "\r\n";
				send(fdTemp, b.c_str(), b.size(), 0);
				b.clear();
			}
			k++;
		}
		j++;
	}
	std::cerr << "\033[1;96mNumber of channels:\033[0m" << this->channels_.size() << std::endl;
	buffer.clear();
}
