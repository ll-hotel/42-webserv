/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canonicalize.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:22:24 by ll-hotel          #+#    #+#             */
/*   Updated: 2025/02/26 13:22:44 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <vector>

std::vector<std::string> split(const std::string &str, char c);
std::string join_with(const std::vector<std::string> &strs,
		      const std::string &joint);
std::string canonicalize(const std::string &str);
