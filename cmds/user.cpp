/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtemel <mtemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 19:14:48 by mtemel            #+#    #+#             */
/*   Updated: 2023/05/16 19:35:24 by mtemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Server.hpp"
#include "../headers/Client.hpp"
#include "../headers/Channel.hpp"

void Server::user(std::string buffer, int fd)
{
	std::cout<<"USER BUFFER: *"<<buffer<<"*\n";
	std::vector<std::string> my_vec;
	unsigned int i = 0;
	while (buffer.size() > i)
	{
		std::string command = "";
		while (i < buffer.size() && (buffer[i] != ' ' && buffer[i] != '\r' && buffer[i] != '\n'))
			command += buffer[i++];
		while (i < buffer.size() && (buffer[i] == ' ' || buffer[i] == '\r' || buffer[i] == '\n'))
			i++;
		my_vec.push_back(command);
	}
	if (my_vec.size() > 3)
	{
			Client c(fd,my_vec[0],my_vec[1],my_vec[2],my_vec[3],this->temp_nick);
			this->clients_.push_back(c);
			std::cout<<"\033[1;92mNEW USER CREATED AND ADDED TO THE VEC!\033[0m\n";
	}
	else
		std::cout<<"USER: NOT ENOUGH ARG!\n";
	my_vec.clear();
	std::vector<Client>::iterator ite = this->clients_.end();
	for(std::vector<Client>::iterator it = this->clients_.begin(); it != ite; it++)
	{
		std::cout<<"class_attr:"<<(*it).getFd()<<","<<(*it).getUserName()<<","<<(*it).getHostName()<<",";
		std::cout<<(*it).getServername()<<","<<(*it).getReelName()<<","<<(*it).getNickName()<<","<<std::endl;
	}
	std::cout<<"USER sonu geldi"<<std::endl;
}