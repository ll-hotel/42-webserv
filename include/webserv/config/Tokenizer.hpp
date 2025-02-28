/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tokenizer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:38:47 by ll-hotel          #+#    #+#             */
/*   Updated: 2025/02/25 15:58:57 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Option.hpp"
#include "Token.hpp"
#include <string>
#include <vector>

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

	std::string m_str;
	size_t m_i;
};
