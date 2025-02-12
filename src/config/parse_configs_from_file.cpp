/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_configs_from_file.cpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 10:39:53 by ll-hotel          #+#    #+#             */
/*   Updated: 2025/02/08 11:45:34 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Token.hpp"
#include "webserv/Exception.hpp"
#include "webserv/ServerConfig.hpp"
#include <cerrno>
#include <cstring>
#include <fstream>
#include <vector>

std::vector<ServerConfig> parse_configs_from_file(const std::string &filename)
{
	std::vector<Token> tokens;
	{
		std::ifstream file(filename.c_str());
		if (!file.is_open())
			WS_THROW("can not open `" + filename + \
					"' for reading: " + strerror(errno));
		tokens = file_lexer(file);
	}
	if (tokens.empty())
		WS_THROW("empty configuration file");
	std::vector<ServerConfig> configurations;
	size_t start = 0;
	size_t end = 0;
	while (start < tokens.size()) {
		while (tokens[end].type() != Token::CONTEXT_END) {
			end += 1;
			if (end == tokens.size())
				WS_THROW("missing end of context");
		}
		end += 1;
		std::vector<Token> config_tokens(tokens.begin() + start, \
				tokens.begin() + end);
		start = end;
		configurations.push_back(ServerConfig(config_tokens));
	}
	return configurations;
}
