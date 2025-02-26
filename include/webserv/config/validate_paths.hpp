/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_paths.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:07:02 by ll-hotel          #+#    #+#             */
/*   Updated: 2025/02/26 11:23:04 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>

bool is_directory(const std::string &path);
bool is_file(const std::string &path);
bool is_valid_path(const std::string &path);
