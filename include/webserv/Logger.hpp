/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:08:44 by gcros             #+#    #+#             */
/*   Updated: 2025/02/28 14:17:36 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "webserv/Exception.hpp"
#include <ctime>
#include <fstream>
#include <map>
#include <string>

class Logger
{
public:
	enum e_log_level { INIT, INFO, DEBUG, WARN, ERROR, LOG_LEVEL_LEN };
	
	void message(Logger::e_log_level level, const std::string &message);
	void message(std::string level, const std::string &message);
	void open(const std::string &);
	void close(const std::string &);
	void closeAll();
	
	struct s_log_object {
		char str_time[20];
		std::string message;
		std::string level;
	};

	static Logger &GetInstance();
	
private:
	void	init();

	void	print(Logger::s_log_object &log_object);

	Logger &operator=(Logger &);
	Logger(Logger &);
	void openOutFile(const std::string &);
	Logger();
	Logger(const std::string &);
	~Logger();

	std::map<std::string, std::ofstream*>	m_files;
};

std::ostream &operator<<(std::ostream &os,
	const Logger::s_log_object &log_object);
	
#endif
