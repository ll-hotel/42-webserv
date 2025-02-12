/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:46:44 by gcros             #+#    #+#             */
/*   Updated: 2025/02/13 00:44:04 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exception>
#include <vector>
#include <map>
#include <cstring>
#include <unistd.h>
#include <errno.h>

#include "webserv/Webserv.hpp"
#include "webserv/Config.hpp"

static inline	void	generate_socketListeners(Config &config,
		std::vector<SocketListener*> &listeners_list);
static inline	void	generate_epoll_event(int fd,
		std::vector<SocketListener*> &listeners_list);

Webserv::Webserv(const std::string &file_name):
_config(file_name)
{
	generate_socketListeners(_config, _listeners);
	_epollSize = _listeners.size();
	_epollFd = epoll_create(_epollSize);
	if (_epollFd < 0)
		throw (WebservException(std::string("epoll_create: ") + strerror(errno)));
	generate_epoll_event(_epollFd, _listeners);
}

static inline	void	generate_epoll_event(int fd, std::vector<SocketListener*> &listeners_list)
{
	for (int i = 0; i < listeners_list.size(); i++)
	{
		struct epoll_event	nevent = {0};
		nevent.events = EPOLLIN;
		nevent.data.fd = listeners_list[i]->getFd();
		if (epoll_ctl(fd, EPOLL_CTL_ADD, listeners_list[i]->getFd(), &nevent) < 0)
			throw (WebservException(std::string("epoll_ctl") + strerror(errno)));
	}
}

static inline	void	generate_socketListeners(Config &config,
		std::vector<SocketListener*> &listeners_list)
{
	std::vector<Config::Server>::const_iterator it_end = config.getServers().end();
	std::vector<Config::Server>::const_iterator it_inc = config.getServers().begin();

	for (;it_inc != it_end; it_inc++)
		listeners_list.push_back(new SocketListener(it_inc->getPort()));
}

const Config &Webserv::getConfig() const
{
	return (this->_config);
}

const std::vector<SocketListener *> &Webserv::getlisteners() const
{
	return (this->_listeners);
}

const std::queue<struct s_client_handler> &Webserv::getClientList() const
{
	return (_clientsList);
}

static inline	std::map<int, SocketListener*> set_listener(Webserv &ws)
{
	std::map<int, SocketListener*> listener_map;
	for (size_t i = 0; i < ws.getlisteners().size(); i++)
	{
		int fd = ws.getlisteners()[i]->getFd();
		listener_map[fd] = ws.getlisteners()[i];
	}
	return (listener_map);
}

void Webserv::acceptClients()
{
	std::map<int, SocketListener *>	listener_map;
	struct epoll_event		*epoll_events = new struct epoll_event[this->_epollSize]();
	
	listener_map = set_listener(*this);
	int nbr_action = epoll_wait(_epollFd, epoll_events, _epollSize, DEFAULT_POLL_TIMEOUT);
	if (nbr_action < 0)
	{
		delete[] epoll_events;
		throw WebservException(std::string("epoll_wait: ") + strerror(errno));
	}
	for (int nbr_action_count = 0; nbr_action_count < nbr_action; nbr_action_count++)
	{
		SocketListener *socket_action = listener_map[epoll_events[nbr_action_count].data.fd];
		if (socket_action == NULL)
		{
			delete[] epoll_events;
			throw WebservException("socketListener not found");
		}
		try
		{
			struct s_client_handler client_handle;
			client_handle.client = socket_action->accept();
			client_handle.eevents = epoll_events[nbr_action_count];
			_clientsList.push(client_handle);
		}
		catch(WebservException e)
		{
			e.print();
		}
	}
	delete[] epoll_events;
}

void Webserv::resolveClients()
{
	for (size_t clients_count = this->_clientsList.size(); clients_count ;clients_count--)
	{
		struct s_client_handler client = this->_clientsList.front();
		this->_clientsList.pop();
		std::cout << "Client on " << client.client->fd() << std::endl;
		this->_clientsList.push(client);
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
		ClientSocket *client = _clientsList.front().client;
		delete client;
		_clientsList.pop();
	}
	_listeners.clear();
	close(_epollFd);
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

