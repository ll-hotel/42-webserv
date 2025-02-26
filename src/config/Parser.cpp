/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:46:33 by ll-hotel          #+#    #+#             */
/*   Updated: 2025/02/25 15:59:12 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv/config/Parser.hpp"
#include "webserv/Exception.hpp"

Parser::Parser() : m_tokens(), m_i(0) {}

Parser::Parser(const std::vector<Token> &tokens) : m_tokens(tokens), m_i(0) {}

Parser::Parser(const Parser &other) : m_tokens(other.m_tokens), m_i(0) {}

Parser &Parser::operator=(const Parser &) { return *this; }

Parser::~Parser() {}

Option<Token> Parser::peek() const
{
	if (m_i >= m_tokens.size())
		return Option<Token>();
	return Option<Token>(m_tokens[m_i]);
}

Token Parser::consume() { return m_tokens[m_i++]; }

std::vector<Parameter> Parser::parse()
{
	std::vector<Parameter> parameters;

	if (!peek().is_some())
		WS_THROW("missing opening bracket");
	if (peek().value().type != Token::BRACK_LEFT)
		WS_THROW("unexpected token `" + peek().value().value +
			 "': expected {");
	consume();
	while (peek().is_some() && peek().value().type != Token::BRACK_RIGHT) {
		std::vector<std::string> words;
		while (peek().is_some() && peek().value().type == Token::WORD)
			words.push_back(consume().value);
		if (!peek().is_some()) {
			WS_THROW("unexpected end of file: missing semicolon");
		} else if (peek().value().type != Token::SEMI) {
			WS_THROW("unexpected token `" + consume().value +
				 "': expected semicolon");
		} else if (words.empty()) {
			WS_THROW("unexpected semicolon: expected parameter "
				 "identifier");
		}
		consume();
		std::string parameter_name = words[0];
		std::vector<std::string> parameter_args(words.begin() + 1,
							words.end());
		parameters.push_back(Parameter(parameter_name, parameter_args));
	}
	if (!peek().is_some())
		WS_THROW("unexpected end of file: missing closing bracket");
	return parameters;
}
