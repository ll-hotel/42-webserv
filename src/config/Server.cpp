/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:52:00 by ll-hotel          #+#    #+#             */
/*   Updated: 2025/01/28 17:54:17 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv/Server.hpp"

Server::Server()
{
}

Server::Server(std::ifstream &file):
	_config(file)
{
}

Server::Server(const Server &other)
{
	*this = other;
}

Server& Server::operator=(const Server &other)
{
	_config = other.configuration();
	return *this;
}

Server::~Server()
{
}

const Config& Server::configuration() const
{
	return _config;
}
