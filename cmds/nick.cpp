#include "../headers/Server.hpp"
#include "../headers/Client.hpp"
#include "../headers/Channel.hpp"

void Server::nick_change(std::string command_n, std::string buffer, int fd)
{
	std::cout<<"nick_change_command:*"<<command_n<<"*"<<std::endl;
	std::string command = "";
	unsigned int i = 0;
	while (i < buffer.size() && (buffer[i] > 32))
		command += buffer[i++]; //first ->command
	if(this->client_ret(fd) && !this->client_nick_check(command))
	{
		std::cout << "Will change the nick fd: *"<<fd<<"*"<<std::endl;
		std::string b = ":" + this->client_ret(fd)->getNickName()+"!localhost NICK "+command+"\r\n";
		send(fd, b.c_str(), b.size(), 0);
		this->client_ret(fd)->setNickName(command);
		buffer.clear();
	}
	else
		std::cout << "\033[1;92mThere is some user has the same nickname or user doesn't exist!\033[0m" << std::endl;
}


void Server::nick_first(std::string command_n, std::string buffer, int fd)
{
	std::cout<<"nick_first_command:*"<<command_n<<"*"<<std::endl;
	std::vector<std::string> my_vec;
	my_vec.push_back(command_n);
	unsigned int i = 0;
	while (buffer.size() > i)
	{
		std::string command = "";
		std::string args = "";
		while (i < buffer.size() && (buffer[i] > 32))
			command += buffer[i++]; //first ->command
		while (i < buffer.size() && (buffer[i] < 33))
			i++;
		my_vec.push_back(command);
	}
	std::cout << "----------------_nick_first_vec_size--------------:*" << my_vec.size() << "*" << std::endl;
	if (my_vec.size() < 3)
		this->is_nick_first = 1;
	i = 0;
	while (my_vec.size() > i)
	{
		if (my_vec[i] == "NICK")
		{
			this->temp_nick = my_vec[i + 1];
			if(this->client_nick_check(temp_nick) == 1)
				break;
		}
		else if (my_vec[i] == "USER")
		{
			if (!this->client_nick_check(this->temp_nick))
			{
				Client c(fd,my_vec[i+1],my_vec[i+2],my_vec[i+3],my_vec[i+4],this->temp_nick);
				this->clients_.push_back(c);
			}
			else
				std::cout << "Nickname exists!" << std::endl;
		}
		std::cout << "vector:" << my_vec[i] << std::endl;
		i++;
	}
	my_vec.clear();
	this->is_nick_first = 0;
	std::vector<Client>::iterator it_begin = this->clients_.begin();
	std::vector<Client>::iterator it_end = this->clients_.end();
	while (it_begin != it_end)
	{
		std::cout << "class_attr:"<<(*it_begin).getFd() << "," << (*it_begin).getUserName() << ","<<(*it_begin).getHostName() << ",";
		std::cout << (*it_begin).getServername() << "," << (*it_begin).getReelName() << "," << (*it_begin).getNickName() << "," << std::endl;
		++it_begin;
	}
	std::cout<<"cap sonu geldi"<<std::endl;
}
