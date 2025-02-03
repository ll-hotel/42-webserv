/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 22:14:17 by gcros             #+#    #+#             */
/*   Updated: 2025/02/04 00:27:21 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
# define WEBSERV_HPP

#include <string>
#include <queue>
#include <sys/epoll.h>

#include "webserv/Config.hpp"
#include "webserv/SocketListener.hpp"

# define DEFAULT_POLL_TIMEOUT 500

struct s_client_handler
{
	ClientSocket	*client;
	struct epoll_event	eevents;
};

class Webserv
{

public:
	Webserv(const std::string &file_name);
	const Config &getConfig() const;
	const std::vector<SocketListener *> &getlisteners() const;
	const std::queue<struct s_client_handler>	&getClientList() const;
	void	acceptClients();
	void	resolveClients();
	~Webserv();
private:
	Webserv();
	Webserv(const Webserv &);
	Webserv operator=(const Webserv &);

	Config					_config;
	std::vector<SocketListener *>		_listeners;
	int					_epollFd;
	size_t					_epollSize;
	std::queue<struct s_client_handler>	_clientsList;
};


#endif