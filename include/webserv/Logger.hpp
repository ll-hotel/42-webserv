/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:08:44 by gcros             #+#    #+#             */
/*   Updated: 2025/02/25 12:21:19 by gcros            ###   ########.fr       */
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
	void	flush();
	
	struct s_log_object
	{
		char			str_time[20];
		std::string		message;
		enum e_log_level	type;
	};

private:
	std::queue<struct s_log_object> _messageQueue;
	Logger(Logger&);
	void	openOutFile(const std::string&);
	Logger& operator=(Logger&);

	std::ofstream	_outFile;
};

std::ostream &operator<<(std::ostream &os, const Logger::s_log_object &log_object);

#endif