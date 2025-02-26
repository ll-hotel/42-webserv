/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_paths.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:07:02 by ll-hotel          #+#    #+#             */
/*   Updated: 2025/02/26 13:50:37 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv/config/validate_paths.hpp"
#include "webserv/Exception.hpp"
#include "webserv/ServerConfig.hpp"
#include <cstdlib>
#include <cstring>
#include <map>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

static void validate_root(const std::string &path)
{
	if (::access(path.c_str(), F_OK) == -1)
		WS_THROW("invalid root directory `" + path +
			 "': no such file or directory");
	struct stat root_stat = {};
	if (::stat(path.c_str(), &root_stat) == -1 ||
	    !S_ISDIR(root_stat.st_mode))
		WS_THROW("invalid root directory `" + path +
			 "': is not a directory");
}

static void validate_web_page(const std::string &path)
{
	if (::access(path.c_str(), F_OK) == -1)
		WS_THROW("invalid web page `" + path +
			 "': no such file or directory");
	struct stat page_stat = {};
	if (::stat(path.c_str(), &page_stat) == -1)
		WS_THROW("invalid web page `" + path + "': " + WS_STRERROR);
	else if (S_ISBLK(page_stat.st_mode))
		WS_THROW("invalid web page `" + path + "': is a block device");
	else if (S_ISDIR(page_stat.st_mode))
		WS_THROW("invalid web page `" + path + "': is a directory");
}

static void validate_upload_dir(const std::string &path)
{
	if (::access(path.c_str(), F_OK) == -1)
		WS_THROW("invalid upload directory `" + path +
			 "': no such file or directory");
	struct stat path_stat = {};
	if (::stat(path.c_str(), &path_stat) == -1 ||
	    !S_ISDIR(path_stat.st_mode))
		WS_THROW("invalid path directory `" + path +
			 "': is not a directory");
}

void validate_paths(const ServerConfig &sconf)
{
	const std::string &root = sconf.root();
	validate_root(root);

	validate_web_page(root + "/" + sconf.indexPage());

	typedef std::map<int, std::string>::const_iterator ErrorPageIterator;
	for (ErrorPageIterator page = sconf.errorPages().begin();
	     page != sconf.errorPages().end(); page++)
		validate_web_page(root + "/" + page->second);

	validate_upload_dir(root + "/" + sconf.uploadDir());
}
