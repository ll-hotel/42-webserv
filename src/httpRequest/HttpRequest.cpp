/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 20:08:58 by gcros             #+#    #+#             */
/*   Updated: 2025/01/15 12:17:32 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv/HttpRequest.hpp"
#include "webserv/Exception.hpp"
#include <string>
#include <sstream>
#include <iostream>

HttpRequest::HttpRequest()
{
}

HttpRequest::HttpRequest(const HttpRequest &rp)
{
	*this = rp;
}

HttpRequest& HttpRequest::operator=(const HttpRequest &other)
{
	_method = other._method;
	_version = other._version;
	_resources = other._resources;
	_request = other._request;
	return *this;
}

HttpRequest::HttpRequest(const std::string &request)
{
	std::istringstream stream_request(request);

	if (request.empty() || !stream_request)
		throw(WebservException("empty request"));
	std::getline(stream_request, _method, ' ');
	if (_method != "GET" && _method != "POST")
		throw(WebservException("unsupported request method " + _method));
	if (!stream_request)
		throw(WebservException("incomplete request"));
	std::getline(stream_request, _resources, ' ');
	if (!stream_request)
		throw(WebservException("incomplete request"));
	std::getline(stream_request, _version, '\n');
	if (_version != "HTTP/1.1\r")
		throw(WebservException("unsupported HTTP version " + _version));
	std::getline(stream_request, _request, '\0');
}

void HttpRequest::print()
{
	std::cout << this->_method
		<< " " << this->_resources
		<< " " << this->_version
		<< std::endl;
}
