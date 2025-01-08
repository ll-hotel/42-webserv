/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketListener.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 18:22:26 by gcros             #+#    #+#             */
/*   Updated: 2025/01/08 19:35:33 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv/SocketListener.hpp"
#include <string>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
#include <cstring>

SocketListener SocketListener::generate(int port)
{
	SocketListener	socket(port);

	if (socket.create())
		throw(WebservException(std::string("socket create fail: ") + strerror(errno)));
	if (socket.bind())
		throw(WebservException(std::string("socket bind fail: ") + strerror(errno)));
	if (socket.listen())
		throw(WebservException(std::string("socket listen fail: ") + strerror(errno)));
	return socket;
}

SocketListener::SocketListener()
{
	_close = true;
	_fail = false;
	_bind = false;
	_create = false;
	_listen = false;
	_port = DEFAULT_PORT;
	_fd = -1;
	_limit_queue = DEFAULT_LIMIT_QUEUE;
}

SocketListener::SocketListener(int port):
_port(port)
{
	_close = true;
	_fail = false;
	_bind = false;
	_create = false;
	_listen = false;
	_fd = -1;
	_limit_queue = DEFAULT_LIMIT_QUEUE;
}

SocketListener::~SocketListener()
{
	this->close();
}

int SocketListener::create()
{
	if (this->_fail)
		return (1);
	if (this->_create)
		return (1);
	int serverSocket = ::socket(DEFAULT_FAMILY, DEFAULT_STREAM, 0);
	if (serverSocket == -1)
	{
		this->_fail = true;
		return (1);
	}
	this->_fd = serverSocket;
	this->_create = true;
	return (0);
}

int SocketListener::bind()
{
	if (this->_fail)
		return (1);
	if (not this->_create)
		return (1);
	if (not this->_close)
		return (1);
	sockaddr_in serverAddress;
	serverAddress.sin_family = DEFAULT_FAMILY;
	serverAddress.sin_port = htons(this->_port);
	serverAddress.sin_addr.s_addr = DEFAULT_ADDR;

	if (::bind(this->_fd,
		(struct sockaddr*)&serverAddress, 
		sizeof(serverAddress)))
	{
		this->_fail = true;
		this->close();
		return (1);
	}
	this->_bind = true;
	return (0);
}

int SocketListener::listen()
{
	if (this->_fail)
		return (1);
	if (not this->_bind)
		return (1);
	if (::listen(this->_fd, this->_limit_queue))
	{
		this->_fail = true;
		this->close();
		return (1);
	}
	this->_listen = true;
	return (0);
}

int SocketListener::accept()
{
	struct sockaddr	client;
	socklen_t	client_len = sizeof(client);
	int		client_fd = -1;
	
	client_fd = ::accept(this->_fd, &client, &client_len);
	if (client_fd == -1)
		throw (WebservException(std::string("socket accept: ") + strerror(errno)));
	std::cout << "connection from " << client.sa_data << std::endl;
	return (0);
}

int SocketListener::close()
{
	if (this->_close)
		return (1);
	::close(this->_fd);
	this->_fd = -1;
	this->_close = true;
	return (0);
}
