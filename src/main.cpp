/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 18:40:52 by gcros             #+#    #+#             */
/*   Updated: 2025/01/08 20:51:25 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv/Config.hpp"
#include "webserv/Exception.hpp"
#include "webserv/SocketListener.hpp"
#include <iostream>
#include <vector>

int main(void)
{
	Config conf;

	try {
		conf = Config("webserv.conf");
	} catch (WebservException &e) {
		e.print();
		return 1;
	}

	std::cout << "Configuration:\n\n";
	for (size_t i = 0; i < conf.getServers().size(); i += 1) {
		const Config::Server &srv = conf.getServers()[i];

		if (srv.getServerNames().size() == 0)
			std::cout << "<anonymous server> ";
		for (size_t i = 0; i < srv.getServerNames().size(); i += 1)
			std::cout << srv.getServerNames()[i] << ' ';
		std::cout << "{";
		std::cout << "\n\thost: " << srv.getHost();
		std::cout << "\n\tport: " << srv.getPort();
		std::cout << "\n}" << std::endl;
	}


	std::vector<SocketListener*> listeners;
	for (size_t i = 0; i < conf.getServers().size(); i += 1) {
		const Config::Server &server = conf.getServers()[i];
		try {
			listeners.push_back(new SocketListener(server.getPort()));
		} catch (WebservException &e) {
			e.print();
		}
	}
	while (listeners.size()) {
		listeners.back()->accept();
		delete listeners.back();
		listeners.pop_back();
	}
	return 0;
}
