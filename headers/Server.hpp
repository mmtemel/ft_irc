#ifndef SERVER_HPP
# define SERVER_HPP

#include <sstream>
#include <cstring>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h> /* for struct sockaddr_in */
#include <unistd.h>
#include <fcntl.h>
#include <netdb.h> /* struct hostent *server */
#include <sys/poll.h>
#include <map>
#include <netinet/tcp.h>
#include "Client.hpp"
#include "Channel.hpp"
#include <cstdlib>
#include <algorithm>

#define PORT 8080
#define BUFFER_SIZE 1024
#define MAX_USR 100

class Channel;
class Client;

class Server
{
	private:
		int my_port;
		int is_nick_first;
		std::string my_password;
	public:
		int					new_socket;
		int					server_fd;
		struct sockaddr_in	address;
		std::string			temp_nick;
		int					user_count;

		std::map<int, std::string> pass_fd;
		std::map<int, std::string> cap_ls;
		std::vector<pollfd>	pollfds;
		std::vector<Client> clients_;
		std::vector<Channel> channels_;


		Server(int, char **);
		~Server();

		void	appointment(int argc, char **argv);
		void	socketOperations();
		void	socketOperations2(char **argv);
		void	executable(std::string, std::string, int);

		void	newClient();
		void	executeCommand(int fd);
		void	loop();

		/* Getter and setter */
		int	getmyport();
		std::string	getmypassword();

		void cap(std::string, int);
		void join(std::string, int);
		void quit(std::string, int);
		void ping(std::string, int);
		void privmsg(std::string, int);
		void pass(std::string, int);
		void kick(std::string, int);
		void mode(std::string, int);
		void kill(std::string, int);
		void bot(std::string, int);
		void user(std::string, int);

		void nick_change(std::string, int);
		void nick_first(std::string, std::string, int);

		int client_nick_check(std::string nickname);
		Client *client_ret(std::string nickname);
		Client *client_ret(int fd);

		int getNick_first() {return this->is_nick_first; };
		void setNick_first(int is) {this->is_nick_first = is; };
		int flag;
		unsigned int channel_ok;
};

#endif
