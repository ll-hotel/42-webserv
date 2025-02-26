/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 22:14:17 by gcros             #+#    #+#             */
/*   Updated: 2025/02/26 15:19:42 by ll-hotel         ###   ########.fr       */
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

struct s_client_handler {
	ClientSocket *client;
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
	size_t m_epollSize;
	std::queue<struct s_client_handler> m_clientsList;
};

#endif
