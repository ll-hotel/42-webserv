/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:08:44 by gcros             #+#    #+#             */
/*   Updated: 2025/02/25 16:08:06 by gcros            ###   ########.fr       */
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
	bool	isSet() const {return m_isSet;}
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
	
	std::ofstream	m_outFile;
	bool		m_isSet;
};

std::ostream &operator<<(std::ostream &os, const Logger::s_log_object &log_object);

#endif