#include "../headers/Channel.hpp"
#include "../headers/Client.hpp"
#include "../headers/Server.hpp"

void	Server::executeCommand(int fd)
{
	while (this->buffer.find("\r\n"))
	{
		buffer.clear();
		char buff[BUFFER_SIZE];
		memset(buff, 0, BUFFER_SIZE); /* Cleaning up memory */
		int bytes_received = recv(fd, buff, BUFFER_SIZE, 0);
		if(buff[0] > 31)
			std::cout << "Received message: *" << buff << "* from fd: *" << fd << "*" << std::endl;
		if (bytes_received < 0)
		{
			std::cerr << "Receive ended" << std::endl;
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
	std::cout << "commmand: *" << command << "*" << std::endl;
	std::cout << "args: *" << args << "*" << std::endl;

	std::transform(command.begin(), command.end(), command.begin(), ::toupper);
	if (command == "NICK")
	{
		if (this->is_nick_first == 1)
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
	if (command == "PRIVMSG")
		privmsg(args, fd);
	if (command == "PING")
		ping(args, fd);
	if (command == "PASS")
		pass(args, fd);
	if (command == "KICK")
		kick(args, fd);
	if (command == "MODE")
		mode(args, fd);
	if (command == "KILL")
		kill(args, fd);
}
