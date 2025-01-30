/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 21:00:43 by ll-hotel          #+#    #+#             */
/*   Updated: 2025/01/28 17:32:09 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP
#define CONFIG_HPP
#include <fstream>
#include <map>
#include <string>
#include <vector>

class Config {
public:
	class Location {
		std::string root;
		std::string alias;
		bool do_post;
		bool do_get;
	};

private:
	std::string _host;
	std::string _root;
	std::string _index;
	std::map<int, std::string> _error_pages;
	std::vector<Location> _locations;
	std::vector<std::string> _allowed_cgi;
	size_t _body_size;
	int _port;
	bool _do_directory_listing;
	bool _do_post;
	bool _do_get;
	bool _do_upload;
	std::string _upload_dir;

public:
	Config(std::ifstream &file);
	Config();
	Config(const Config &other);
	Config& operator=(const Config &other);
	~Config();
};

#endif
