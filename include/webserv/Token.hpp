/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:46:18 by ll-hotel          #+#    #+#             */
/*   Updated: 2025/02/24 14:03:34 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <fstream>

class Token {
public:
	Token();
        Token(const std::string &value);
	Token(const Token&);
	Token& operator=(const Token&);
	~Token();

        enum Type {
                WORD,
                BRACK_LEFT = '{',
                BRACK_RIGHT = '}',
                SEMI = ';',
        } type;
        std::string value;
};

std::ostream& operator<<(std::ostream&, const Token&);
