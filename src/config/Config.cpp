/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 21:21:15 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/12/16 05:29:51 by ll-hotel         ###   ########.fr       */
/* ************************************************************************** */

#include "webserv/Config.hpp"
#include "webserv/parsing.hpp"
#include <cctype>
#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

extern std::string read_file(const std::string &file_path);
extern ConfigToken::Vector lexer(const std::string &content);

Config::Config() throw()
{
}

Config::Config(const std::string &file_path)
{
	const std::string content = read_file(file_path);
	const ConfigToken::Vector tokens = lexer(content);
	ConfigToken::Vector::const_iterator it;

	for (it = tokens.begin(); it != tokens.end(); ++it)
		_servers.push_back(Config::Server(it));
}

Config::Config(const Config &config) throw()
{
	*this = config;
}

Config& Config::operator=(const Config &other) throw()
{
	_servers = other._servers;
	_error_pages = other._error_pages;
	_max_client_body_size = other._max_client_body_size;
	return *this;
}

Config::~Config() throw()
{
}

const std::vector<Config::Server>& Config::getServers()
{
	return _servers;
}

const std::map<uint16_t, std::string>& Config::getErrorPages()
{
	return _error_pages;
}

size_t Config::getMaxClientBodySize()
{
	return _max_client_body_size;
}
