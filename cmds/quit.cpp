#include "../headers/Server.hpp"
#include "../headers/Client.hpp"
#include "../headers/Channel.hpp"

void Server::quit(std::string str, int fd)
{
	this->pass_fd[fd].erase();
	if (this->flag == 0)
	{
		//There is no join
		if(this->client_ret(fd))
		{
			std::cerr << "\033[1;91mError: " << this->client_ret(fd)->getNickName() << " is leaving with message\033[0m" << std::endl;
			for (size_t i = 0; i < pollfds.size(); i++)
			{
				if(fd == pollfds[i].fd)
				{
					std::string b = ":" + this->client_ret(fd)->getPrefixName() + " QUIT :Leaving " + str + "\r\n";
					send(fd, b.c_str(), b.size(), 0);
					close(pollfds[i].fd);
					pollfds.erase(pollfds.begin()+i);
				}
			}
			for (size_t i = 0; i < pollfds.size(); i++)
			{
				if(fd == clients_[i].getFd())
				{
					clients_.erase(clients_.begin()+i);
				}
			}
		}
		else
		{
			for (size_t i = 0; i < pollfds.size(); i++)
			{
				if(fd == pollfds[i].fd)
				{
					std::string b = "QUIT :Leaving " + str + "\r\n";
					send(fd, b.c_str(), b.size(), 0);
					close(pollfds[i].fd);
					pollfds.erase(pollfds.begin()+i);
				}
			}
		}
	}

	std::vector<std::string> my_vec;
	unsigned int i = 0;

	while (str.size() > i)
	{
		std::string command = "";
		while (i < str.size() && (str[i] != ' ' && str[i] != '\r' && str[i] != '\n'))
			command += str[i++];
		while (i < str.size() && (str[i] == ' ' || str[i] == '\r' || str[i] == '\n'))
			i++;
		my_vec.push_back(command);
	}

	i = 0;
	bool _flag = false;
	if (my_vec.size() > 1 && my_vec[1][0] == ':')
		my_vec[1] = my_vec[1].substr(1); //cut the :

	while (this->channels_.size() > i)
	{
		if (this->channels_[i].getchannelName() == my_vec[1])
		{
			_flag = true;
			break;
		}
		i++;
	}

	if (this->client_ret(fd) && (_flag == true || this->flag == 1))
	{
		std::cout << "\033[1;91m" << this->client_ret(fd)->getNickName() << " is leaving with message\033[0m" << std::endl;

		for (size_t i = 0; i < pollfds.size(); i++)
		{
			if(fd == pollfds[i].fd)
			{
				std::string b = ":" + this->client_ret(fd)->getPrefixName() + " QUIT " + str + "\r\n";
				send(fd, b.c_str(), b.size(), 0);
				close(pollfds[i].fd);
				pollfds.erase(pollfds.begin()+i);
			}
		}
		for (size_t i = 0; i < pollfds.size(); i++)
		{
			if(fd == clients_[i].getFd())
			{
				clients_.erase(clients_.begin()+i);
			}
		}

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
						this->channels_.erase(this->channels_.begin() + x);
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
	}
	else if(_flag == true || this->flag == 1)
	{
		for (size_t i = 0; i < pollfds.size(); i++)
		{
			if(fd == pollfds[i].fd)
			{
				std::string b = "QUIT :Leaving " + str + "\r\n";
				send(fd, b.c_str(), b.size(), 0);
				close(pollfds[i].fd);
				pollfds.erase(pollfds.begin()+i);
			}
		}
	}
	my_vec.clear();
	std::vector<Client>::iterator ite = this->clients_.end();
	for(std::vector<Client>::iterator it = this->clients_.begin(); it != ite; it++)
	{
		std::cout<<"class_attr:"<<(*it).getFd()<<","<<(*it).getUserName()<<","<<(*it).getHostName()<<",";
		std::cout<<(*it).getServername()<<","<<(*it).getReelName()<<","<<(*it).getNickName()<<","<<std::endl;
	}
}
