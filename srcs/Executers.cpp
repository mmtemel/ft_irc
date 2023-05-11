#include "../headers/Channel.hpp"
#include "../headers/Client.hpp"
#include "../headers/Server.hpp"

void	Server::executeCommand(int fd)
{
	while (this->buffer.find("\r\n"))
	{
		buffer.clear();
		char buff[BUFFER_SIZE];
		memset(buff, 0, BUFFER_SIZE);
		int bytes_received = recv(fd, buff, BUFFER_SIZE, 0);
		if(buff[0] > 31)
			std::cout << "\033[1;94mReceived message: *" << buff << "*\nFrom fd: *" << fd << "*\033[0m" << std::endl;
		if (bytes_received < 0)
		{
			std::cerr << "\033[1;94mReceive ended\033[0m" << std::endl;
			return ;
		}
		buffer = std::string(buff);
		unsigned int i = 0;
		while (i < buffer.size())
		{
			std::string command = "";
			std::string args = "";
			while (i < buffer.size() && (buffer[i] != ' ' && buffer[i] != '\r' && buffer[i] != '\n'))
				command += buffer[i++]; //first ->command
			while (i < buffer.size() && (buffer[i] == ' ' || buffer[i] == '\r' || buffer[i] == '\n'))
				i++;
			while (i < buffer.size())
				args += buffer[i++];
			executable(command, args, fd);
			buffer.erase(0, i);
		}
	}
}

void	Server::executable(std::string command, std::string args, int fd)
{
	std::cout<<"commmand: *" << command << "*"<<std::endl;
	std::cout << "args: *" << args << "*" << std::endl;
	// if (!strncmp(cap_ls[0].c_str(), command.c_str(), 3))
	// 	add(*this, args);
	if (command == "NICK")
	{
		if(this->is_nick_first == 1)
			this->nick_first(command, args, fd);
		else
			this->nick_change(command, args, fd);
	}
	if (command == "JOIN")
		join(args, fd);
	if (command == "QUIT")
		quit(args, fd);
	if (command == "CAP")
		cap(args, fd);
	if (command == "PRIVMSG") //channel specified message and /ping spesific_addr
		privmsg(args, fd);
	if (command == "PING") //just /ping
		ping(args, fd);
	// if (!strncmp(cap_ls[5].c_str(), command.c_str(), 4))
	// 	kick(*this, args);
}
