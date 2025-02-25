/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_parameter.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 13:17:30 by ll-hotel          #+#    #+#             */
/*   Updated: 2025/02/25 15:14:12 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "webserv/ServerConfig.hpp"
#include <map>
#include <string>
#include <vector>

void change_server_name(const Parameter &, std::string *server_name);
void change_host(const Parameter &, std::string *host);
void change_root(const Parameter &, std::string *root);
void change_index_page(const Parameter &, std::string *index_page);
void change_error_page(const Parameter &,
                       std::map<int, std::string> *error_pages);
void change_location(const Parameter &,
                     std::vector<ServerConfig::Location> *locations);
void change_cgi(const Parameter &, std::vector<std::string> *cgi);
void change_body_size(const Parameter &, size_t *body_size);
void change_port(const Parameter &, int *port);
void change_directory_listing(const Parameter &, bool *directory_listing);
void change_methods(const Parameter &, std::map<std::string, bool> *methods);
void change_upload_dir(const Parameter &, std::string *upload_dir);
