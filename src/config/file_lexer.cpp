/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 13:00:58 by ll-hotel          #+#    #+#             */
/*   Updated: 2025/01/28 18:55:06 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Token.hpp"
#include <cstring>
#include <fstream>
#include <string>
#include <vector>

static std::string read_word(std::ifstream &file, const std::string &delim)
{
	std::string w;
	char c;

	if (!file)
		return w;
	do {
		file.read(&c, 1);
	} while (delim.find(c) != std::string::npos && file);
	while (delim.find(c) == std::string::npos && file) {
		w += c;
		file.read(&c, 1);
	}
	return w;
}

static void push_token(std::vector<Token> &tokens, std::string &value)
{
	if (value.length() > 0) {
		tokens.push_back(Token(value));
		value.clear();
	}
}

std::vector<Token> file_lexer(std::ifstream &file)
{
	const std::string spaces = " \t\r\n";
	const std::string specials = "{};";
	std::string word;
	std::vector<Token> tokens;

	word = read_word(file, spaces);
	while (!word.empty()) {
		std::string token_value;

		for (size_t i = 0; i < word.length(); i += 1) {
			if (specials.find(word[i]) == std::string::npos) {
				token_value += word[i];
			} else {
				push_token(tokens, token_value);
				token_value += word[i];
				push_token(tokens, token_value);
			}
		}
		push_token(tokens, token_value);
		word = read_word(file, spaces);
	}
	return tokens;
}
