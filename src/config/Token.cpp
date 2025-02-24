/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:12:52 by ll-hotel          #+#    #+#             */
/*   Updated: 2025/02/24 14:25:15 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv/Token.hpp"

Token::Token(const std::string &str) : type(WORD), value(str)
{
        if (value.length() == 1) {
                if (value[0] == BRACK_LEFT || value[0] == BRACK_RIGHT ||
                    value[0] == SEMI)
                        type = (Type)value[0];
        }
}

Token::Token() : type(WORD), value() {}

Token::Token(const Token &other) : type(other.type), value(other.value) {}

Token &Token::operator=(const Token &other)
{
	if (this == &other)
		return *this;
	type = other.type;
        value = other.value;
        return *this;
}

Token::~Token() {}

std::ostream &operator<<(std::ostream &os, const Token &token)
{
        os << "Token { type: " << token.type << ", value: '" << token.value
           << "' }";
        return os;
}
