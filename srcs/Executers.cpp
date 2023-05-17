#include "../headers/Channel.hpp"
#include "../headers/Client.hpp"
#include "../headers/Server.hpp"

void	Server::executeCommand(int fd)
{

	std::string	message;
	char buff[100] = {0};

	while (!std::strstr(buff, "\r\n"))
	{
		memset(buff, 0, 100);
		if(-1 == recv(fd, buff, 100, 0))
			std::cout<< "Error: Failed recv function!\n";
		message.append(buff);
	}

	std::stringstream newMessage(message);
	std::string buffer;

	while (std::getline(newMessage, buffer))
	{

		buffer = buffer.substr(0, buffer.length() - (buffer[buffer.length() - 1] == '\r'));
		
		unsigned int i = 0;
		while (i < buffer.size())
		{
			std::string command = "";
			std::string args = "";
			while (i < buffer.size() && (buffer[i] != ' ' && buffer[i] != '\r' && buffer[i] != '\n'))
				command += buffer[i++];
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
	unsigned int i = 0;
	while(i < command.size())
	{
		command[i] = std::toupper(command[i]);
		i++;
	}
	if (command == "NICK")
	{
		if (this->is_nick_first == 1)
			this->nick_first(command, args, fd);
		else
			this->nick_change(args, fd);
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
	if (command == "BOT")
		bot(args, fd);
	if (command == "USER")
		user(args, fd);
}
