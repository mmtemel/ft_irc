#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "../headers/Server.hpp"
#include "../headers/Channel.hpp"

class Client
{
	private:
		int fd;
		int port;
		int status;

		std::string username;
		std::string nickname;
		std::string realname;
		std::string hostname;
		std::string servername;
		std::string password;
	public:
		Client(int fd, std::string username,std::string hostname, std::string servername, std::string realname, std::string nickname);
		Client() {};
		~Client();

		// Getter
		int getFd() const { return (this->fd); }
		int getPort() const { return (this->port); }
		int	getStatus() const { return (this->status); }
		std::string getUserName() const { return (this->username); }
		std::string getNickName() const { return (this->nickname); }
		std::string getReelName() const { return (this->realname); }
		std::string getHostName() const { return (this->hostname); }
		std::string getServername() const { return (this->servername); }
		std::string getPassword() const { return (this->password); }
		std::string getPrefixName();

		// Setter
		void setStatus(int status) {this->status = status; };
		void setUserName(std::string const &Username) { this->username = Username; }
		void setNickName(std::string const &Nickname) { this->nickname = Nickname; }
		void setRealName(std::string const &Realname) { this->realname = Realname; }
		void setHostName(std::string const &Hostname) { this->hostname = Hostname; }
		void setServername(std::string const &Servername) { this->servername = Servername; }
		void setPassword(std::string const &Password) { this->password = Password; }
};

#endif
