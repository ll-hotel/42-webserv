/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exception.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 21:00:43 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/12/11 22:00:45 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_EXCEPTION_HPP
#define WEBSERV_EXCEPTION_HPP
#include <exception>
#include <iostream>
#include <string>

class WebservException : public std::exception {
private:
	const std::string _str;
public:
	WebservException(const std::string &str):
		_str("webserv: exception: " + str)
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
