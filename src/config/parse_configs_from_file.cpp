/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_configs_from_file.cpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 10:39:53 by ll-hotel          #+#    #+#             */
/*   Updated: 2025/02/23 17:34:22 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Token.hpp"
#include "Tokenizer.hpp"
#include "webserv/Exception.hpp"
#include "webserv/ServerConfig.hpp"
#include <cerrno>
#include <cstring>
#include <fstream>
#include <vector>

std::vector<ServerConfig> parse_configs_from_file(const std::string &filename)
{
	std::ifstream file(filename.c_str());
	if (!file.is_open()) {
		WS_THROW("can not open `" + filename + "' for reading: " + \
				strerror(errno));
	}
	std::vector<Token> tokens;
	{
		std::string file_content;
		std::getline(file, file_content, '\0');
		tokens = Tokenizer(file_content).tokenize();
	}
	if (tokens.empty())
		WS_THROW("empty configuration file");
	std::vector<ServerConfig> configurations;
	for (size_t end = 0, start = 0; start < tokens.size(); start = end) {
		while (end < tokens.size() && \
				tokens[end].type != Token::BRACK_RIGHT)
			end += 1;
                if (end >= tokens.size())
			WS_THROW("missing context end");
		end += 1;
		std::vector<Token> config_tokens(tokens.begin() + start, \
				tokens.begin() + end);
		configurations.push_back(ServerConfig(config_tokens));
		if (end - 1 < tokens.size())
			end += 1;
	}
	return configurations;
}
