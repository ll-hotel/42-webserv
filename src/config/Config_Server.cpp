/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config_Server.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 13:14:03 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/12/16 05:33:24 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <cstdlib>
#include "webserv/parsing.hpp"
#include "webserv/Config.hpp"

static bool is_port(const std::string &str)
{
	if (str.empty())
		return false;
	for (size_t i = 0; i < str.size(); i += 1) {
		if (!std::isdigit(str[i]))
			return false;
	}
	return true;
}

Config::Server::Server()
{
	_host = "localhost";
	_port = 80;
	_server_names.clear();
}

void Config::Server::__use_token(ConfigToken::Vector::const_iterator &tok)
{
	const std::string var = tok->getValue();

	if (tok->getType() == BLOCK_END)
		return;
	++tok;
	if (tok->getType() != WORD)
		throw(WebservException("missing value for " + var));
	if (var == "host") {
		_host = tok->getValue();
		++tok;
	} else if (var == "port") {
		if (!is_port(tok->getValue()))
			throw(WebservException("expected uint value for port"));
		_port = std::atoi(tok->getValue().c_str());
		++tok;
	} else if (var == "server_name") {
		while (tok->getType() == WORD) {
			_server_names.push_back(tok->getValue());
			++tok;
		}
	} else {
		return;
	}
	if (tok->getType() != ARG_END)
		throw(WebservException("too many values for " + var));
}

Config::Server::Server(ConfigToken::Vector::const_iterator &tok)
{
	*this = Server();

	if (tok->getValue() != "server")
		THROW_UNEXPECTED(tok->getValue());
	++tok;
	if (tok->getType() != BLOCK_START)
		THROW_UNEXPECTED(tok->getValue());
	do {
		++tok;
		__use_token(tok);
	} while (tok->getType() != BLOCK_END);
}

Config::Server& Config::Server::operator=(const Server &other) throw()
{
	_port = other._port;
	_host = other._host;
	_server_names = other._server_names;
	return *this;
}

const std::string& Config::Server::getHost() const
{
	return _host;
}

uint16_t Config::Server::getPort() const
{
	return _port;
}

const std::vector<std::string>& Config::Server::getServerNames() const
{
	return _server_names;
}
