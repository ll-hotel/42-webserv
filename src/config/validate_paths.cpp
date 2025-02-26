/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_paths.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:07:02 by ll-hotel          #+#    #+#             */
/*   Updated: 2025/02/26 11:39:31 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv/config/validate_paths.hpp"
#include "webserv/Exception.hpp"
#include "webserv/ServerConfig.hpp"
#include <cstring>
#include <map>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

void validate_paths(const ServerConfig &sconf)
{
	typedef std::map<int, std::string>::const_iterator ErrorPageIterator;
	for (ErrorPageIterator page = sconf.errorPages().begin();
	     page != sconf.errorPages().end(); page++) {
		const std::string &page_path = page->second;

		if (::access(page_path.c_str(), F_OK) == -1)
			WS_THROW(page_path + ": " + WS_STRERROR);

		struct stat page_stat = {};
		if (::stat(page_path.c_str(), &page_stat) == -1)
			WS_THROW(page_path + ": " + WS_STRERROR);

		if (S_ISBLK(page_stat.st_mode))
			WS_THROW(page_path + ": Is a block device");
		else if (S_ISDIR(page_stat.st_mode))
			WS_THROW(page_path + ": Is a directory");
	}
}
