/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config_Server.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 13:14:03 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/12/15 22:04:27 by ll-hotel         ###   ########.fr       */
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
	const std::string var = tok->value();

	if (tok->type() == BLOCK_END)
		return;
	++tok;
	if (tok->type() != WORD)
		throw(WebservException("missing value for " + var));
	if (var == "host") {
		_host = tok->value();
		++tok;
	} else if (var == "port") {
		if (!is_port(tok->value()))
			throw(WebservException("expected uint value for port"));
		_port = std::atoi(tok->value().c_str());
		++tok;
	} else if (var == "server_name") {
		while (tok->type() == WORD) {
			_server_names.push_back(tok->value());
			++tok;
		}
	} else {
		return;
	}
	if (tok->type() != ARG_END)
		throw(WebservException("too many values for " + var));
}

Config::Server::Server(ConfigToken::Vector::const_iterator &tok)
{
	*this = Server();

	if (tok->value() != "server")
		THROW_UNEXPECTED(tok->value());
	++tok;
	if (tok->type() != BLOCK_START)
		THROW_UNEXPECTED(tok->value());
	do {
		++tok;
		__use_token(tok);
	} while (tok->type() != BLOCK_END);
}

Config::Server& Config::Server::operator=(const Server &other) throw()
{
	_port = other._port;
	_host = other._host;
	_server_names = other._server_names;
	return *this;
}

const std::string& Config::Server::host() const
{
	return _host;
}

uint16_t Config::Server::port() const
{
	return _port;
}

const std::vector<std::string>& Config::Server::server_names() const
{
	return _server_names;
}
