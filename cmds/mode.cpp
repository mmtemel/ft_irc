#include "../headers/Server.hpp"
#include "../headers/Client.hpp"
#include "../headers/Channel.hpp"

void Server::mode(std::string buffer, int fd)
{
	std::vector<std::string> my_vec;
	std::string command = "";
	unsigned int i = 0;
	while (buffer.size() > i)
	{
		std::string command = "";
		while (i < buffer.size() && (buffer[i] != ' ' && buffer[i] != '\r' && buffer[i] != '\n'))
			command += buffer[i++]; //first ->command
		while (i < buffer.size() && (buffer[i] == ' ' || buffer[i] == '\r' || buffer[i] == '\n'))
			i++;
		my_vec.push_back(command);
	}
	i = 0;
	bool channel_exists_admin = false;
	unsigned int j = 0;
	while (i < my_vec.size())
	{
		j = 0;
		while (j < this->channels_.size())
		{
			if (this->channels_[j].getchannelName() == my_vec[i] && this->channels_[j].getchannelAdminFd() == fd)//&& ekle fd
			{
				channel_exists_admin = true;
				break;
			}
			j++;
		}
		if (channel_exists_admin)
			break;
		i++;
	}
	if (!channel_exists_admin)
	{
		std::cout<<"\033[1;91mNo such channel and/or not channel admin!\033[0m\n";
		return;
	}
	else
		std::cout<<"\033[1;94mChannel exist and fd is the admin!\033[0m\n";
	i++;
	if(i < my_vec.size())
	{
		if(my_vec[i][0] == '+')
		{
			if(my_vec[i][1] == 'n' && my_vec[i].size() == 2)
			{
				this->channels_[j].n = true;
				std::cout<<"CHANNEL "<<this->channels_[j].getchannelName()<<"'S N MODE SET! NO MESSAGES FROM THE OUTSIDE!\n";
				std::string b = ":" + this->client_ret(fd)->getPrefixName()+" NOTICE "+ this->client_ret(fd)->getNickName() +" YOU CHANGED CHANNEL "+this->channels_[j].getchannelName()+"'S N MODE TO SET! NO MESSAGES FROM THE OUTSIDE!\r\n";
				send(fd, b.c_str(), b.size(), 0);
			}
			else if(my_vec[i][1] == 'l' && my_vec[i].size() == 2 && i+1 < my_vec.size())
			{
				if(atoi(my_vec[i+1].c_str()) < 1)
					return;
				this->channels_[j].l = true;
				try
				{
					this->channels_[j].setChannelLimit(atoi(my_vec[i+1].c_str()));
					std::cout<<"CHANNEL "<<this->channels_[j].getchannelName()<<"'S L MODE SET! USER LIMIT IS "<<atoi(my_vec[i+1].c_str())<<"\n";
					std::string b = ":" + this->client_ret(fd)->getPrefixName()+" NOTICE "+ this->client_ret(fd)->getNickName() +" YOU CHANGED CHANNEL "+this->channels_[j].getchannelName()+"'S L MODE TO SET! USER LIMIT IS "+my_vec[i+1]+"!\r\n";
					send(fd, b.c_str(), b.size(), 0);
				}
				catch(const std::exception& e)
				{
					std::cerr << e.what() << '\n';
				}
			}
			else if(my_vec[i][1] == 'k' && my_vec[i].size() == 2 && i+1 < my_vec.size())
			{
				this->channels_[j].k = true;
				this->channels_[j].setChannelKey(my_vec[i+1]);
				std::cout<<"CHANNEL "<<this->channels_[j].getchannelName()<<"'S K MODE SET! THIS CHANNEL HAS PASSWORD!\n";
				std::string b = ":" + this->client_ret(fd)->getPrefixName()+" NOTICE "+ this->client_ret(fd)->getNickName() +" YOU CHANGED CHANNEL "+this->channels_[j].getchannelName()+"'S K MODE TO SET! THIS CHANNEL HAS PASSWORD!\r\n";
				send(fd, b.c_str(), b.size(), 0);
			}
		}
		else if(my_vec[i][0] == '-')
		{
			if(my_vec[i][1] == 'n' && my_vec[i].size() == 2)
			{
				this->channels_[j].n = false;
				std::cout<<"CHANNEL "<<this->channels_[j].getchannelName()<<"'S N MODE UNSET! MESSAGES ACCEPTED FROM THE OUTSIDE!\n";
				std::string b = ":" + this->client_ret(fd)->getPrefixName()+" NOTICE "+ this->client_ret(fd)->getNickName() +" YOU CHANGED CHANNEL "+this->channels_[j].getchannelName()+"'S N MODE TO UNSET! MESSAGES ACCEPTED FROM THE OUTSIDE!\r\n";
				send(fd, b.c_str(), b.size(), 0);
			}
			else if(my_vec[i][1] == 'l' && my_vec[i].size() == 2)
			{
				this->channels_[j].l = false;
				std::cout<<"CHANNEL "<<this->channels_[j].getchannelName()<<"'S L MODE UNSET! THERE IS NO USER LIMIT!\n";
				std::string b = ":" + this->client_ret(fd)->getPrefixName()+" NOTICE "+ this->client_ret(fd)->getNickName() +" YOU CHANGED CHANNEL "+this->channels_[j].getchannelName()+"'S L MODE TO UNSET! THERE IS NO USER LIMIT!\r\n";
				send(fd, b.c_str(), b.size(), 0);
			}
			else if(my_vec[i][1] == 'k' && my_vec[i].size() == 2)
			{
				this->channels_[j].k = false;
				std::cout<<"CHANNEL "<<this->channels_[j].getchannelName()<<"'S K MODE UNSET! THIS CHANNEL HAS NO PASSWORD!\n";
				std::string b = ":" + this->client_ret(fd)->getPrefixName()+" NOTICE "+ this->client_ret(fd)->getNickName() +" YOU CHANGED CHANNEL "+this->channels_[j].getchannelName()+"'S K MODE TO UNSET! THIS CHANNEL HAS NO PASSWORD!\r\n";
				send(fd, b.c_str(), b.size(), 0);
			}
		}
	}
}
