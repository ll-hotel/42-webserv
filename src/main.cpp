/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 18:40:52 by gcros             #+#    #+#             */
/*   Updated: 2024/12/16 05:12:02 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv/Config.hpp"
#include "webserv/Exception.hpp"
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
	for (size_t i = 0; i < conf.getServerConfigs().size(); i += 1) {
		const Config::Server &srv = conf.getServerConfigs()[i];

		if (srv.server_names().size() == 0)
			std::cout << "<anonymous server> ";
		for (size_t i = 0; i < srv.server_names().size(); i += 1)
			std::cout << srv.server_names()[i] << ' ';
		std::cout << "{";
		std::cout << "\n\thost: " << srv.host();
		std::cout << "\n\tport: " << srv.port();
		std::cout << "\n}" << std::endl;
	}
	return 0;
}
