/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerConfig.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 10:03:55 by ll-hotel          #+#    #+#             */
/*   Updated: 2025/02/23 17:33:40 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv/ServerConfig.hpp"
#include "Token.hpp"
#include "parse_args.hpp"
#include "webserv/Exception.hpp"
#include <cstdlib>
#include <string>
#include <utility>
#include <vector>

enum ServerConfigKeyType {
        SERVER_NAME,
        HOST,
        ROOT,
        INDEX_PAGE,
        ERROR_PAGE,
        LOCATION,
        CGI,
        BODY_SIZE,
        PORT,
        DIRECTORY_LISTING,
        METHODS,
        UPLOAD_DIR,
        MAX_KEY_TYPE = UPLOAD_DIR,
        INVALID = MAX_KEY_TYPE + 1,
};

static ServerConfigKeyType which_key_type(const Token &token)
{
        static std::map<std::string, ServerConfigKeyType> key_list;

        if (key_list.empty()) {
                key_list["server_name"] = SERVER_NAME;
                key_list["host"] = HOST;
                key_list["root"] = ROOT;
                key_list["index_page"] = INDEX_PAGE;
                key_list["error_page"] = ERROR_PAGE;
                key_list["location"] = LOCATION;
                key_list["cgi"] = CGI;
                key_list["body_size"] = BODY_SIZE;
                key_list["port"] = PORT;
                key_list["directory_listing"] = DIRECTORY_LISTING;
                key_list["methods"] = METHODS;
                key_list["upload_dir"] = UPLOAD_DIR;
        }
        std::map<std::string, ServerConfigKeyType>::const_iterator key =
            key_list.find(token.value);
        if (key != key_list.end())
                return key->second;
        return INVALID;
}

ServerConfig::ServerConfig(const std::vector<Token> &tokens)
{
        if (tokens.empty())
                WS_THROW("empty token list!");
        if (tokens.front().type != Token::BRACK_LEFT)
                WS_THROW("unexpected token `" + tokens.front().value +
                         "': expected context start");
        if (tokens.back().type != Token::BRACK_RIGHT)
                WS_THROW("missing end of context");
        *this = ServerConfig();
        size_t i;
        for (i = 1; i + 1 < tokens.size(); i += 1) {
                const Token &token = tokens[i];
                ServerConfigKeyType key = which_key_type(token.value);
                if (i + 1 >= tokens.size())
                        WS_THROW("missing argument for key `" + token.value +
                                 "'");
                i = this->setVar(key, tokens, i);
                if (tokens[i].type != Token::SEMI)
                        WS_THROW("missing end of line");
        }
        if (tokens[i].type != Token::BRACK_RIGHT)
                WS_THROW("missing end of context");
}

size_t ServerConfig::setVar(int key_type, const std::vector<Token> &tokens,
                            size_t i)
{
        if (key_type == INVALID)
                WS_THROW("invalid key `" + tokens[i].value + "'");
        switch (key_type) {
        case SERVER_NAME:
                parse_server_name(_server_name, tokens, i);
                break;
        case HOST:
                parse_host(_host, tokens, i);
                break;
        case ROOT:
                parse_root(_root, tokens, i);
                break;
        case INDEX_PAGE:
                parse_index_page(_index_page, tokens, i);
                break;
        case ERROR_PAGE:
                parse_error_page(_error_pages, tokens, i);
                break;
        case LOCATION:
                parse_location(_locations, tokens, i);
                break;
        case CGI:
                parse_cgi(_allowed_cgi, tokens, i);
                break;
        case BODY_SIZE:
                parse_body_size(_body_size, tokens, i);
                break;
        case PORT:
                parse_port(_port, tokens, i);
                break;
        case DIRECTORY_LISTING:
                parse_directory_listing(_do_directory_listing, tokens, i);
                break;
        case METHODS:
                parse_methods(_methods, tokens, i);
                break;
        case UPLOAD_DIR:
                parse_upload_dir(_upload_dir, tokens, i);
                break;
        }
        return i + 1;
}

ServerConfig::ServerConfig()
{
        _server_name = "server";
        _host = "127.0.0.1";
        _root = ".";
        _index_page = "index.html";
        // _error_pages;
        // _locations;
        // _allowed_cgi;
        _methods["POST"] = false;
        _methods["GET"] = false;
        _body_size = 1024;
        _port = 8080;
        _do_directory_listing = false;
        _upload_dir = "";
}

ServerConfig::ServerConfig(const ServerConfig &other) { *this = other; }

ServerConfig &ServerConfig::operator=(const ServerConfig &other)
{
        _server_name = other._server_name;
        _host = other._host;
        _root = other._root;
        _index_page = other._index_page;
        _error_pages = other._error_pages;
        _locations = other._locations;
        _allowed_cgi = other._allowed_cgi;
        _methods = other._methods;
        _body_size = other._body_size;
        _port = other._port;
        _do_directory_listing = other._do_directory_listing;
        _upload_dir = other._upload_dir;
        return *this;
}

ServerConfig::~ServerConfig() {}

const std::string &ServerConfig::server_name() const { return _server_name; }
const std::string &ServerConfig::host() const { return _host; }
const std::string &ServerConfig::root() const { return _root; }
const std::string &ServerConfig::index_page() const { return _index_page; }
const std::map<int, std::string> &ServerConfig::error_pages() const
{
        return _error_pages;
}
const std::vector<ServerConfig::Location> &ServerConfig::locations() const
{
        return _locations;
}
const std::vector<std::string> &ServerConfig::allowed_cgi() const
{
        return _allowed_cgi;
}
const size_t ServerConfig::body_size() const { return _body_size; }
const int ServerConfig::port() const { return _port; }
const bool ServerConfig::do_directory_listing() const
{
        return _do_directory_listing;
}
const bool ServerConfig::do_post() const { return _methods.at("POST"); }
const bool ServerConfig::do_get() const { return _methods.at("GET"); }
const bool ServerConfig::do_upload() const { return !_upload_dir.empty(); }
const std::string &ServerConfig::upload_dir() const { return _upload_dir; }

std::ostream &operator<<(std::ostream &stream, const ServerConfig &elem)
{
        stream << "server_name: " << elem.server_name() << "\n";
        stream << "host: " << elem.host() << "\n";
        stream << "root: " << elem.root() << "\n";
        stream << "index_page: " << elem.index_page() << "\n";
        stream << "error_pages : {\n";
        for (std::map<int, std::string>::const_iterator iter =
                 elem.error_pages().begin();
             iter != elem.error_pages().end(); ++iter) {
                stream << "    " << iter->first << " => " << iter->second
                       << "\n";
        }
        stream << "}\n";
        stream << "locations : {\n";
        for (std::vector<ServerConfig::Location>::const_iterator iter =
                 elem.locations().begin();
             iter != elem.locations().end(); ++iter) {
                stream << "    " << iter->root() << " {\n";
                stream << "        alias: " << iter->alias() << "\n";
                stream << "        do_get: " << (iter->do_get() ? "yes" : "no")
                       << "\n";
                stream << "        do_post: "
                       << (iter->do_post() ? "yes" : "no") << "\n";
        }
        stream << "}\n";
        stream << "allowed_cgi : {\n";
        for (std::vector<std::string>::const_iterator iter =
                 elem.allowed_cgi().begin();
             iter != elem.allowed_cgi().end(); ++iter) {
                stream << "    " << *iter << "\n";
        }
        stream << "}\n";
        stream << "body_size: " << elem.body_size() << "\n";
        stream << "port: " << elem.port() << "\n";
        stream << "do_directory_listing: "
               << (elem.do_directory_listing() ? "yes" : "no") << "\n";
        stream << "do_get: " << (elem.do_get() ? "yes" : "no") << "\n";
        stream << "do_post: " << (elem.do_post() ? "yes" : "no") << "\n";
        stream << "do_upload: " << (elem.do_upload() ? "yes" : "no") << "\n";
        stream << "upload_dir: " << elem.upload_dir() << "\n";
        return stream;
}
