/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:46:44 by gcros             #+#    #+#             */
/*   Updated: 2025/01/28 16:44:27 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv/Webserv.hpp"

#include <vector>
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

const std::vector<SocketListener *> &Webserv::getlisteners() const
{
	return (this->_listeners);
}

Webserv::~Webserv()
{
	std::vector<SocketListener*>::const_iterator it_end = _listeners.end();
	std::vector<SocketListener*>::iterator it_inc = _listeners.begin();
	for (;it_inc != it_end; it_inc++)
		delete *it_inc;
	_listeners.clear();
}
