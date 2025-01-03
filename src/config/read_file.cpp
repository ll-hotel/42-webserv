/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 13:00:58 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/12/15 22:10:15 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv/Exception.hpp"
#include <fstream>
#include <string>
#include <cstring>

std::string read_file(const std::string &file_path)
{
	std::string content;
	std::ifstream file_stream(file_path.c_str());

	if (!file_stream.is_open()) {
		content = "can not open " + file_path;
		content += std::string(": ") + std::strerror(errno);
		WS_THROW(content);
	}
	std::getline(file_stream, content, '\0');
	file_stream.close();
	return content;
}
