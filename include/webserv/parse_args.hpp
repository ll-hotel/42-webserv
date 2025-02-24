/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 13:17:30 by ll-hotel          #+#    #+#             */
/*   Updated: 2025/02/23 18:35:08 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "webserv/ServerConfig.hpp"
#include <map>
#include <string>
#include <vector>

void parse_server_name(const Parameter &, std::string *server_name);
void parse_host(const Parameter &, std::string *host);
void parse_root(const Parameter &, std::string *root);
void parse_index_page(const Parameter &, std::string *index_page);
void parse_error_page(const Parameter &,
                      std::map<int, std::string> *error_pages);
void parse_location(const Parameter &,
                    std::vector<ServerConfig::Location> *locations);
void parse_cgi(const Parameter &, std::vector<std::string> *cgi);
void parse_body_size(const Parameter &, size_t *body_size);
void parse_port(const Parameter &, int *port);
void parse_directory_listing(const Parameter &, bool *directory_listing);
void parse_methods(const Parameter &, std::map<std::string, bool> *methods);
void parse_upload_dir(const Parameter &, std::string *upload_dir);
