/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 21:34:20 by gcros             #+#    #+#             */
/*   Updated: 2024/12/06 17:35:54 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_HPP
# define SOCKET_HPP

#include <netdb.h>
#include <string>
#include "Client.hpp"

# define CLIENT_QUEUE 100
# define DEFAULT_SERVICE "127.0.0.1"

/**
 * @brief simple IPv4 TCP socket wrapper
 */
class Socket
{
public :

	Socket();
	Socket(int port);
	~Socket();

	/**
	 * @brief create the socket connection
	 * @returns 0 if success, 1 if fail
	 */
	int	create();
	Client	get_client();

private :
	int		_fd;
	int		_port;
	struct addrinfo *_addrinfo;
	
	Socket(const Socket &socket);
	Socket &operator=(const Socket &socket);
};

#endif