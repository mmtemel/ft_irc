#include "../headers/Server.hpp"
#include "../headers/Client.hpp"
#include "../headers/Channel.hpp"

void Server::join(std::string buffer, int fd)
{
	std::cout<<"join func buffer: *"<<buffer<<"*"<<std::endl;
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
	if (my_vec[0][0] != '#' && my_vec[0][0] != '&')
	{
		std::cerr << "\033[1;91mWrong channel name, must start with '&' or '#'!\033[0m" << std::endl;
	}
	else
	{
		my_vec[0] = my_vec[0].substr(1, my_vec[0].size() - 1);
		unsigned int j = 0;
		while (j < this->channels_.size())
		{
			if (this->channels_[j].getchannelName() == my_vec[0])
			{
				// 2 farklı kullanıcı aynı kanala katılamıyor.
				std::cerr << "\033[1;91mThis channel is already exist:\033[0m" << my_vec[0] << std::endl;
				std::string b = ":" + this->clients_[this->client_ret(fd)].getNickName() + "!localhost JOIN " + my_vec[0] + "\r\n";
				send(fd, b.c_str(), b.size(), 0);
				b.clear();
				break;
			}
			j++;
		}
		if (j == this->channels_.size())
		{
			Channel c(my_vec[0]);
			this->channels_.push_back(c);
		}
		else
		{
			std::string b = ":" + this->clients_[this->client_ret(fd)].getNickName() + "!localhost JOIN " + my_vec[0] + "\r\n";
			this->write_send(fd, b);
			// send(fd, b.c_str(), b.size(), 0);
			b.clear();
		}
	}
	std::cerr << "\033[1;96mNumber of channel:\033[0m" << this->channels_.size() << std::endl;
	buffer.clear();
}
