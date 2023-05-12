#include "../headers/Server.hpp"
#include "../headers/Client.hpp"
#include "../headers/Channel.hpp"

void Server::privmsg(std::string buffer, int fd)
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

	std::cout << my_vec[0] << std::endl;
	std::cout << my_vec[1] << std::endl;

	if (my_vec[0][0] == '#')
	{
		// Kanaldaki herkese broadcast, kendinin fd'si hariç
		unsigned int j = 0;
		while (channels_.size() > 0 && channels_[j].getchannelName() == my_vec[0])
		{
			unsigned int k = 0;
			while (k < channels_[j]._clientsFd.size())
			{
				if (channels_[j]._clientsFd[k] != fd)
				{
					int fdTemp = channels_[j]._clientsFd[k];
					//std::cout << "GELEN FD " + std::to_string(fdTemp) << "\n";
					std::string b = ":" + this->client_ret(fd)->getPrefixName() + " PRIVMSG " + my_vec[0] + " " + my_vec[1] + "\r\n";
					send(fdTemp, b.c_str(), b.size(), 0);
					b.clear();
				}
				k++;
			}
			j++;
		}
	}
}
