/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:46:18 by ll-hotel          #+#    #+#             */
/*   Updated: 2025/02/23 17:31:55 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>

struct Token {
        Token(const std::string &value);

        enum Type {
                WORD,
                BRACK_LEFT = '{',
                BRACK_RIGHT = '}',
                SEMI = ';',
        } type;
        std::string value;
};
