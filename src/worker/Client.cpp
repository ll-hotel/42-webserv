/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 18:21:54 by gcros             #+#    #+#             */
/*   Updated: 2024/12/06 17:54:56 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>

Client::Client():
_fd(-1)
{
}

Client::Client(int fd):
_fd(fd)
{
}

Client::~Client()
{
	close(this->_fd);
}

int Client::send(std::string msg)
{
	ssize_t ret;

	if (this->_fd == -1)
		return (1);
	ret = ::send(this->_fd, msg.c_str(), msg.size(), 0);
	if (ret < 0)
		return (1);
	return 0;
}

int Client::getFd()
{
	return this->_fd;
}

Client::Client(const Client &client)
{
	this->_fd = client._fd;
}

Client &Client::operator=(const Client &client)
{
	this->_fd = client._fd;
	return (*this);
}
