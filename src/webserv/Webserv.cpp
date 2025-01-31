/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:46:44 by gcros             #+#    #+#             */
/*   Updated: 2025/01/31 17:47:14 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exception>
#include <vector>
#include <poll.h>
#include <map>

#include "webserv/Webserv.hpp"
#include "webserv/Config.hpp"


Webserv::Webserv(const std::string &file_name):
_config(file_name)
{
	try
	{
		std::vector<Config::Server>::const_iterator it_end = _config.getServers().end();
		std::vector<Config::Server>::const_iterator it_inc = _config.getServers().begin();

		for (;it_inc != it_end; it_inc++)
		{
			_listeners.push_back(new SocketListener(it_inc->getPort()));
		}
	}
	catch(...)
	{
		std::vector<SocketListener*>::const_iterator it_end = _listeners.end();
		std::vector<SocketListener*>::iterator it_inc = _listeners.begin();
		for (;it_inc != it_end; it_inc++)
			delete *it_inc;
		_listeners.clear();
		throw;
	}
}

const Config &Webserv::getConfig() const
{
	return (this->_config);
}

const std::vector<SocketListener *> &Webserv::getlisteners() const
{
	return (this->_listeners);
}

const std::queue<ClientSocket *> &Webserv::getClientList() const
{
	return (_clientsList);
}

static inline	void set_listener(Webserv &ws,
	std::vector<struct pollfd> &fds,
	std::map<int, SocketListener*> &listener_map)
{
	for (size_t i = 0; i < ws.getlisteners().size(); i++)
	{
		struct pollfd	fd = {0};
		fd.events = POLLIN;
		fd.fd = ws.getlisteners()[i]->getFd();
		fds.push_back(fd);
		listener_map[fd.fd] = ws.getlisteners()[i];
	}
}

void Webserv::acceptClient()
{
	std::vector<struct pollfd>	fds;
	std::map<int, SocketListener*>	listener_map;

	set_listener(*this, fds, listener_map);
	int nbr_action = poll(fds.data(), fds.size(), DEFAULT_POLL_TIMEOUT);
	if (nbr_action < 0)
		throw WebservException("poll: fail");
	int	socket_count = 0;
	for (int nbr_action_count = 0; nbr_action_count < nbr_action; nbr_action_count++)
	{
		for ((void)socket_count; socket_count < fds.size(); socket_count++)
			if (fds[socket_count].revents != 0)
				break ;
		SocketListener *socket_action = listener_map[fds[socket_count].fd];
		if (socket_action == NULL)
			throw WebservException("socketListener not found");
		try
		{
			ClientSocket *client = socket_action->accept();
			_clientsList.push(client);
		}
		catch(WebservException e)
		{
			e.print();
		}
		socket_count++;
	}
}

Webserv::~Webserv()
{
	std::vector<SocketListener*>::const_iterator it_end = _listeners.end();
	std::vector<SocketListener*>::iterator it_inc = _listeners.begin();
	for (;it_inc != it_end; it_inc++)
		delete *it_inc;
	while (_clientsList.size() != 0)
	{
		ClientSocket *client = _clientsList.front();
		delete client;
		_clientsList.pop();
	}
	_listeners.clear();
}

/******************************************************************************/
/*                                     unused                                 */
/******************************************************************************/


Webserv Webserv::operator=(const Webserv &)
{
	return (*this);
}

Webserv::Webserv() : _config()
{
}

Webserv::Webserv(const Webserv &) : _config()
{
}

