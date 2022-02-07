/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 17:59:12 by mleblanc          #+#    #+#             */
/*   Updated: 2022/02/07 17:49:05 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft {

template <bool B, typename T = void>
struct enable_if {};

template <typename T>
struct enable_if<true, T> {
    typedef T type;
};

template <typename T, T v>
struct integral_constant {
    typedef T                 value_type;
    typedef integral_constant type;

    static const T value = v;

                     operator value_type() const { return value; }
    const value_type operator()() const { return value; }
};

typedef integral_constant<bool, true>  true_type;
typedef integral_constant<bool, false> false_type;

template <typename>
struct is_integral : public false_type {};

template <>
struct is_integral<bool> : public true_type {};

template <>
struct is_integral<char> : public true_type {};

template <>
struct is_integral<signed char> : public true_type {};

template <>
struct is_integral<short int> : public true_type {};

template <>
struct is_integral<int> : public true_type {};

template <>
struct is_integral<long int> : public true_type {};

template <>
struct is_integral<unsigned char> : public true_type {};

template <>
struct is_integral<unsigned short int> : public true_type {};

template <>
struct is_integral<unsigned int> : public true_type {};

template <>
struct is_integral<unsigned long int> : public true_type {};

template <typename T, typename U>
struct is_same : public false_type {};

template <typename T>
struct is_same<T, T> : public true_type {};

template <typename T>
struct void_t {
    typedef T type;
};

}
