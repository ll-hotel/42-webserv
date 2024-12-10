/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 18:19:07 by gcros             #+#    #+#             */
/*   Updated: 2024/12/06 17:47:36 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

#include <string>

class Client
{

public :
	Client();
	Client(int fd);
	Client(const Client &client);
	Client &operator=(const Client &client);
	~Client();
	int	send(std::string msg);
	int	getFd();
	
private :
	int	_fd;
};

#endif