/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketListener.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 18:02:10 by gcros             #+#    #+#             */
/*   Updated: 2025/01/08 20:31:27 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKETLISTENER_HPP
# define SOCKETLISTENER_HPP

# include <stdint.h>
# include <sys/socket.h>

# define DEFAULT_PORT		80
# define DEFAULT_FAMILY		AF_INET
# define DEFAULT_ADDR		INADDR_ANY
# define DEFAULT_STREAM		SOCK_STREAM
# define DEFAULT_LIMIT_QUEUE	256

class SocketListener
{
public:
	SocketListener(int port);
	~SocketListener();
/*                                     utils                                  */
	int	accept();
/*                                     get/set                                */
	bool	has_failed() const;
	bool	poll() const;

private:
	SocketListener();
	SocketListener(const SocketListener &);
/*                                     utils                                  */
	void	create();
	void	bind(int port);
	void	listen();

	bool		_failed;
	uint16_t	_port;
	int32_t		_fd;
	int32_t		_limit_queue;
};

#endif
