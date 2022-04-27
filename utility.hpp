/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 16:56:07 by mleblanc          #+#    #+#             */
/*   Updated: 2022/04/27 15:34:56 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{
template <typename T1, typename T2>
struct pair {
    typedef T1 first_type;
    typedef T2 second_type;

    pair()
        : first(T1()),
          second(T2())
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

    T1 first;
    T2 second;
};

template <typename T1, typename T2>
pair<T1, T2> make_pair(T1 x, T2 y)
{
    return pair<T1, T2>(x, y);
}

template <typename T1, typename T2>
inline bool operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{
    return lhs.first == rhs.first && lhs.second == rhs.second;
}

template <typename T1, typename T2>
inline bool operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{
    return !(lhs == rhs);
}

template <typename T1, typename T2>
inline bool operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{
    return (lhs.first < rhs.first) || (!(lhs.first < rhs.first) && lhs.second < rhs.second);
}

template <typename T1, typename T2>
inline bool operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{
    return !(rhs < lhs);
}

template <typename T1, typename T2>
inline bool operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{
    return rhs < lhs;
}

template <typename T1, typename T2>
inline bool operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{
    return !(lhs < rhs);
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
    for (; first2 != last2; ++first1, (void)++first2) {
        if (first1 == last1 || *first1 < *first2) {
            return true;
        }
        if (*first2 < *first1) {
            return false;
        }
    }
    return false;
}

template <typename InputIt1, typename InputIt2, typename Compare>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2,
                             Compare comp)
{
    for (; first2 != last2; ++first1, (void)++first2) {
        if (first1 == last1 || comp(*first1, *first2)) {
            return true;
        }
        if (comp(*first2, *first1)) {
            return false;
        }
    }
    return false;
}

template <typename Arg1, typename Arg2, typename Result>
struct binary_function {
    typedef Arg1 first_argument_type;
    typedef Arg2 second_argument_type;
    typedef Result result_type;
};

template <typename T>
struct less : binary_function<T, T, bool> {
    bool operator()(const T& lhs, const T& rhs) const
    {
        return lhs < rhs;
    };
};
} // namespace ft
