/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 09:59:48 by gcros             #+#    #+#             */
/*   Updated: 2025/02/28 14:17:58 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv/Logger.hpp"
#include <cerrno>
#include <cstring>
#include <iostream>
#include <sstream>


Logger & Logger::GetInstance()
{
	static Logger	s_Instance;
	return (s_Instance);
}

Logger::Logger()
{
	init();
}

void Logger::init()
{
	time_t	raw_time;
	tm	*timeinfo;
	char	str_time[20];

	open(".log");
	raw_time = time(0);
	timeinfo = localtime(&raw_time);
	strftime(str_time, 20, "%Y%m%d", timeinfo);
	open(std::string(".log") + str_time);
	strftime(str_time, 20, "%Y%m%d%H%M%S", timeinfo);
	open(std::string(".log") + str_time);
}

Logger::Logger(const std::string &t_file_name)
{
	this->openOutFile(t_file_name);
}

Logger::~Logger() {this->closeAll(); }

static std::string level_to_string(Logger::e_log_level t_level)
{
	std::string level_list[] = {"INIT", "INFO",  "DEBUG",
				    "WARN", "ERROR", "UNKOWN"};

	if (t_level >= Logger::LOG_LEVEL_LEN)
		return (level_list[Logger::LOG_LEVEL_LEN]);
	return (level_list[t_level]);
}

void Logger::message(Logger::e_log_level t_level, const std::string &t_message)
{
	message(level_to_string(t_level), t_message);
}

void Logger::message(std::string t_str_level, const std::string &t_message)
{
	struct Logger::s_log_object log_object = {};
	time_t raw_time;
	tm *timeinfo;

	log_object.message = t_message;
	log_object.level = t_str_level;
	raw_time = time(0);
	timeinfo = localtime(&raw_time);
	strftime(log_object.str_time, 20, "%Y-%m-%d %H:%M:%S", timeinfo);
	print(log_object);
}

void Logger::print(Logger::s_log_object &log_object)
{
	std::map<std::string, std::ofstream *>::iterator it_cur = m_files.begin();
	std::map<std::string, std::ofstream *>::iterator it_end = m_files.end();

	std::cout << log_object;

	for (; it_cur != it_end; it_cur++)
	{
		if (it_cur->second != NULL)
			*it_cur->second << log_object; 
	}
}

void Logger::open(const std::string &t_file_name)
{
	openOutFile(t_file_name);
}

void Logger::close(const std::string &t_file_name)
{
	delete m_files[t_file_name];
	m_files[t_file_name] = NULL;
}

void Logger::closeAll()
{
	std::map<std::string, std::ofstream *>::iterator it_cur = m_files.begin();
	std::map<std::string, std::ofstream *>::iterator it_end = m_files.end();
	for (; it_cur != it_end; it_cur++)
	{
		delete it_cur->second;
		it_cur->second = NULL;
	}
}

void Logger::openOutFile(const std::string &t_file_name)
{
	if (this->m_files[t_file_name] != NULL)
		throw WebservException(std::string("logger: ") + t_file_name +
		": already open");
	std::ofstream *new_file = new std::ofstream(t_file_name.c_str(), std::fstream::app);

	if (new_file->bad() || !new_file->is_open())
	{
		delete new_file;
		throw WebservException(std::string("logger: ") + t_file_name +
				       ": " + strerror(errno));
	}
	m_files[t_file_name] = new_file;
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
