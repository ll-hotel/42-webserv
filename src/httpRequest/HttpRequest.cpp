/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 20:08:58 by gcros             #+#    #+#             */
/*   Updated: 2025/01/08 21:20:12 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv/HttpRequest.hpp"
#include "webserv/Exception.hpp"
#include <string>
#include <sstream>
#include <iostream>

HttpRequest::HttpRequest()
{
	_type = "";
	_version = "";
	_resources = "";
	_request = "";
}

HttpRequest::HttpRequest(const HttpRequest &rp)
{
	_type = rp._type;
	_version = rp._version;
	_request = rp._request;
}

HttpRequest::HttpRequest(std::string request)
{
	std::istringstream	stream_request(request);
	if (request.empty())
		throw(WebservException("empty request"));
	if (!stream_request)
		throw(WebservException("empty request"));
	std::string	word;
	std::getline(stream_request, word, ' ');
	if (word != "GET" && word != "POST")
		throw(WebservException("unsuported request " + word));
	this->_type = word;
	if (!stream_request)
		throw(WebservException("incomplete request"));
	std::getline(stream_request, word, ' ');
	this->_resources = word;
	if (!stream_request)
		throw(WebservException("incomplete request"));
	std::getline(stream_request, word);
	if (word != "HTTP/1.1\r")
		throw(WebservException("unsuported Protocol " + word));
	this->_version = word;
	if (std::getline(stream_request, word, '\0'))
		this->_request = word;
}

void HttpRequest::print()
{
	std::cout << this->_type
		<< " " << this->_resources
		<< " " << this->_version
		<< std::endl;
}
