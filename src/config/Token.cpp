/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:12:52 by ll-hotel          #+#    #+#             */
/*   Updated: 2025/02/08 10:36:40 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Token.hpp"

Token::Token(const std::string &value)
{
	_type = WORD;
	if (value.length() == 1) {
		switch (value[0]) {
			case TOKEN_CONTEXT_START:
				_type = Token::CONTEXT_START;
				break;
			case TOKEN_CONTEXT_END:
				_type = Token::CONTEXT_END;
				break;
			case TOKEN_ARG_END:
				_type = Token::ARG_END;
				break;
		}
	}
	_value = value;
}

Token::Token()
{
}

Token::Token(const Token &other)
{
	*this = other;
}

Token& Token::operator=(const Token &other)
{
	_type = other.type();
	_value = other.value();
	return *this;
}

Token::~Token() throw()
{
}

const Token::Type& Token::type() const throw()
{
	return _type;
}

const std::string& Token::value() const throw()
{
	return _value;
}
