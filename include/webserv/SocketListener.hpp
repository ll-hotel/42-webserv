/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketListener.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 18:02:10 by gcros             #+#    #+#             */
/*   Updated: 2025/01/31 17:09:44 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKETLISTENER_HPP
#define SOCKETLISTENER_HPP
#include <stdint.h>
#include <string>
#include <sys/socket.h>

#define DEFAULT_PORT 80
#define DEFAULT_FAMILY AF_INET
#define DEFAULT_ADDR INADDR_ANY
#define DEFAULT_STREAM SOCK_STREAM
#define DEFAULT_LIMIT_QUEUE 256

class ClientSocket
{
private:
        struct sockaddr _addr;
        socklen_t _addr_len;
        int _fd;

public:
        ClientSocket(int fd);
        ~ClientSocket();

        const struct sockaddr &addr() const;
        socklen_t addr_len() const;
        int fd() const;

        std::string recv();
        ssize_t send(const std::string &buf);
};

class SocketListener
{
public:
        SocketListener(int port);
        ~SocketListener();
        /*                                     utils */
        ClientSocket *accept();
        /*                                     get/set */
        bool has_failed() const;
        int32_t getFd() const;
        bool poll() const;

private:
        SocketListener();
        SocketListener(const SocketListener &);
        /*                                     utils */
        void create();
        void bind(int port);
        void listen();

        bool _failed;
        uint16_t _port;
        int32_t _fd;
        int32_t _limit_queue;
};

#endif
