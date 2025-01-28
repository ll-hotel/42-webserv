/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 18:40:52 by gcros             #+#    #+#             */
/*   Updated: 2025/01/28 18:44:26 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv/SocketListener.hpp"
#include "webserv/Config.hpp"
#include "webserv/Exception.hpp"
#include "webserv/HttpRequest.hpp"
#include "webserv/HttpResponse.hpp"
#include "webserv/Webserv.hpp"
#include <iostream>
#include <vector>
#include <poll.h>
#include <map>

int main(int ac, char **av)
{
	// Config conf;

	// try {
	// 	conf = Config("webserv.conf");
	// } catch (WebservException &e) {
	// 	e.print();
	// 	return 1;
	// }

	// std::cout << "Configuration:\n\n";
	// for (size_t i = 0; i < conf.getServers().size(); i += 1) {
	// 	const Config::Server &srv = conf.getServers()[i];

	// 	if (srv.getServerNames().size() == 0)
	// 		std::cout << "<anonymous server> ";
	// 	for (size_t i = 0; i < srv.getServerNames().size(); i += 1)
	// 		std::cout << srv.getServerNames()[i] << ' ';
	// 	std::cout << "{";
	// 	std::cout << "\n\thost: " << srv.getHost();
	// 	std::cout << "\n\tport: " << srv.getPort();
	// 	std::cout << "\n}" << std::endl;
	// }
	if (ac > 2)
	{
		std::cout << "to many args" << std::endl;
		return 1;
	}
	std::string	file_path = "webserv.conf";
	if (ac == 2)
		file_path = av[1];
	try
	{
		Webserv webserv(file_path);


		// std::vector<SocketListener*> listeners;
		// for (size_t i = 0; i < conf.getServers().size(); i += 1) {
		// 	const Config::Server &server = conf.getServers()[i];
		// 	try {
		// 		listeners.push_back(new SocketListener(server.getPort()));
		// 	} catch (WebservException &e) {
		// 		e.print();
		// 	}
		// }
		std::vector<struct pollfd>	fds;
		std::map<int, SocketListener*>	listener_map;
		for (size_t i = 0; i < webserv.getlisteners().size(); i++)
		{
			struct pollfd	fd = {0};
			fd.events = POLLIN;
			fd.fd = webserv.getlisteners()[i]->getFd();
			fds.push_back(fd);
			listener_map[fd.fd] = webserv.getlisteners()[i];
		}
		while (webserv.getlisteners().size() > 0)
		{
			std::cout << "polling" << std::endl;
			int nbr_action = poll(fds.data(), fds.size(), -1);
			if (nbr_action < 0)
				throw WebservException("poll: fail");
			int	socket_count = 0;
			for (int nbr_action_count = 0; nbr_action_count < nbr_action; nbr_action_count++)
			{
				for ((void)socket_count; socket_count < fds.size(); socket_count++)
					if (fds[socket_count].revents != 0)
						break ;
				SocketListener *socket_action = listener_map[fds[socket_count].fd];
				if (socket_action == NULL)
					throw WebservException("socketListener not found");
				ClientSocket client = socket_action->accept();
				std::string request = client.recv();
				std::cout << "--- Request ---\n" << request << std::endl;

				try {
					HttpRequest http_req(request);
					HttpResponse http_response(http_req);

					std::string response = http_response.generate();
					std::cout << "--- Response ---\n" << response << std::endl;

					client.send(response);
				} catch (WebservException &e) {
					e.print();
				}
				socket_count++;
			}
		}
	}
	catch(WebservException &e)
	{
		e.print();
	}
	return 0;
}
