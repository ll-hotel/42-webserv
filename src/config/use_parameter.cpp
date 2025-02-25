#include "webserv/use_parameter.hpp"
#include "webserv/Exception.hpp"
#include <cstdlib>

void change_server_name(const Parameter &parameter, std::string *server_name)
{
        if (parameter.second.size() > 1)
                WS_THROW("too many arguments for server_name");
        *server_name = parameter.second[0];
}
void change_host(const Parameter &parameter, std::string *host)
{
        if (parameter.second.size() > 1)
                WS_THROW("too many arguments for host");
        *host = parameter.second[0];
}

void change_root(const Parameter &parameter, std::string *root)
{
        if (parameter.second.size() > 1)
                WS_THROW("too many arguments for root");
        *root = parameter.second[0];
}

void change_index_page(const Parameter &parameter, std::string *index_page)
{
        if (parameter.second.size() > 1)
                WS_THROW("too many arguments for index_page");
        *index_page = parameter.second[0];
}

void change_error_page(const Parameter &parameter,
                       std::map<int, std::string> *error_pages)
{
        if (parameter.second.size() != 2)
                WS_THROW("bad arguments for error_page");
        int code = std::atoi(parameter.second[0].c_str());
        (*error_pages)[code] = parameter.second[1];
}

void change_location(const Parameter &parameter,
                     std::vector<ServerConfig::Location> *locations)
{
        if (parameter.second.size() > 1)
                WS_THROW("too many arguments for location");
        (void)locations;
}

void change_cgi(const Parameter &parameter, std::vector<std::string> *cgi)
{
        if (parameter.second.size() == 0)
                WS_THROW("missing arguments for cgi");
        for (size_t i = 0; i < parameter.second.size(); i += 1)
                cgi->push_back(parameter.second[i]);
}

void change_body_size(const Parameter &parameter, size_t *body_size)
{
        if (parameter.second.size() > 1)
                WS_THROW("too many arguments for body_size");
        *body_size = std::atol(parameter.second[0].c_str());
}

void change_port(const Parameter &parameter, int *port)
{
        if (parameter.second.size() > 1)
                WS_THROW("too many arguments for port");
        *port = std::atoi(parameter.second[0].c_str());
}

void change_directory_listing(const Parameter &parameter,
                              bool *directory_listing)
{
        if (parameter.second.size() > 1)
                WS_THROW("too many arguments for directory_listing");
        *directory_listing = parameter.second[0] == "true" ? true : false;
}

void change_methods(const Parameter &parameter,
                    std::map<std::string, bool> *methods)
{
        if (parameter.second.size() > 1)
                WS_THROW("too many arguments for methods");
        (*methods)[parameter.second[0]] = true;
}

void change_upload_dir(const Parameter &parameter, std::string *upload_dir)
{
        if (parameter.second.size() > 1)
                WS_THROW("too many arguments for updload_dir");
        *upload_dir = parameter.second[0];
}
