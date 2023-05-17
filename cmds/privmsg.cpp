#include "../headers/Server.hpp"
#include "../headers/Client.hpp"
#include "../headers/Channel.hpp"

void Server::privmsg(std::string buffer, int fd)
{
	std::vector<std::string> my_vec;
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

	if (my_vec[0][0] == '#')
	{
		// Kanaldaki herkese broadcast, kendinin fd'si hariç
		unsigned int j = 0;
		while (j < channels_.size())
		{
			if(channels_[j].getchannelName() == my_vec[0])
			{
				std::vector<int>::iterator it = std::find(channels_[j]._clientsFd.begin(), channels_[j]._clientsFd.end(), fd);
				if(channels_[j].n == true && it == channels_[j]._clientsFd.end())
				{
					std::cout<<"NO MESSAGES ALLOWED FROM THE OUTSIDE TO "<<this->channels_[j].getchannelName()<<"!\n";
					std::string b = ":" + this->client_ret(fd)->getPrefixName()+" NOTICE "+ this->client_ret(fd)->getNickName() +" NO MESSAGES ALLOWED FROM THE OUTSIDE TO "+this->channels_[j].getchannelName()+"!\r\n";
					send(fd, b.c_str(), b.size(), 0);
					return;
				}
				unsigned int k = 0;
				while (k < channels_[j]._clientsFd.size())
				{
					if (channels_[j]._clientsFd[k] != fd)
					{
						int fdTemp = channels_[j]._clientsFd[k];
						std::string b = ":" + this->client_ret(fd)->getPrefixName() + " PRIVMSG " + my_vec[0] + " ";
						for (unsigned int m = 1; m < my_vec.size(); m++)
							b += my_vec[m] + " ";
						b += "\r\n";
						send(fdTemp, b.c_str(), b.size(), 0);
						b.clear();
					}
					k++;
				}
			}
			j++;
		}
	}
}
