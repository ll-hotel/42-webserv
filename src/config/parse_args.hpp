/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 13:17:30 by ll-hotel          #+#    #+#             */
/*   Updated: 2025/02/08 13:18:16 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Token.hpp"
#include "webserv/ServerConfig.hpp"
#include <map>
#include <string>
#include <vector>

void parse_server_name(std::string &server_name, \
		const std::vector<Token> &tokens, size_t &i);
void parse_host(std::string &host, \
		const std::vector<Token> &tokens, size_t &i);
void parse_root(std::string &root, \
		const std::vector<Token> &tokens, size_t &i);
void parse_index_page(std::string &index_page, \
		const std::vector<Token> &tokens, size_t &i);
void parse_error_page(std::map<int, std::string> &error_pages, \
		const std::vector<Token> &tokens, size_t &i);
void parse_location(std::vector<ServerConfig::Location> &locations, \
		const std::vector<Token> &tokens, size_t &i);
void parse_cgi(std::vector<std::string> &cgi, \
		const std::vector<Token> &tokens, size_t &i);
void parse_body_size(size_t &body_size, \
		const std::vector<Token> &tokens, size_t &i);
void parse_port(int &port, \
		const std::vector<Token> &tokens, size_t &i);
void parse_directory_listing(bool &directory_listing, \
		const std::vector<Token> &tokens, size_t &i);
void parse_methods(std::map<std::string, bool> &methods, \
		const std::vector<Token> &tokens, size_t &i);
void parse_upload_dir(std::string &upload_dir, \
		const std::vector<Token> &tokens, size_t &i);
