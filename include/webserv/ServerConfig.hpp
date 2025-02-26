/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerConfig.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 21:00:43 by ll-hotel          #+#    #+#             */
/*   Updated: 2025/02/25 16:12:55 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "config/Parser.hpp"
#include <map>
#include <ostream>
#include <string>
#include <vector>

class ServerConfig
{
public:
	class Location
	{
	private:
		std::string m_root;
		std::string m_alias;
		bool m_doPost;
		bool m_doGet;

	public:
		const std::string &root() const { return Location::m_root; }
		const std::string &alias() const { return Location::m_alias; }
		bool doPost() const { return Location::m_doPost; }
		bool doGet() const { return Location::m_doGet; }
	};

private:
	std::string m_serverName;
	std::string m_host;
	std::string m_root;
	std::string m_indexPage;
	std::map<int, std::string> m_errorPages;
	std::vector<Location> m_locations;
	std::vector<std::string> m_allowedCgi;
	std::map<std::string, bool> m_methods;
	size_t m_bodySize;
	int m_port;
	bool m_doDirectoryListing;
	std::string m_uploadDir;

	void setVar(const Parameter &parameter);

public:
	ServerConfig(const std::vector<Parameter> &tokens);
	ServerConfig();
	ServerConfig(const ServerConfig &other);
	ServerConfig &operator=(const ServerConfig &other);
	~ServerConfig();

	const std::string &serverName() const;
	const std::string &host() const;
	const std::string &root() const;
	const std::string &indexPage() const;
	const std::map<int, std::string> &errorPages() const;
	const std::vector<Location> &locations() const;
	const std::vector<std::string> &allowedCgi() const;
	size_t bodySize() const;
	int port() const;
	bool doDirectoryListing() const;
	bool doPost() const;
	bool doGet() const;
	bool doUpload() const;
	const std::string &uploadDir() const;
};

std::ostream &operator<<(std::ostream &, const ServerConfig &);

std::vector<ServerConfig> parse_configs_from_file(const std::string &filename);
