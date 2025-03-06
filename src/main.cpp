/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 18:40:52 by gcros             #+#    #+#             */
/*   Updated: 2025/03/06 18:07:19 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv/Exception.hpp"
#include "webserv/Logger.hpp"
#include "webserv/Webserv.hpp"
#include <csignal>

static void sigint_handler(int)
{
	Logger::GetInstance().message(Logger::INFO, "Quitting...");
}

int main(int argc, const char *argv[])
{
	std::signal(SIGINT, sigint_handler);
	Logger::GetInstance().message(Logger::INIT, "--start--");
	if (argc > 2) {
		Logger::GetInstance().message(Logger::ERROR, "to many args");
		return 1;
	}
	std::string file_path = "webserv.conf";
	if (argc == 2)
		file_path = argv[1];
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
