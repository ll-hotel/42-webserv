/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Worker.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:43:24 by gcros             #+#    #+#             */
/*   Updated: 2024/12/03 20:08:26 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORKER_HPP
# define WORKER_HPP

class Worker
{
public:
/*                                     constructor                            */

	Worker();
	~Worker();
	Worker(Worker &worker) = delete;
	Worker&	operator=(Worker &worker) = delete;
};

#endif