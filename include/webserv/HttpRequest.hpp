/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:54:36 by gcros             #+#    #+#             */
/*   Updated: 2025/01/23 16:29:21 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPREQUEST_HPP
#define HTTPREQUEST_HPP
#include <string>

class HttpRequest
{
private:
        std::string _method;
        std::string _resource;
        std::string _version;
        std::string _request;

public:
        HttpRequest();
        HttpRequest(const HttpRequest &);
        HttpRequest(const std::string &request);
        HttpRequest &operator=(const HttpRequest &);

        const std::string &method() const { return _method; }
        const std::string &resource() const { return _resource; }
        const std::string &version() const { return _version; }
        const std::string &request() const { return _request; }

        /* For debug purposes only */
        void print();
};

#endif
