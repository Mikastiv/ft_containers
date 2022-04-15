/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 16:56:07 by mleblanc          #+#    #+#             */
/*   Updated: 2022/04/15 18:13:30 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{
template <typename T1, typename T2>
struct pair {
    T1 first;
    T2 second;

    pair()
        : first(),
          second()
    {
    }

    pair(const T1& x, const T2& y)
        : first(x),
          second(y)
    {
    }

    template <class U1, class U2>
    pair(const pair<U1, U2>& other)
        : first(other.first),
          second(other.second)
    {
    }

    pair(const pair& other)
        : first(other.first),
          second(other.second)
    {
    }

    pair& operator=(const pair& other)
    {
        first = other.first;
        second = other.second;
        return *this;
    }
};

template <typename T1, typename T2>
pair<T1, T2> make_pair(T1 x, T2 y)
{
    return pair<T1, T2>(x, y);
}

template <typename InputIt1, typename InputIt2>
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
{
    for (; first1 != last1; ++first1, (void)++first2) {
        if (!(*first1 == *first2)) {
            return false;
        }
    }
    return true;
}

template <typename InputIt1, typename InputIt2, typename BinaryPredicate>
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p)
{
    for (; first1 != last1; ++first1, (void)++first2) {
        if (!p(*first1, *first2)) {
            return false;
        }
    }
    return true;
}

template <typename InputIt1, typename InputIt2>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
{
}

template <typename InputIt1, typename InputIt2, typename Compare>
bool lexicographical_compare(
    InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp)
{
}
} // namespace ft
