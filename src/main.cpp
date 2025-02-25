/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 18:40:52 by gcros             #+#    #+#             */
/*   Updated: 2025/02/25 17:03:51 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv/Exception.hpp"
#include "webserv/Webserv.hpp"
#include <iostream>
#include <vector>
#include <map>

int main(int ac, char **av)
{
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

		while (1)
		{
			webserv.acceptClients();
			std::cout << webserv.getClientList().size() << std::endl;
			webserv.resolveClients();
		}
	}
	catch(WebservException &e)
	{
		e.print();
	}
	return 0;
}
