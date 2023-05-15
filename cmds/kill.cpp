#include "../headers/Server.hpp"
#include "../headers/Client.hpp"
#include "../headers/Channel.hpp"

void Server::kill(std::string buffer, int fd)
{
	//kill name reason
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

	if (my_vec.size() != 2){
		std::cerr << "\033[1;91mError: Kill args\033[0m" << std::endl;
		return;
	}

	bool flag = false;
	for (unsigned int i = 0; i < this->clients_.size(); i++) {
		if (this->clients_[i].getNickName() == my_vec[0])
		{
			flag = true;
			int target_fd = this->clients_[i].getFd();
			std::string msg = ":" + this->client_ret(fd)->getNickName() + " KILL " + my_vec[0] + " :Killed by " + this->client_ret(fd)->getNickName() + " " + my_vec[1] + "\r\n";
			send(target_fd, msg.c_str(), msg.size(), 0);
			close(target_fd);
			this->clients_.erase(this->clients_.begin() + i);
			break;
		}
	}

	if (flag == false)
	{
		std::cerr << "\033[1;91mThe user couldn't find\033[0m" << std::endl;
		return;
	}
	buffer.clear();
}
