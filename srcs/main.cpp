/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasinsensoy <yasinsensoy@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 22:16:34 by yasinsensoy       #+#    #+#             */
/*   Updated: 2023/04/23 22:16:35 by yasinsensoy      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Server.hpp"

int main(int argc, char **argv)
{
	Server server = Server(argc, argv);

	server.loop();
	shutdown(server.server_fd, SHUT_RDWR);
	return (0);
}
