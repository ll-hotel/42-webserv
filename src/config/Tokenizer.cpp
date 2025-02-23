/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tokenizer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:54:36 by ll-hotel          #+#    #+#             */
/*   Updated: 2025/02/23 16:44:03 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Tokenizer.hpp"

template <typename T> Option<T>::Option() : _value(0) {}

template <typename T> Option<T>::Option(const T &value) : _value(value) {}

template <typename T> Option<T> &Option<T>::operator=(const Option &other)
{
        _value = other._value();
        return *this;
}

template <typename T> Option<T>::~Option() {}

template <typename T> bool Option<T>::is_some() const
{
        return _value != (T){0};
}

template <typename T> T &Option<T>::value() { return _value; }

template <typename T> const T &Option<T>::value() const { return _value; }

/*** Tokenizer ***/

Tokenizer::Tokenizer() : _str(), _i(0) {}

Tokenizer::Tokenizer(const std::string &str) : _str(str), _i(0) {}

Tokenizer::Tokenizer(const Tokenizer &other) : _str(other._str), _i(other._i) {}

Tokenizer &Tokenizer::operator=(const Tokenizer &other) { return *this; }

Tokenizer::~Tokenizer() {}

static std::string read_token_str(Tokenizer &tokenizer)
{
        static const std::string specials("{};");
        std::string w;
        char c;

        if (!tokenizer.peek().is_some())
                return w;
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
        return w;
}

std::vector<Token> Tokenizer::tokenize()
{
        std::vector<Token> tokens;

        while (peek().is_some())
                tokens.push_back(Token(read_token_str(*this)));
        _i = 0;
        return tokens;
}

Option<char> Tokenizer::peek() const
{
        if (_i >= _str.size())
                return Option<char>();
        return Option<char>(_str[_i]);
}

char Tokenizer::consume() { return _str[_i++]; }
