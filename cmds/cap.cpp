#include "../headers/Server.hpp"
#include "../headers/Client.hpp"
#include "../headers/Channel.hpp"

void Server::cap(std::string line, int fd)
{
	std::vector<std::string> my_vec;
	unsigned int i = 0;
	while (line.size() > i)
	{
		std::string command = "";
		while (i < line.size() && (line[i] > 32))
			command += line[i++]; //first ->command
		while (i < line.size() && (line[i] < 33))
			i++;
		my_vec.push_back(command);
	}
	if (my_vec.size() < 7)
		this->is_nick_first = 1;
	i = 0;
	while (my_vec.size() > i)
	{
		if (my_vec[i] == "NICK")
		{
			this->nick_first(my_vec[i], my_vec[i + 1], fd);
			if(this->client_nick_check(temp_nick) == 1)
			{
				std::cout<<"NCIK IS ALREADY IN THE SERVER!\n";
				break;
			}
		}
		else if (my_vec[i] == "USER")
		{
			if (!this->client_nick_check(this->temp_nick) && my_vec.size() > i+4)
			{
				Client c(fd,my_vec[i+1],my_vec[i+2],my_vec[i+3],my_vec[i+4],this->temp_nick);
				this->clients_.push_back(c);
				std::cout<<"\033[1;92mNEW USER CREATED AND ADDED TO THE VEC!\033[0m\n";
			}
		}
		else if (my_vec[i] == "PASS")
			pass(my_vec[i+1], fd);
		i++;
	}
	my_vec.clear();
	// std::vector<Client>::iterator ite = this->clients_.end();
	// for(std::vector<Client>::iterator it = this->clients_.begin(); it != ite; it++)
	// {
	// 	std::cout<<"class_attr:"<<(*it).getFd()<<","<<(*it).getUserName()<<","<<(*it).getHostName()<<",";
	// 	std::cout<<(*it).getServername()<<","<<(*it).getReelName()<<","<<(*it).getNickName()<<","<<std::endl;
	// }
}
