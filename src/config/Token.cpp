/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:12:52 by ll-hotel          #+#    #+#             */
/*   Updated: 2025/02/23 19:14:43 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv/Token.hpp"

Token::Token(const std::string &str) : type(WORD), value(str)
{
        if (value.length() == 1) {
                switch (value[0]) {
                case BRACK_LEFT:
                case BRACK_RIGHT:
                case SEMI:
                        type = (Type)value[0];
                }
        }
}

Token::Token() : type(WORD), value() {}

Token::Token(const Token &other) : type(WORD), value(other.value) {}

Token &Token::operator=(const Token &other)
{
        value = other.value;
        return *this;
}

Token::~Token() {}
