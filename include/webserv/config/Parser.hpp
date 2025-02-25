/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:40:52 by ll-hotel          #+#    #+#             */
/*   Updated: 2025/02/25 18:38:23 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Option.hpp"
#include "Token.hpp"
#include <string>
#include <utility>
#include <vector>

typedef std::vector<std::string> StringVector;
typedef std::pair<std::string, StringVector> Parameter;

class Parser
{
public:
        Parser();
        Parser(const std::vector<Token> &tokens);
        Parser(const Parser &);
        ~Parser();
        Option<Token> peek() const;
        Token consume();
        std::vector<Parameter> parse();

private:
        Parser &operator=(const Parser &);

        const std::vector<Token> m_tokens;
        size_t m_i;
};
