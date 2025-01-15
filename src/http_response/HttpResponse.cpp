/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpResponse.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:11:31 by ll-hotel          #+#    #+#             */
/*   Updated: 2025/01/15 16:41:43 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv/HttpResponse.hpp"
#include <fstream>
#include <sstream>
#include <string>

HttpResponse::HttpResponse()
{
	_status_code = SUCCESS_OK;
}

HttpResponse::HttpResponse(const std::string &resource)
{
	_status_code = SUCCESS_OK;
	_resource = resource;
}

HttpResponse::HttpResponse(const HttpResponse &other)
{
	_status_code = other._status_code;
	_resource = other._resource;
}

HttpResponse& HttpResponse::operator=(const HttpResponse &other)
{
	_status_code = other._status_code;
	_resource = other._resource;
	return *this;
}

HttpResponse::~HttpResponse()
{
}

static std::string read_file(const std::string &path)
{
	std::ifstream fstream(path.c_str());
	std::string content;

	if (fstream.is_open()) {
		std::getline(fstream, content, '\0');
	}
	return content;
}

std::string create_status_line(t_status_code code)
{
	std::string status_line = "HTTP/1.1";
	status_line += ' ';
	{
		std::stringstream strs;
		std::string str_code;
		strs << code;
		strs >> str_code;
		status_line += str_code;
	}
	status_line += status_table(code);
	status_line += "\r\n";
	return status_line;
}

std::string HttpResponse::generate()
{
	std::string str;

	// Status line
	str += create_status_line(_status_code);
	// Response headers
	str += "Server: webserv\r\n";
	// Representation headers
	str += "Content-Type: text/html\r\n";
	// Empty line
	str += "\r\n";
	// Response body
	str += read_file(_resource);
	return str;
}
