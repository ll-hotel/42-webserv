/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketListener.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 18:22:26 by gcros             #+#    #+#             */
/*   Updated: 2025/01/08 20:52:20 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv/SocketListener.hpp"
#include "webserv/Exception.hpp"
#include <cstring>
#include <errno.h>
#include <netinet/in.h>
#include <string>
#include <unistd.h>

SocketListener::SocketListener(int port)
{
	create();
	bind(port);
	listen();
}

SocketListener::SocketListener()
{
	create();
	bind(DEFAULT_PORT);
	listen();
}

SocketListener::~SocketListener()
{
	close(_fd);
}

void SocketListener::create()
{
	_failed = false;
	_limit_queue = DEFAULT_LIMIT_QUEUE;
	_fd = socket(DEFAULT_FAMILY, DEFAULT_STREAM, 0);
	if (_fd == -1)
		throw(WebservException(std::string("socket create fail: ") + strerror(errno)));
}

void SocketListener::bind(int port)
{
	sockaddr_in address = {
		.sin_family = DEFAULT_FAMILY,
		.sin_port = htons(port),
		.sin_addr = {.s_addr = DEFAULT_ADDR},
	};
	_port = port;
	if (::bind(_fd, (struct sockaddr *)&address, sizeof(address)))
		throw(WebservException(std::string("socket bind fail: ") + strerror(errno)));
}

void SocketListener::listen()
{
	if (::listen(_fd, _limit_queue))
		throw(WebservException(std::string("socket listen fail: ") + strerror(errno)));
}

int SocketListener::accept()
{
	struct sockaddr	client;
	socklen_t	client_len = sizeof(client);
	int		client_fd = -1;
	
	client_fd = ::accept(_fd, &client, &client_len);
	if (client_fd == -1)
		throw (WebservException(std::string("socket accept: ") + strerror(errno)));
	std::cerr << "connection on port " << _port << std::endl;
	return (0);
}

bool SocketListener::has_failed() const
{
    return _failed;
}

// TODO
bool SocketListener::poll() const
{
    return true;
}
