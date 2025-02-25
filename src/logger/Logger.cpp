/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 09:59:48 by gcros             #+#    #+#             */
/*   Updated: 2025/02/25 12:24:35 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv/Logger.hpp"
#include <sstream>
#include <iostream>
#include <cstring>
#include <cerrno>

Logger::Logger()
{
	this->openOutFile("log.log");
}

Logger::Logger(const std::string &file_name)
{
	this->openOutFile(file_name);
}

Logger::~Logger()
{
	this->_outFile.flush();
	this->_outFile.close();
}

void Logger::log(Logger::e_log_level level, const std::string &message)
{
	struct Logger::s_log_object log_object = {0};
	time_t raw_time;
	tm* timeinfo;

	log_object.type = level;
	log_object.message = message;
	raw_time = time(0);
	timeinfo = localtime(&raw_time);
	strftime(log_object.str_time, 20, "%Y-%m-%d %H:%M:%S", timeinfo);
	this->_messageQueue.push(log_object);
}

static std::string level_to_string(Logger::e_log_level level)
{
	std::string level_list[] = {
		"INFO",
		"DEBUG",
		"WARN",
		"ERROR",
		"UNKOWN"
	};

	if (level >= Logger::LOG_LEVEL_LEN)
		return (level_list[Logger::LOG_LEVEL_LEN]);
	return (level_list[level]);
}

void Logger::flush()
{
	while (this->_messageQueue.size() > 0)
	{
		Logger::s_log_object log_object = this->_messageQueue.front();
		this->_messageQueue.pop();
		std::cout << log_object;
		this->_outFile << log_object;
	}
	this->_outFile.flush();
	std::cout.flush();
}

void Logger::openOutFile(const std::string &file_name)
{
	this->_outFile.open(file_name.c_str(), std::fstream::app );
	if (this->_outFile.bad() || !this->_outFile.is_open())
		throw WebservException(std::string("logger: ") + file_name + ": " + strerror(errno));
	this->log(Logger::INFO, "---start log---");
	this->flush();
}
std::ostream &operator<<(std::ostream &os, const Logger::s_log_object &log_object)
{
	std::ostringstream log_entry;

	log_entry << "[" << log_object.str_time << "] "
		<< level_to_string(log_object.type)
		<< ": " << log_object.message
		<< std::endl;
	os << log_entry.str();
	return (os);
}
