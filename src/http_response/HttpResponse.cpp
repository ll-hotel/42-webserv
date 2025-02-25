/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpResponse.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:11:31 by ll-hotel          #+#    #+#             */
/*   Updated: 2025/01/15 17:48:49 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv/HttpResponse.hpp"
#include "webserv/HttpRequest.hpp"
#include <cerrno>
#include <fstream>
#include <sstream>
#include <string>
#include <sys/stat.h>

HttpResponse::HttpResponse() { _status_code = HTTP_ERROR_NOT_FOUND; }

HttpResponse::HttpResponse(const HttpRequest &request)
{
        if (request.version() != "HTTP/1.1\r")
                _status_code = SERVER_ERROR_HTTP_VERSION_NOT_SUPPORTED;
        else if (request.method() != "GET" && request.method() != "POST")
                _status_code = HTTP_ERROR_METHOD_NOT_ALLOWED;
        else {
                std::string filename = "resources" + request.resource();
                struct stat file_stat = {0};
                if (::stat(filename.c_str(), &file_stat)) {
                        switch (errno) {
                        case ENOENT:
                                _status_code = HTTP_ERROR_NOT_FOUND;
                                break;
                        case EACCES:
                        case EPERM:
                                _status_code = HTTP_ERROR_FORBIDDEN;
                                break;
                        case EISDIR:
                                _status_code = HTTP_ERROR_BAD_REQUEST;
                                break;
                        case ENAMETOOLONG:
                                _status_code = HTTP_ERROR_REQUEST_URI_TOO_LONG;
                                break;
                        case ENOSPC:
                                _status_code =
                                        SERVER_ERROR_INSUFFICIENT_STORAGE;
                                break;
                        case ETIMEDOUT:
                                _status_code = HTTP_ERROR_TIMEOUT;
                                break;
                        case EIO:
                        case ENOMEM:
                        case ESTALE:
                        default:
                                _status_code =
                                        SERVER_ERROR_INTERNAL_SERVER_ERROR;
                                break;
                        }
                        return;
                }
                if (S_ISDIR(file_stat.st_mode)) {
                        _status_code = HTTP_ERROR_NOT_FOUND;
                } else {
                        _status_code = SUCCESS_OK;
                        _file = filename;
                }
        }
}

HttpResponse::HttpResponse(const HttpResponse &other)
{
        _status_code = other._status_code;
        _file = other._file;
}

HttpResponse &HttpResponse::operator=(const HttpResponse &other)
{
        _status_code = other._status_code;
        _file = other._file;
        return *this;
}

HttpResponse::~HttpResponse() {}

static std::string read_file(const std::string &path)
{
        std::ifstream file_stream(path.c_str());
        std::string content;

        if (file_stream.is_open()) {
                std::getline(file_stream, content, '\0');
        }
        return content;
}

std::string create_status_line(t_status_code code)
{
        std::string status_line = "HTTP/1.1";
        status_line += ' ';
        {
                std::stringstream strs;
                std::string str_code;
                strs << code;
                strs >> str_code;
                status_line += str_code;
        }
        status_line += ' ';
        status_line += status_table(code);
        status_line += "\r\n";
        return status_line;
}

std::string HttpResponse::generate()
{
        std::string str;

        // Status line
        str += create_status_line(_status_code);
        // Response headers
        str += "Server: webserv\r\n";
        // Representation headers
        str += "Content-Type: text/html\r\n";
        // Empty line
        str += "\r\n";
        // Response body
        if (_status_code == SUCCESS_OK)
                str += read_file(_file);
        switch (_status_code) {
        case HTTP_ERROR_NOT_FOUND:
                str += read_file("resources/error_pages/404.html");
                break;
        default:
                break;
        }
        return str;
}
