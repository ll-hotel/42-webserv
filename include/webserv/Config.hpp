/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 21:00:43 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/12/15 22:03:39 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_CONFIG_HPP
#define WEBSERV_CONFIG_HPP
#include "webserv/Exception.hpp"
#include "webserv/parsing.hpp"
#include <map>
#include <stdint.h>
#include <string>
#include <vector>

class Config {
public:
	class Server {
	private:
		uint16_t _port;
		std::string _host;
		std::vector<std::string> _server_names;
		// TODO: ERROR PAGES
		// error_page 404 ./404_page.html
		// TODO: ROUTES
		// class RedirectionRoute {
		// public:
		// 	std::vector<std::string> route_methods;
		// 	std::string redirection_url;
		// 	std::string root_dir;
		// 	bool do_directory_listing;
		// 	std::string default_dir_file;
		// 	// TODO: CGI
		// 	// std::string cgi_extensions;
		// 	std::string http_methods;
		// 	bool do_file_upload;
		// 	std::string file_save_dir;
		// };
		// std::vector<RedirectionRoute> routes;
		void __use_token(ConfigToken::Vector::const_iterator &tok);

	public:
		Server();
		Server(ConfigToken::Vector::const_iterator &it);
                Server& operator=(const Server &other) throw();

		uint16_t port() const;
		const std::string& host() const;
		const std::vector<std::string>& server_names() const;
	};

private:
	std::vector<Server> _servers;
	std::map<uint16_t, std::string> _error_pages;
	size_t _max_client_body_size;

public:
	Config() throw();
	Config(const std::string &file_path);
	Config(const Config&) throw();
	Config& operator=(const Config&) throw();
	~Config() throw();

	const std::vector<Server>& getServerConfigs();
	const std::map<uint16_t, std::string>& getErrorPages();
	size_t getMaxClientBodySize();

	class FileErrorException : public WebservException {
		FileErrorException(const std::string &str):
			WebservException(str)
		{}
	};
};

#endif
