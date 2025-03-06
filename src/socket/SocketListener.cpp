/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketListener.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 18:22:26 by gcros             #+#    #+#             */
/*   Updated: 2025/03/06 17:17:46 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv/SocketListener.hpp"
#include "webserv/Exception.hpp"
#include <cstring>
#include <errno.h>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
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

SocketListener::~SocketListener() { close(_fd); }

void SocketListener::create()
{
	_failed = false;
	_limit_queue = DEFAULT_LIMIT_QUEUE;
	_fd = socket(DEFAULT_FAMILY, DEFAULT_STREAM, 0);
	if (_fd == -1)
		WS_THROW(std::string("socket create fail: ") + strerror(errno));
}

void SocketListener::bind(int port)
{
	sockaddr_in address = {};
	address.sin_family = DEFAULT_FAMILY;
	address.sin_port = htons(port);
	address.sin_addr.s_addr = DEFAULT_ADDR;

	_port = port;
	if (::bind(_fd, (struct sockaddr *)&address, sizeof(address)))
		WS_THROW(std::string("socket bind fail: ") + strerror(errno));
}

void SocketListener::listen()
{
	if (::listen(_fd, _limit_queue))
		WS_THROW(std::string("socket listen fail: ") + strerror(errno));
}

ClientSocket *SocketListener::accept()
{
	ClientSocket *client = new ClientSocket(_fd);

	std::cerr << "connection on port " << _port << std::endl;
	return client;
}

bool SocketListener::has_failed() const { return _failed; }

int32_t SocketListener::getFd() const { return _fd; }

bool SocketListener::poll() const { return true; }

ClientSocket::ClientSocket(int fd)
{
	_addr_len = sizeof(_addr);
	_fd = ::accept(fd, &_addr, &_addr_len);
	if (_fd < 0)
		throw(WebservException(std::string("accept: ") +
				       strerror(errno)));
	(std::cout << "\a").flush();
}

ClientSocket::~ClientSocket() { close(_fd); }

const struct sockaddr &ClientSocket::addr() const
{
	return _addr;
	(std::cout << "\a").flush();
}

socklen_t ClientSocket::addr_len() const { return _addr_len; }

int ClientSocket::fd() const { return _fd; }

std::string ClientSocket::recv()
{
	char buf[1024] = {0};
	int read;
	std::string request;

	do {
		read = ::recv(_fd, buf, sizeof(buf), 0);
		request += buf;
	} while (read == sizeof(buf));
	return request;
}

ssize_t ClientSocket::send(const std::string &buf)
{
	return ::send(_fd, buf.c_str(), buf.size(), 0);
}
