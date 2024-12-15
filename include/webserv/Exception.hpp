/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exception.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 21:00:43 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/12/15 22:08:39 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_EXCEPTION_HPP
#define WEBSERV_EXCEPTION_HPP
#include <exception>
#include <iostream>
#include <string>
#define WS_THROW(error) throw(WebservException(error))

class WebservException : public std::exception {
private:
	const std::string _str;
public:
	WebservException(const std::string &str):
		_str("webserv: error: " + str)
	{}
	virtual ~WebservException() throw()
	{};
	virtual const char *what() const throw()
	{
		return _str.c_str();
	}
	virtual void print() const throw()
	{
		std::cerr << what() << std::endl;
	}
};

#endif
