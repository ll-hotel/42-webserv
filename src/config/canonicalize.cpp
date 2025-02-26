/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canonicalize.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:21:08 by ll-hotel          #+#    #+#             */
/*   Updated: 2025/02/26 13:37:01 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <vector>

std::vector<std::string> split(const std::string &str, char c)
{
	std::vector<std::string> str_slices;
	for (size_t i = 0; i < str.size(); i += 1) {
		size_t c_pos = str.find(c, i);
		if (c_pos == std::string::npos)
			c_pos = str.size();
		std::string path(str.begin() + i, str.begin() + c_pos);
		str_slices.push_back(path);
		i = c_pos;
	}
	return str_slices;
}

std::string join_with(const std::vector<std::string> &strs,
		      const std::string &joint)
{
	std::string new_str;
	size_t i;
	for (i = 0; i + 1 < strs.size(); i += 1)
		new_str += strs[i] + joint;
	if (strs.size() > 0)
		new_str += strs[i];
	return new_str;
}

std::string canonicalize(const std::string &str)
{
	std::vector<std::string> paths(split(str, '/'));

	for (size_t i = 0; i < paths.size(); i += 1) {
		if (paths[i].empty() || paths[i] == ".") {
			paths.erase(paths.begin() + i);
			i -= 1;
		} else if (paths[i] == "..") {
			if (i > 0) {
				i -= 1;
				paths.erase(paths.begin() + i);
				paths.erase(paths.begin() + i);
			}
		}
	}
	return join_with(paths, "/");
}
