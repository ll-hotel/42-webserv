/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:54:36 by gcros             #+#    #+#             */
/*   Updated: 2025/01/15 17:39:41 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPREQUEST_HPP
# define HTTPREQUEST_HPP
# include <string>

class HttpRequest
{
private:
	std::string	_method;
	std::string	_resources;
	std::string	_version;
	std::string	_request;
public:
	HttpRequest();
	HttpRequest(const HttpRequest&);
	HttpRequest(const std::string &request);
	HttpRequest& operator=(const HttpRequest&);

	const std::string& method() const { return _method; }
	const std::string& resources() const { return _resources; }
	const std::string& version() const { return _version; }
	const std::string& request() const { return _request; }

	/* For debug purposes only */
	void print();
};

#endif
