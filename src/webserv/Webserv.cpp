/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:46:44 by gcros             #+#    #+#             */
/*   Updated: 2025/02/25 17:16:20 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv/Webserv.hpp"
#include "webserv/Exception.hpp"
#include <cstring>
#include <errno.h>
#include <exception>
#include <map>
#include <unistd.h>
#include <vector>

static inline void
generate_epoll_event(int fd, std::vector<SocketListener *> &listeners_list);
static inline void
generate_socketListeners(const std::vector<ServerConfig> server_list,
			 std::vector<SocketListener *> &listeners_list);

Webserv::Webserv(const std::string &file_name)
{
	m_serverConfig = parse_configs_from_file(file_name);
	generate_socketListeners(m_serverConfig, m_listeners);
	m_epollSize = m_listeners.size();
	m_epollFd = epoll_create(m_epollSize);
	if (m_epollFd < 0)
		throw(WebservException(std::string("epoll_create: ") +
				       strerror(errno)));
	generate_epoll_event(m_epollFd, m_listeners);
}

static inline void
generate_epoll_event(int fd, std::vector<SocketListener *> &listeners_list)
{
	for (size_t i = 0; i < listeners_list.size(); i++) {
		struct epoll_event nevent = {};
		nevent.events = EPOLLIN;
		nevent.data.fd = listeners_list[i]->getFd();
		if (epoll_ctl(fd, EPOLL_CTL_ADD, listeners_list[i]->getFd(),
			      &nevent) < 0)
			throw(WebservException(std::string("epoll_ctl") +
					       strerror(errno)));
	}
}

static inline void
generate_socketListeners(const std::vector<ServerConfig> server_list,
			 std::vector<SocketListener *> &listeners_list)
{
	std::vector<ServerConfig>::const_iterator it_end = server_list.end();
	std::vector<ServerConfig>::const_iterator it_inc = server_list.begin();

	for (; it_inc != it_end; it_inc++)
		listeners_list.push_back(new SocketListener(it_inc->port()));
}

const std::vector<ServerConfig> &Webserv::getServerConfig() const
{
	return (this->m_serverConfig);
}

const std::vector<SocketListener *> &Webserv::getListeners() const
{
	return (this->m_listeners);
}

const std::queue<struct s_client_handler> &Webserv::getClientList() const
{
	return (m_clientsList);
}

static inline std::map<int, SocketListener *> set_listener(Webserv &ws)
{
	std::map<int, SocketListener *> listener_map;
	for (size_t i = 0; i < ws.getListeners().size(); i++) {
		int fd = ws.getListeners()[i]->getFd();
		listener_map[fd] = ws.getListeners()[i];
	}
	return (listener_map);
}

void Webserv::acceptClients()
{
	std::map<int, SocketListener *> listener_map;
	struct epoll_event *epoll_events =
		new struct epoll_event[this->m_epollSize]();

	listener_map = set_listener(*this);
	int nbr_action = epoll_wait(m_epollFd, epoll_events, m_epollSize,
				    DEFAULT_POLL_TIMEOUT);
	if (nbr_action < 0) {
		delete[] epoll_events;
		throw WebservException(std::string("epoll_wait: ") +
				       strerror(errno));
	}
	for (int nbr_action_count = 0; nbr_action_count < nbr_action;
	     nbr_action_count++) {
		SocketListener *socket_action =
			listener_map[epoll_events[nbr_action_count].data.fd];
		if (socket_action == NULL) {
			delete[] epoll_events;
			throw WebservException("socketListener not found");
		}
		try {
			struct s_client_handler client_handle;
			client_handle.client = socket_action->accept();
			client_handle.eevents = epoll_events[nbr_action_count];
			m_clientsList.push(client_handle);
		} catch (WebservException e) {
			e.print();
		}
	}
	delete[] epoll_events;
}

void Webserv::resolveClients()
{
	for (size_t clients_count = this->m_clientsList.size(); clients_count;
	     clients_count--) {
		struct s_client_handler client = this->m_clientsList.front();
		this->m_clientsList.pop();
		std::cout << "Client on " << client.client->fd() << std::endl;
		this->m_clientsList.push(client);
	}
}
Webserv::~Webserv()
{
	std::vector<SocketListener *>::const_iterator it_end =
		m_listeners.end();
	std::vector<SocketListener *>::iterator it_inc = m_listeners.begin();
	for (; it_inc != it_end; it_inc++)
		delete *it_inc;
	while (m_clientsList.size() != 0) {
		ClientSocket *client = m_clientsList.front().client;
		delete client;
		m_clientsList.pop();
	}
	m_listeners.clear();
	close(m_epollFd);
}

/******************************************************************************/
/*                                     unused                                 */
/******************************************************************************/

Webserv Webserv::operator=(const Webserv &) { return (*this); }

Webserv::Webserv() {}

Webserv::Webserv(const Webserv &) {}
