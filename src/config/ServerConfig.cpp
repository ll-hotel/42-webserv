/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerConfig.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 10:03:55 by ll-hotel          #+#    #+#             */
/*   Updated: 2025/02/25 16:06:06 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv/ServerConfig.hpp"
#include "webserv/Exception.hpp"
#include "webserv/config/use_parameter.hpp"
#include <cstdlib>
#include <string>
#include <utility>
#include <vector>

enum ServerConfigIdentifier {
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

static ServerConfigIdentifier which_identifier(const Token &token)
{
        static std::map<std::string, ServerConfigIdentifier> key_list;

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
        std::map<std::string, ServerConfigIdentifier>::const_iterator key =
                key_list.find(token.value);
        if (key != key_list.end())
                return key->second;
        return INVALID;
}

ServerConfig::ServerConfig(const std::vector<Parameter> &parameters)
{
        *this = ServerConfig();
        for (size_t i = 0; i < parameters.size(); i += 1) {
                const Parameter &parameter = parameters[i];
                if (parameter.second.empty())
                        WS_THROW("missing argument for key `" +
                                 parameter.first + "'");
                this->setVar(parameter);
        }
}

void ServerConfig::setVar(const Parameter &parameter)
{
        switch (which_identifier(parameter.first)) {
        case INVALID:
                WS_THROW("invalid key `" + parameter.first + "'");
        case SERVER_NAME:
                change_server_name(parameter, &m_serverName);
                break;
        case HOST:
                change_host(parameter, &m_host);
                break;
        case ROOT:
                change_root(parameter, &m_root);
                break;
        case INDEX_PAGE:
                change_index_page(parameter, &m_indexPage);
                break;
        case ERROR_PAGE:
                change_error_page(parameter, &m_errorPages);
                break;
        case LOCATION:
                change_location(parameter, &m_locations);
                break;
        case CGI:
                change_cgi(parameter, &m_allowedCgi);
                break;
        case BODY_SIZE:
                change_body_size(parameter, &m_bodySize);
                break;
        case PORT:
                change_port(parameter, &m_port);
                break;
        case DIRECTORY_LISTING:
                change_directory_listing(parameter, &m_doDirectoryListing);
                break;
        case METHODS:
                change_methods(parameter, &m_methods);
                break;
        case UPLOAD_DIR:
                change_upload_dir(parameter, &m_uploadDir);
                break;
        }
}

ServerConfig::ServerConfig()
{
        m_serverName = "server";
        m_host = "127.0.0.1";
        m_root = ".";
        m_indexPage = "index.html";
        // _error_pages;
        // _locations;
        // _allowed_cgi;
        m_methods["POST"] = false;
        m_methods["GET"] = false;
        m_bodySize = 1024;
        m_port = 8080;
        m_doDirectoryListing = false;
        m_uploadDir = "";
}

ServerConfig::ServerConfig(const ServerConfig &other) { *this = other; }

ServerConfig &ServerConfig::operator=(const ServerConfig &other)
{
        m_serverName = other.m_serverName;
        m_host = other.m_host;
        m_root = other.m_root;
        m_indexPage = other.m_indexPage;
        m_errorPages = other.m_errorPages;
        m_locations = other.m_locations;
        m_allowedCgi = other.m_allowedCgi;
        m_methods = other.m_methods;
        m_bodySize = other.m_bodySize;
        m_port = other.m_port;
        m_doDirectoryListing = other.m_doDirectoryListing;
        m_uploadDir = other.m_uploadDir;
        return *this;
}

ServerConfig::~ServerConfig() {}

const std::string &ServerConfig::serverName() const { return m_serverName; }
const std::string &ServerConfig::host() const { return m_host; }
const std::string &ServerConfig::root() const { return m_root; }
const std::string &ServerConfig::indexPage() const { return m_indexPage; }
const std::map<int, std::string> &ServerConfig::errorPages() const
{
        return m_errorPages;
}
const std::vector<ServerConfig::Location> &ServerConfig::locations() const
{
        return m_locations;
}
const std::vector<std::string> &ServerConfig::allowedCgi() const
{
        return m_allowedCgi;
}
size_t ServerConfig::bodySize() const { return m_bodySize; }
int ServerConfig::port() const { return m_port; }
bool ServerConfig::doDirectoryListing() const
{
        return m_doDirectoryListing;
}
bool ServerConfig::doPost() const { return m_methods.at("POST"); }
bool ServerConfig::doGet() const { return m_methods.at("GET"); }
bool ServerConfig::doUpload() const { return !m_uploadDir.empty(); }
const std::string &ServerConfig::uploadDir() const { return m_uploadDir; }

std::ostream &operator<<(std::ostream &stream, const ServerConfig &elem)
{
        stream << "server_name: " << elem.serverName() << "\n";
        stream << "host: " << elem.host() << "\n";
        stream << "root: " << elem.root() << "\n";
        stream << "index_page: " << elem.indexPage() << "\n";
        stream << "error_pages : {\n";
        for (std::map<int, std::string>::const_iterator iter =
                     elem.errorPages().begin();
             iter != elem.errorPages().end(); ++iter) {
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
                stream << "        do_get: " << (iter->doGet() ? "yes" : "no")
                       << "\n";
                stream << "        do_post: "
                       << (iter->doPost() ? "yes" : "no") << "\n";
        }
        stream << "}\n";
        stream << "allowed_cgi : {\n";
        for (std::vector<std::string>::const_iterator iter =
                     elem.allowedCgi().begin();
             iter != elem.allowedCgi().end(); ++iter) {
                stream << "    " << *iter << "\n";
        }
        stream << "}\n";
        stream << "body_size: " << elem.bodySize() << "\n";
        stream << "port: " << elem.port() << "\n";
        stream << "do_directory_listing: "
               << (elem.doDirectoryListing() ? "yes" : "no") << "\n";
        stream << "do_get: " << (elem.doGet() ? "yes" : "no") << "\n";
        stream << "do_post: " << (elem.doPost() ? "yes" : "no") << "\n";
        stream << "do_upload: " << (elem.doUpload() ? "yes" : "no") << "\n";
        stream << "upload_dir: " << elem.uploadDir();
        return stream;
}
