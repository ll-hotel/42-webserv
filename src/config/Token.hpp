/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:46:18 by ll-hotel          #+#    #+#             */
/*   Updated: 2025/02/08 10:36:27 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_TOKEN_HPP
#define WEBSERV_TOKEN_HPP
#include <string>
#include <vector>

#define TOKEN_ARG_END ';'
#define TOKEN_CONTEXT_START '{'
#define TOKEN_CONTEXT_END '}'

class Token {
	public:
		enum Type {
			WORD,
			CONTEXT_START,
			CONTEXT_END,
			ARG_END,
		};

	private:
		Type _type;
		std::string _value;

	public:
		Token(const std::string &value);
		Token();
		Token(const Token &other);
		Token& operator=(const Token &other);
		~Token() throw();

		const Type& type() const throw();
		const std::string& value() const throw();
};

std::vector<Token> file_lexer(std::ifstream &file);

#endif
