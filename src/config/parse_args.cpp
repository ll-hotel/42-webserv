/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 11:56:06 by ll-hotel          #+#    #+#             */
/*   Updated: 2025/02/23 17:34:40 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_args.hpp"
#include "Token.hpp"
#include "webserv/Exception.hpp"
#include "webserv/ServerConfig.hpp"
#include <cstdlib>
#include <map>

static void expect(const std::vector<Token> &tokens, size_t &i, Token::Type t)
{
        if (i + 1 >= tokens.size())
                WS_THROW("unexpected end of file");
        i += 1;
        if (tokens[i].type != t)
                WS_THROW("unexpected token `" + tokens[i].value + "' after `" +
                         tokens[i - 1].value + "'");
}

void parse_server_name(std::string &server_name,
                       const std::vector<Token> &tokens, size_t &i)
{
        expect(tokens, i, Token::WORD);
        server_name = tokens[i].value;
}

void parse_host(std::string &host, const std::vector<Token> &tokens, size_t &i)
{
        expect(tokens, i, Token::WORD);
        host = tokens[i].value;
}

void parse_root(std::string &root, const std::vector<Token> &tokens, size_t &i)
{
        expect(tokens, i, Token::WORD);
        root = tokens[i].value;
}

void parse_index_page(std::string &index_page, const std::vector<Token> &tokens,
                      size_t &i)
{
        expect(tokens, i, Token::WORD);
        index_page = tokens[i].value;
}

void parse_error_page(std::map<int, std::string> &error_pages,
                      const std::vector<Token> &tokens, size_t &i)
{
        int code;

        expect(tokens, i, Token::WORD);
        code = std::atol(tokens[i].value.c_str());
        i += 1;
        if (i >= tokens.size())
                WS_THROW("missing error page file for code " +
                         tokens[i - 1].value);
        if (tokens[i].type != Token::WORD)
                WS_THROW("unexpected token `" + tokens[i].value + "' after `" +
                         tokens[i - 1].value + "'");
        error_pages[code] = tokens[i].value;
}

void parse_location(std::vector<ServerConfig::Location> &locations,
                    const std::vector<Token> &tokens, size_t &i)
{
        WS_THROW("location TO DO!");
}

void parse_cgi(std::vector<std::string> &cgi, const std::vector<Token> &tokens,
               size_t &i)
{
        static const std::string valid_cgis = "py";

        do {
                expect(tokens, i, Token::WORD);
                if (valid_cgis.find(tokens[i].value) == std::string::npos)
                        WS_THROW("invalid cgi `" + tokens[i].value + "'");
                cgi.push_back(tokens[i].value);
        } while (i + 1 < tokens.size() && tokens[i + 1].type != Token::SEMI);
}

static bool is_number(const std::string &str)
{
        for (size_t i = 0; i < str.size(); i += 1) {
                if (!std::isdigit(str[i]))
                        return false;
        }
        return true;
}

void parse_body_size(size_t &body_size, const std::vector<Token> &tokens,
                     size_t &i)
{
        expect(tokens, i, Token::WORD);
        if (!is_number(tokens[i].value))
                WS_THROW("body size: invalid value `" + tokens[i].value +
                         "': expected a number");
        body_size = std::atol(tokens[i].value.c_str());
}

void parse_port(int &port, const std::vector<Token> &tokens, size_t &i)
{
        expect(tokens, i, Token::WORD);
        if (!is_number(tokens[i].value))
                WS_THROW("port: invalid value `" + tokens[i].value +
                         "': expected a number");
        port = std::atoi(tokens[i].value.c_str());
}

void parse_directory_listing(bool &directory_listing,
                             const std::vector<Token> &tokens, size_t &i)
{
        expect(tokens, i, Token::WORD);
        if (tokens[i].value != "false" && tokens[i].value != "true")
                WS_THROW("invalid value " + tokens[i].value + " for key " +
                         tokens[i - 1].value);
        directory_listing = tokens[i].value == "true";
}

void parse_methods(std::map<std::string, bool> &methods,
                   const std::vector<Token> &tokens, size_t &i)
{
        do {
                expect(tokens, i, Token::WORD);
                if (methods.find(tokens[i].value) == methods.end())
                        WS_THROW("unknown method `" + tokens[i].value + "'");
                else
                        methods[tokens[i].value] = true;
        } while (i + 1 < tokens.size() && tokens[i + 1].type != Token::SEMI);
}

void parse_upload_dir(std::string &upload_dir, const std::vector<Token> &tokens,
                      size_t &i)
{
        expect(tokens, i, Token::WORD);
        upload_dir = tokens[i].value;
}
