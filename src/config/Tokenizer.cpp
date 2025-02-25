/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tokenizer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:54:36 by ll-hotel          #+#    #+#             */
/*   Updated: 2025/02/25 15:22:02 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv/config/Tokenizer.hpp"

Tokenizer::Tokenizer() : _str(), _i(0) {}

Tokenizer::Tokenizer(const std::string &str) : _str(str), _i(0) {}

Tokenizer::Tokenizer(const Tokenizer &other) : _str(other._str), _i(other._i) {}

Tokenizer &Tokenizer::operator=(const Tokenizer &other)
{
        _str = other._str;
        _i = other._i;
        return *this;
}

Tokenizer::~Tokenizer() {}

static Option<std::string> read_token_str(Tokenizer &tokenizer)
{
        static const std::string specials("{};");
        std::string w;

        if (!tokenizer.peek().is_some())
                return Option<std::string>();
        while (tokenizer.peek().is_some() &&
               std::isspace(tokenizer.peek().value()))
                tokenizer.consume();
        if (tokenizer.peek().is_some() &&
            specials.find(tokenizer.peek().value()) != std::string::npos) {
                w += tokenizer.consume();
                return w;
        }
        while (tokenizer.peek().is_some() &&
               !std::isspace(tokenizer.peek().value()) &&
               specials.find(tokenizer.peek().value()) == std::string::npos)
                w += tokenizer.consume();
        if (w.length() == 0)
                return Option<std::string>();
        return Option<std::string>(w);
}

std::vector<Token> Tokenizer::tokenize()
{
        std::vector<Token> tokens;

        while (peek().is_some()) {
                Option<std::string> token_str = read_token_str(*this);
                if (token_str.is_some())
                        tokens.push_back(Token(token_str.value()));
        }
        _i = 0;
        return tokens;
}

Option<char> Tokenizer::peek() const
{
        if (_i >= _str.length())
                return Option<char>();
        return Option<char>(_str[_i]);
}

char Tokenizer::consume() { return _str[_i++]; }
