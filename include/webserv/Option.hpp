/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Option.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:41:32 by ll-hotel          #+#    #+#             */
/*   Updated: 2025/02/24 16:08:32 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <cstring>

template <typename T> class Option
{
public:
        Option() : _value() { std::memset(&_value, 0, sizeof(_value)); }
        Option(const T &value) : _value(value) {}
        Option &operator=(const Option &other)
        {
                _value = other._value;
                return *this;
        }
        ~Option() {}
        bool is_some() const
        {
                static const char zeroed[sizeof(_value)] = {0};
                return std::memcmp(&_value, zeroed, sizeof(zeroed)) != 0;
        }
        T &value() { return _value; }
        const T &value() const { return _value; }

private:
        T _value;
};
