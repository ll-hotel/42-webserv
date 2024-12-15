/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:46:18 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/12/15 20:46:25 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_PARSING_HPP
#define WEBSERV_PARSING_HPP
#include <list>
#include <vector>
#include <string>

template <typename TokenType, typename TokenValue>
class Token {
	private:
		TokenType _type;
		TokenValue _value;

	public:
		typedef std::list< Token<TokenType, TokenValue> >List;
		typedef std::vector< Token<TokenType, TokenValue> >Vector;
		typedef TokenType type_type;
		typedef TokenValue value_type;
		typedef const TokenType& const_typeref;
		typedef const TokenValue& const_valueref;

		Token()
		{};
		Token(const TokenType &type, const TokenValue &value)
		{
			_type = type;
			_value = value;
		};
		Token(const Token<TokenType, TokenValue> &other)
		{
			_type = other._type;
			_value = other._value;
		};
		Token& operator=(const Token<TokenType, TokenValue> &other)
		{
			_type = other._type;
			_value = other._value;
			return *this;
		};
		~Token() throw()
		{};

		const_typeref type() const throw() { return _type; }
		const_valueref value() const throw() { return _value; }
};

enum LexerType {
	WORD,
	BLOCK_START,
	BLOCK_END,
	ARG_END,
};

typedef Token<LexerType, std::string> ConfigToken;

#define THROW_UNEXPECTED(value) \
	throw(WebservException("unexpected token '" + (value) + "'"))

#endif
