/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:45:04 by ll-hotel          #+#    #+#             */
/*   Updated: 2025/01/28 17:53:27 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP
#include "webserv/Config.hpp"

class Server {
private:
	Config _config;
public:
	Server();
	Server(std::ifstream &file);
	Server(const Server &other);
	Server& operator=(const Server &other);
	~Server();

	const Config& configuration() const;
};

#endif /* #ifndef SERVER_HPP */
