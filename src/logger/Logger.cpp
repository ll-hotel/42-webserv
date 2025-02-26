/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 09:59:48 by gcros             #+#    #+#             */
/*   Updated: 2025/02/25 18:08:40 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv/Logger.hpp"
#include <cerrno>
#include <cstring>
#include <iostream>
#include <sstream>

Logger::Logger() { this->m_isSet = false; }

Logger::Logger(const std::string &t_file_name)
{
	this->openOutFile(t_file_name);
}

Logger::~Logger() { this->close(); }

static std::string level_to_string(Logger::e_log_level t_level)
{
	std::string level_list[] = {"INIT", "INFO",  "DEBUG",
				    "WARN", "ERROR", "UNKOWN"};

	if (t_level >= Logger::LOG_LEVEL_LEN)
		return (level_list[Logger::LOG_LEVEL_LEN]);
	return (level_list[t_level]);
}

void Logger::log(Logger::e_log_level t_level, const std::string &t_message)
{
	log(level_to_string(t_level), t_message);
}

void Logger::log(std::string t_str_level, const std::string &t_message)
{
	struct Logger::s_log_object log_object = {};
	time_t raw_time;
	tm *timeinfo;

	log_object.message = t_message;
	log_object.level = t_str_level;
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
}

void Logger::open() { this->open("logout.txt"); }

void Logger::close()
{
	if (!m_isSet)
		return;
	m_outFile.close();
	m_isSet = false;
}

void Logger::openOutFile(const std::string &t_file_name)
{
	this->m_outFile.open(t_file_name.c_str(), std::fstream::app);
	if (this->m_outFile.bad() || !this->m_outFile.is_open())
		throw WebservException(std::string("logger: ") + t_file_name +
				       ": " + strerror(errno));
	this->m_isSet = true;
	this->log(Logger::INIT, "---start log---");
}
std::ostream &operator<<(std::ostream &os,
			 const Logger::s_log_object &t_log_object)
{
	std::ostringstream log_entry;

	log_entry << "[" << t_log_object.str_time << "] "
		  << "[" << t_log_object.level << "]"
		  << ": " << t_log_object.message << std::endl;
	os << log_entry.str();
	os.flush();
	return (os);
}
