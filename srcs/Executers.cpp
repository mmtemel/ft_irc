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
		// int flag = 0;
		// std::cout<<"TEMP1: *"<<temp<<"*"<<std::endl;
		buffer = buffer.substr(0, buffer.length() - (buffer[buffer.length() - 1] == '\r'));
		std::cout<<"BUFFER: *"<<buffer<<"*"<<std::endl;
		
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

		// std::vector<std::string> arguments;
		// std::string buf, buf2, commandName = temp.substr(0, temp.find(' '));
		// std::stringstream args(temp.substr(commandName.length(), temp.length()));

		// while (args >> buf)
		// {
			// if (buf[0] == ':' || flag) {
				// buf2 += buf + " "; flag = 1;
				// std::cout<<"BUF2: *"<<buf2<<"*"<<std::endl;
			// }
			// else if (buf.size() > 0)
				// arguments.push_back(buf);
		// }
		// if (buf2.size() > 0) {
			// arguments.push_back(buf2);
		// }
		
		// arguments.insert(arguments.begin(), commandName);

		// for (size_t i = 0; i < arguments.size(); i++)
		// {
			// std::cout<<"ARGUMENTS: *"<<arguments[i]<<"*"<<std::endl;
		// }

		// if (arguments[0] == "USER" )
		// {
		// 	std::string errMsg = "ERROR :Error either password was not given or the nick was in use \r\n";
		// 	send(fd, errMsg.c_str(), errMsg.size(), 0);
		// 	// quit("Passwords didn't match" ,fd);
		// 	break ;
		// }

		// if (cap_ls.find(arguments[0]) != cap_ls.end())
		// 	(this->*_commands[toUpper(arguments[0])])(fd, arguments);
		// else
		// 	ft_write(fd, ERR_UNKNOWNCOMMAND(_clients[fd]->getNickName(), commandName));
	}

	// while (this->buffer.find("\r\n"))
	// {
	// 	buffer.clear();
	// 	char buff[BUFFER_SIZE];
	// 	memset(buff, 0, BUFFER_SIZE); /* Cleaning up memory */
	// 	int bytes_received = recv(fd, buff, BUFFER_SIZE, 0);
	// 	if(buff[0] > 31)
	// 		std::cout << "Received message: *" << buff << "* from fd: *" << fd << "*" << std::endl;
	// 	if (bytes_received < 0)
	// 	{
	// 		std::cerr << "Receive ended" << std::endl;
	// 		return ;
	// 	}
	// 	buffer = std::string(buff);
	// 	unsigned int i = 0;
	// 	while (i < buffer.size())
	// 	{
	// 		std::string command = "";
	// 		std::string args = "";
	// 		while (i < buffer.size() && (buffer[i] != ' ' && buffer[i] != '\r' && buffer[i] != '\n'))
	// 			command += buffer[i++]; //first ->command
	// 		while (i < buffer.size() && (buffer[i] == ' ' || buffer[i] == '\r' || buffer[i] == '\n'))
	// 			i++;
	// 		while (i < buffer.size())
	// 			args += buffer[i++];
	// 		executable(command, args, fd);
	// 		buffer.erase(0, i);
	// 	}
	// 	std::cout<<"IN WHILE EXECUTE COMMAND FD: *"<<fd<<"*"<<std::endl;
	// }
	// std::cout<<"EXECUTE COMMAND FD: *"<<fd<<"*"<<std::endl;
}

void	Server::executable(std::string command, std::string args, int fd)
{
	std::cout << "commmand: *" << command << "*" << std::endl;
	std::cout << "args: *" << args << "*" << std::endl;

	// std::transform(command.begin(), command.end(), command.begin(), ::toupper);
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
