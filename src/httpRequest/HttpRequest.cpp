/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 20:08:58 by gcros             #+#    #+#             */
/*   Updated: 2025/01/23 16:30:32 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv/HttpRequest.hpp"
#include "webserv/Exception.hpp"
#include <iostream>
#include <sstream>
#include <string>

HttpRequest::HttpRequest() {}

HttpRequest::HttpRequest(const HttpRequest &rp)
        : _method(rp._method), _version(rp._version), _resource(rp._resource),
          _request(rp._request)
{
}

HttpRequest &HttpRequest::operator=(const HttpRequest &other)
{
        _method = other._method;
        _version = other._version;
        _resource = other._resource;
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
                throw(WebservException("unsupported request method " +
                                       _method));
        if (!stream_request)
                throw(WebservException("incomplete request"));
        std::getline(stream_request, _resource, ' ');
        if (!stream_request)
                throw(WebservException("incomplete request"));
        std::getline(stream_request, _version, '\n');
        if (_version != "HTTP/1.1\r")
                throw(WebservException("unsupported HTTP version " + _version));
        std::getline(stream_request, _request, '\0');
}

void HttpRequest::print()
{
        std::cout << this->_method << " " << this->_resource << " "
                  << this->_version << std::endl;
}
