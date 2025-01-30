/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:20:06 by ll-hotel          #+#    #+#             */
/*   Updated: 2025/01/28 18:54:45 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv/Config.hpp"
#include "Token.hpp"

Config::Config()
{
}

Config::Config()
{
	_do_directory_listing = false;
	_do_post = false;
	_do_get = false;
	_do_upload = false;
}

Config::Config(const Config &other)
{
	*this = other;
}

Config& Config::operator=(const Config &other)
{
	_host = other._host;
	_root = other._root;
	_index = other._index;
	_error_pages = other._error_pages;
	_locations = other._locations;
	_allowed_cgi = other._allowed_cgi;
	_body_size = other._body_size;
	_port = other._port;
	_do_directory_listing = other._do_directory_listing;
	_do_post = other._do_post;
	_do_get = other._do_get;
	_do_upload = other._do_upload;
	_upload_dir = other._upload_dir;
	return *this;
}
