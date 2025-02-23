/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tokenizer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:38:47 by ll-hotel          #+#    #+#             */
/*   Updated: 2025/02/23 17:33:55 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Token.hpp"
#include <string>
#include <vector>

template <typename T> class Option
{
public:
        Option();
        Option(const T &);
        Option &operator=(const Option &);
        ~Option();
        bool is_some() const;
        T &value();
        const T &value() const;

private:
        T _value;
};

class Tokenizer
{
public:
        Tokenizer();
        Tokenizer(const std::string &str);
        Tokenizer(const Tokenizer &);
        ~Tokenizer();
        std::vector<Token> tokenize();
        Option<char> peek() const;
        char consume();

private:
        Tokenizer &operator=(const Tokenizer &);

        const std::string _str;
        size_t _i;
};
