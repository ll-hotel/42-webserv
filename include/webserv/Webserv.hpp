/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 22:14:17 by gcros             #+#    #+#             */
/*   Updated: 2025/01/31 17:46:16 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
# define WEBSERV_HPP

#include <string>
#include <queue>
#include "webserv/Config.hpp"
#include "webserv/SocketListener.hpp"

# define DEFAULT_POLL_TIMEOUT 500
class Webserv
{

public:
	Webserv(const std::string &file_name);
	const Config &getConfig() const;
	const std::vector<SocketListener *> &getlisteners() const;
	const std::queue<ClientSocket *>	&getClientList() const;
	void	acceptClient();
	~Webserv();
private:
	Webserv();
	Webserv(const Webserv &);
	Webserv operator=(const Webserv &);

	Config				_config;
	std::vector<SocketListener *>	_listeners;

	std::queue<ClientSocket *>	_clientsList;
};


#endif