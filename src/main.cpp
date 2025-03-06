/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 18:40:52 by gcros             #+#    #+#             */
/*   Updated: 2025/03/06 16:28:18 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv/Exception.hpp"
#include "webserv/Logger.hpp"
#include "webserv/Webserv.hpp"

int main(int ac, char **av)
{
	Logger::GetInstance().message(Logger::INIT, "--start--");
	if (ac > 2) {
		Logger::GetInstance().message(Logger::ERROR, "to many args");
		return 1;
	}
	std::string file_path = "webserv.conf";
	if (ac == 2)
		file_path = av[1];
	try {
		Webserv webserv(file_path);

		while (true) {
			webserv.acceptClients();
			webserv.resolveClients();
		}
	} catch (WebservException &e) {
		e.print();
	}
	return 0;
}
