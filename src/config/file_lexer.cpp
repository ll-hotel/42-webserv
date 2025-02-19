/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_lexer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 13:00:58 by ll-hotel          #+#    #+#             */
/*   Updated: 2025/02/19 16:33:57 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Token.hpp"
#include <cstring>
#include <fstream>
#include <string>
#include <vector>

static std::string read_word(std::ifstream &file)
{
	std::string w;
	char c;

	if (!file)
		return w;
	do {
		file.read(&c, 1);
	} while (file && std::isspace(c));
	while (file && !std::isspace(c)) {
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

static std::vector<std::string> read_words_and_split(std::ifstream &file)
{
	std::vector<std::string> split;

	while (file) {
		const std::string word = read_word(file);
		const std::string *s_ptr = &word;
		std::string suffix;
		for (size_t pos = 0; pos < word.size(); pos += 1) {
			size_t len = s_ptr->find_first_of("{};");
			if (len == 0)
				len += 1;
			split.push_back(s_ptr->substr(0, len));
			if (len != std::string::npos) {
				suffix = s_ptr->substr(len);
				s_ptr = &suffix;
			}
			pos += len - 1;
		}
	}
	return split;
}

std::vector<Token> file_lexer(std::ifstream &file)
{
	const std::vector<std::string> identifiers = read_words_and_split(file);
	std::vector<Token> tokens;
	for (size_t i = 0; i < identifiers.size(); i += 1)
		tokens.push_back(Token(identifiers[i]));
	return tokens;
}
