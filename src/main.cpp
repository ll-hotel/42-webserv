/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 18:40:52 by gcros             #+#    #+#             */
/*   Updated: 2025/01/15 15:39:37 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv/Config.hpp"
#include "webserv/Exception.hpp"
#include "webserv/HttpResponse.hpp"
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

	HttpResponse response("index.html");

	std::string response_string = response.generate();
	std::cout << response_string << std::endl;
	return 0;
}
