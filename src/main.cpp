/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 18:40:52 by gcros             #+#    #+#             */
/*   Updated: 2024/12/06 18:04:06 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Socket.hpp"
#include <iostream>

int main(void)
{
	Socket sock(4242);
	Client client;

	if (sock.create())
		return (1);
	client = sock.get_client();
	client.send("hello world");
	return 0;
}
