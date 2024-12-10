/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 21:38:17 by gcros             #+#    #+#             */
/*   Updated: 2024/12/06 17:36:09 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Socket.hpp"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <cstdio>
#include <cerrno>

Socket::Socket():
_fd(-1), _port(80)
{
}

Socket::Socket(int port):
_fd(-1), _port(port)
{
}

Socket::~Socket()
{
	close(this->_fd);
}

Socket::Socket(const Socket &socket)
{
	this->_addrinfo = socket._addrinfo;
	this->_fd = socket._fd;
	this->_port = socket._port;
}

Socket &Socket::operator=(const Socket &socket)
{
	(void) socket;
	return (*this);
}

int Socket::create()
{
	struct sockaddr_in	server_addr;
	int			error;

	this->_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_fd == -1) {
		std::perror("socket fail");
		return (1);
	}
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(this->_port);

	error = bind(this->_fd,
		(struct sockaddr *)&server_addr,
		sizeof(server_addr));
	if (error < 0) {
		std::perror("bind fail");
		return (1);
	}
	error = listen(this->_fd, CLIENT_QUEUE);
	if (error < 0) {
		std::perror("listen fail");
		return (1);
	}
	return (0);
}

Client Socket::get_client()
{
	struct sockaddr_in	client_addr;
	socklen_t		sock_len = sizeof(client_addr);
	int			client_fd;
	Client			ret;

	client_fd = accept(this->_fd,
		(struct sockaddr *)&client_addr,
		&sock_len);
	if (client_fd < 0) {
		std::perror("accept fail");
		return (-1);
	}
	ret = Client(client_fd);
	return (ret);
}
