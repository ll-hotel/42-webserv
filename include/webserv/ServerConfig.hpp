/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerConfig.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 21:00:43 by ll-hotel          #+#    #+#             */
/*   Updated: 2025/02/08 12:54:34 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP
#define CONFIG_HPP
#include <map>
#include <ostream>
#include <string>
#include <vector>

class Token;

class ServerConfig {
public:
	class Location {
	private:
		std::string _root;
		std::string _alias;
		bool _do_post;
		bool _do_get;
	public:
		const std::string& root() const { return Location::_root; }
		const std::string& alias() const { return Location::_alias; }
		const bool do_post() const { return Location::_do_post; }
		const bool do_get() const { return Location::_do_get; }
	};

private:
	std::string _server_name;
	std::string _host;
	std::string _root;
	std::string _index_page;
	std::map<int, std::string> _error_pages;
	std::vector<Location> _locations;
	std::vector<std::string> _allowed_cgi;
	std::map<std::string, bool> _methods;
	size_t _body_size;
	int _port;
	bool _do_directory_listing;
	std::string _upload_dir;

	size_t setVar(int, const std::vector<Token>&, size_t);

public:
	ServerConfig(const std::vector<Token> &tokens);
	ServerConfig();
	ServerConfig(const ServerConfig &other);
	ServerConfig& operator=(const ServerConfig &other);
	~ServerConfig();

	const std::string& server_name() const;
	const std::string& host() const;
	const std::string& root() const;
	const std::string& index_page() const;
	const std::map<int, std::string>& error_pages() const;
	const std::vector<Location>& locations() const;
	const std::vector<std::string>& allowed_cgi() const;
	const size_t body_size() const;
	const int port() const;
	const bool do_directory_listing() const;
	const bool do_post() const;
	const bool do_get() const;
	const bool do_upload() const;
	const std::string& upload_dir() const;
};

std::ostream& operator<<(std::ostream&, const ServerConfig&);

std::vector<ServerConfig> parse_configs_from_file(const std::string &filename);

#endif
