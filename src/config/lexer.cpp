/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 13:04:23 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/12/15 22:06:23 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv/Exception.hpp"
#include "webserv/parsing.hpp"
#include <string>

static void token_checker(const ConfigToken::Vector &tokens);
static std::string itos(int n);
static bool isseparator(char c) throw();

ConfigToken::Vector lexer(const std::string &content)
{
	ConfigToken::Vector tokens;
	int line;
	size_t i;
	size_t w;

	line = 0;
	i = 0;
	for (i = 0; i < content.length(); i += 1) {
		const char c = content[i];

		if (!isseparator(c)) {
			w = i;
			while (i < content.length() && !isseparator(content[i]))
				i += 1;
			const std::string word(content.substr(w, i - w));
			i -= 1;
			tokens.push_back(ConfigToken(WORD, word));
		} else if (!std::isspace(c)) {
			ConfigToken::type_type token_type;
			ConfigToken::value_type token_value;

			switch (c) {
			case '{':
				token_type = BLOCK_START;
				token_value = "{";
				break;
			case '}':
				token_type = BLOCK_END;
				token_value = "}";
				break;
			case ';':
				token_type = ARG_END;
				token_value = ";";
				break;
			default:
				throw(WebservException("unexpected character "
					"'" + std::string((char []){c, '\0'}) +
					"' at line " + itos(line)));
			}
			tokens.push_back(ConfigToken(token_type, token_value));
		}
		if (c == '\n')
			line += 1;
	}
	token_checker(tokens);
	return tokens;
}

static void increment_i(const ConfigToken &tok, size_t &i, const size_t l) {
	i += 1;
	if (i >= l && tok.type() != BLOCK_END) {
		std::string err = "missing ";
		if (tok.type() == BLOCK_START || tok.type() == ARG_END)
			err += "'}'";
		else
			err += "value after token " + tok.value();
		throw(WebservException(err));
	}
}

static void token_checker(const ConfigToken::Vector &tokens)
{
	const size_t limit = tokens.size();
	size_t i = 0;

	while (i < limit) {
		if (tokens[i].value() != "server")
			THROW_UNEXPECTED(tokens[i].value());
		increment_i(tokens[i], i, limit);
		if (tokens[i].type() != BLOCK_START)
			THROW_UNEXPECTED(tokens[i].value());
		increment_i(tokens[i], i, limit);
		while (tokens[i].type() != BLOCK_END) {
			do {
				if (tokens[i].type() != WORD)
					THROW_UNEXPECTED(tokens[i].value());
				increment_i(tokens[i], i, limit);
			} while (tokens[i].type() != ARG_END);
			increment_i(tokens[i], i, limit);
		}
		increment_i(tokens[i], i, limit);
        }
}

static std::string itos(int n)
{
	const bool negative = n < 0;
	char buf[15] = {0};
	size_t i;

	i = 15;
	do {
		buf[--i] = (n % 10) + '0';
		n /= 10;
	} while (n != 0);
	if (negative)
		buf[--i] = '-';
	return std::string(&buf[i]);
}

static bool isseparator(char c) throw()
{
	static const std::string separators = "{};";

	return std::isspace(c) || separators.find(c) != std::string::npos;
}
