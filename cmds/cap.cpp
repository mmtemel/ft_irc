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
		std::string args = "";
		while (i < buffer.size() && (buffer[i] > 32))
			command += buffer[i++]; //first ->command
		while (i < buffer.size() && (buffer[i] < 33))
			i++;
		my_vec.push_back(command);
	}
	std::cout << "----------------vec_size--------------:*" << my_vec.size() << "*" << std::endl;
	if (my_vec.size() < 5)
		this->is_nick_first = 1;
	i = 0;
	while (my_vec.size() > i)
	{
		if (my_vec[i] == "NICK")
		{
			this->nick_first(my_vec[i], my_vec[i + 1], fd);
			if(this->client_nick_check(temp_nick) == 1)
				break;
		}
		else if (my_vec[i] == "USER")
		{
			Client c(fd,my_vec[i+1],my_vec[i+2],my_vec[i+3],my_vec[i+4],this->temp_nick);
			this->clients_.push_back(c);
		}
		else if (my_vec[i] == "PASS")
		{
			//std::cout << "What is the password : " << my_vec[i + 1] << std::endl;
			this->my_password = my_vec[i + 1];
		}
		std::cout << "vector:" << my_vec[i] << std::endl;
		i++;
	}
	my_vec.clear();
	std::vector<Client>::iterator ite = this->clients_.end();
	for(std::vector<Client>::iterator it = this->clients_.begin(); it != ite; it++)
	{
		std::cout<<"class_attr:"<<(*it).getFd()<<","<<(*it).getUserName()<<","<<(*it).getHostName()<<",";
		std::cout<<(*it).getServername()<<","<<(*it).getReelName()<<","<<(*it).getNickName()<<","<<std::endl;
	}
	std::cout<<"cap sonu geldi"<<std::endl;
}
