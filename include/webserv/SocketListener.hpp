/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketListener.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 18:02:10 by gcros             #+#    #+#             */
/*   Updated: 2025/01/08 19:29:24 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKETLISTENER_HPP
# define SOCKETLISTENER_HPP

# include <stdint.h>
# include "webserv/Exception.hpp"
# include <sys/socket.h>

# define DEFAULT_PORT		80
# define DEFAULT_FAMILY		AF_INET
# define DEFAULT_ADDR		INADDR_ANY
# define DEFAULT_STREAM		SOCK_STREAM
# define DEFAULT_LIMIT_QUEUE	256

class SocketListener
{
public:

	static SocketListener	generate(int port);

	SocketListener();
	SocketListener(int port);
	~SocketListener();

/*                                     utils                                  */
	int	accept();
	int	recv();

/*                                     get/set                                */
	
	bool	is_close() const;
	bool	is_fail() const;
	bool	is_bind() const;
	bool	is_waiting() const;
private:
	SocketListener(const SocketListener &);

/*                                     utils                                  */
	int	create();
	int	bind();
	int	listen();
	int	close();

	bool		_close;
	bool		_fail;
	bool		_bind;
	bool		_create;
	bool		_listen;
	uint16_t	_port;
	int32_t		_fd;
	int32_t		_limit_queue;
};

#endif