/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:08:44 by gcros             #+#    #+#             */
/*   Updated: 2025/02/25 15:05:25 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGGER_HPP
# define LOGGER_HPP

#include <string>
#include <ctime>
#include <queue>
#include <fstream>
#include "webserv/Exception.hpp"

class Logger
{
public:
	Logger();
	Logger(const std::string&);
	~Logger();
	
	enum e_log_level
	{
		INFO,
		DEBUG,
		WARN,
		ERROR,
		LOG_LEVEL_LEN,
	};
	
	void	log(Logger::e_log_level level, const std::string& message);
	bool	isSet() const {return _isSet;}
	void	open(const std::string &);
	void	open();
	void	close();
	
	struct s_log_object
	{
		char			str_time[20];
		std::string		message;
		enum e_log_level	type;
	};
	
	private:
	Logger& operator=(Logger&);
	Logger(Logger&);
	void	openOutFile(const std::string&);
	
	std::ofstream	_outFile;
	bool		_isSet;
};

std::ostream &operator<<(std::ostream &os, const Logger::s_log_object &log_object);

#endif