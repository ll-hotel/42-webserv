/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Option.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:41:32 by ll-hotel          #+#    #+#             */
/*   Updated: 2025/02/25 15:55:02 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <cstring>

template <typename T> class Option
{
public:
        Option() : m_some(false) {}
        Option(const T &value) : m_value(value), m_some(true) {}
        Option &operator=(const Option &other)
        {
                m_value = other.m_value;
		m_some = other.m_some;
                return *this;
        }
        ~Option() {}
        bool is_some() const { return m_some; }
        const T &value() const { return m_value; }

private:
        T m_value;
	bool m_some;
};
