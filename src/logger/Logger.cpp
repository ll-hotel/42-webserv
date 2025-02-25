/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 09:59:48 by gcros             #+#    #+#             */
/*   Updated: 2025/02/25 17:48:23 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv/Logger.hpp"
#include <sstream>
#include <iostream>
#include <cstring>
#include <cerrno>

Logger::Logger()
{
	this->m_isSet = false;
}

Logger::Logger(const std::string &t_file_name)
{
	this->openOutFile(t_file_name);
	this->m_isSet = true;
}

Logger::~Logger()
{
	this->close();
}

void Logger::log(Logger::e_log_level t_level, const std::string &t_message)
{

	struct Logger::s_log_object log_object = {};
	time_t raw_time;
	tm* timeinfo;

	log_object.type = t_level;
	log_object.message = t_message;
	raw_time = time(0);
	timeinfo = localtime(&raw_time);
	strftime(log_object.str_time, 20, "%Y-%m-%d %H:%M:%S", timeinfo);
	std::cout << log_object;
	if (m_isSet)
		this->m_outFile << log_object;
}

void Logger::open(const std::string &t_file_name)
{
	this->close();
	openOutFile(t_file_name);
	m_isSet = true;
}

void Logger::open()
{
	this->open("logout.txt");
}

void Logger::close()
{
	if (!m_isSet)
		return ;
	m_outFile.close();
	m_isSet = false;
}

static std::string level_to_string(Logger::e_log_level t_level)
{
	std::string level_list[] = {
		"INFO",
		"DEBUG",
		"WARN",
		"ERROR",
		"UNKOWN"
	};

	if (t_level >= Logger::LOG_LEVEL_LEN)
		return (level_list[Logger::LOG_LEVEL_LEN]);
	return (level_list[t_level]);
}

void Logger::openOutFile(const std::string &t_file_name)
{
	this->m_outFile.open(t_file_name.c_str(), std::fstream::app );
	if (this->m_outFile.bad() || !this->m_outFile.is_open())
		throw WebservException(std::string("logger: ") + t_file_name + ": " + strerror(errno));
	this->log(Logger::INFO, "---start log---");
}
std::ostream &operator<<(std::ostream &os, const Logger::s_log_object &t_log_object)
{
	std::ostringstream log_entry;

	log_entry << "[" << t_log_object.str_time << "] "
		<< level_to_string(t_log_object.type)
		<< ": " << t_log_object.message
		<< std::endl;
	os << log_entry.str();
	return (os);
}
