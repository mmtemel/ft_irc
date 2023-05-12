#include "../headers/Server.hpp"
#include "../headers/Client.hpp"
#include "../headers/Channel.hpp"

// void Server::mode(std::string buffer, int fd)
// {
	//do admin.
	//join(*this, buffer, fd);
	/*
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
	//std::cout << my_vec[0] << std::endl; #2
	//std::cout << my_vec[1] << std::endl; +o
	//std::cout << my_vec[2] << std::endl; ysensoy
	if (my_vec[0][0] != '#' || my_vec[1][0] != '+')
	{
		//std::cerr << "\033[1;91mError: Invalid args.\033[0m" << std::endl;
		return;
	}
	std::string channel_name = my_vec[0].substr(1); // #parse
	std::string mode_change = my_vec[1].substr(1); // +parse

	// /mode #2 +o ysensoy -> eger 2 kanalında değilsek direkt 2 kanalına ysensoy'u ekle ve admin yap.
	std::string message_mode = ":" + this->client_ret(fd)->getPrefixName() + " MODE " + my_vec[0] + " " + my_vec[1] + my_vec[2] + "\r\n";
	send(fd, message_mode.c_str(), message_mode.size(), 0);
	message_mode.clear();
	*/
// }
