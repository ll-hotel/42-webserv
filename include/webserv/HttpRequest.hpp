/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:54:36 by gcros             #+#    #+#             */
/*   Updated: 2025/01/08 21:04:43 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPREQUEST_HPP
# define HTTPREQUEST_HPP

#include <string>

class HttpRequest
{
private:
	std::string	_type;
	std::string	_version;
	std::string	_resources;
	std::string	_request;
public:
	HttpRequest();
	HttpRequest(const HttpRequest& rp);
	HttpRequest(std::string request);

	std::string	getType() const{return _type;}
	std::string	getVersion() const{return _version;}
	std::string	getRessources() const{return _resources;}
	std::string	getRequest() const{return _request;}
	
	void		print();
	
};

#endif