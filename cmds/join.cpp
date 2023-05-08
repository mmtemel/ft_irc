#include "../headers/Server.hpp"
#include "../headers/Client.hpp"
#include "../headers/Channel.hpp"

void Server::join(Server &server, std::string buffer, int fd)
{
	std::vector<std::string> my_vec;
	std::string command = "";
	int i = 0;
	while (buffer.size() > i)
	{
		std::string command = "";
		while (i < buffer.size() && (buffer[i] != ' ' && buffer[i] != '\r' && buffer[i] != '\n'))
			command += buffer[i++]; //first ->command
		while (i < buffer.size() && (buffer[i] == ' ' || buffer[i] == '\r' || buffer[i] == '\n'))
			i++;
		my_vec.push_back(command);
	}
	i = -1;
	while (my_vec.size() > ++i)
	{
		if (my_vec[i][0] != '#' && my_vec[i][0] != '&')
		{
			std::cerr << "\033[1;91mError couldn't connect the channel..\033[0m" << std::endl;
			continue;
		}
		my_vec[i] = my_vec[i].substr(1, my_vec[i].size() - 1);
		int j = -1;
		while (++j < this->channels_.size())
		{
			if (this->channels_[j].getchannelName() == my_vec[i])
			{
				// 2 farklı kullanıcı aynı kanala katılamıyor.
				std::cerr << "\033[1;91mThis channel is already exist:\033[0m" << my_vec[i] << std::endl;
				break;
			}
		}
		if (j == this->channels_.size())
		{
			Channel c(my_vec[i]);
			this->channels_.push_back(c);
			// if there is just one person you have to admin this channel
			// if (this->channels_.size() == 1)
			// {
			// 	c.doAdmin();
			// }
		}
		std::string b = ":" + this->temp_nick + "!localhost JOIN " + my_vec[i] + "\r\n";
		send(this->new_socket, b.c_str(), b.size(), 0);
		b.clear();
	}
	std::cerr << "\033[1;96mNumber of channel:\033[0m" << this->channels_.size() << std::endl;
	buffer.clear();
}
