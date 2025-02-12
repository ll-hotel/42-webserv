/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 18:40:52 by gcros             #+#    #+#             */
/*   Updated: 2025/02/08 12:59:06 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv/Exception.hpp"
#include "webserv/ServerConfig.hpp"
#include <vector>

int main(void)
{
	std::vector<ServerConfig> configs;

	try {
		configs = parse_configs_from_file("webserv.conf");
	} catch (WebservException &e) {
		e.print();
		return 1;
	}
	for (size_t i = 0; i < configs.size(); i += 1)
		std::cout << configs[i] << std::endl;
}
