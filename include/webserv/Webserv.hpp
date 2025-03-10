/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 22:14:17 by gcros             #+#    #+#             */
/*   Updated: 2025/03/10 14:44:36 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#include <queue>
#include <string>
#include <sys/epoll.h>

#include "webserv/ServerConfig.hpp"
#include "webserv/SocketListener.hpp"

#define DEFAULT_POLL_TIMEOUT 500
#define DEFAULT_EPOLL_MAX_EVENT 20
#define DEFAULT_EPOLL_SIZE 100

struct s_client_handler {
	ClientSocket *socket;
	struct epoll_event eevents;
};

class Webserv
{

public:
	Webserv(const std::string &file_name);
	const std::vector<SocketListener *> &getListeners() const;
	const std::queue<struct s_client_handler> &getClientList() const;
	void acceptClients();
	void resolveClients();
	const std::vector<ServerConfig> &getServerConfig() const;
	~Webserv();

private:
	Webserv();
	Webserv(const Webserv &);
	Webserv operator=(const Webserv &);

	std::vector<ServerConfig> m_serverConfig;
	std::vector<SocketListener *> m_listeners;
	int m_epollFd;
	std::queue<struct s_client_handler> m_clientsList;
};

#endif
