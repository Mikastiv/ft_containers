/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 16:51:59 by mleblanc          #+#    #+#             */
/*   Updated: 2022/04/28 18:24:25 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "vector.hpp"

namespace ft
{
template <typename T, typename Container = vector<T> >
class stack
{
//clang-format off
public:
    typedef Container                                container_type;
    typedef typename container_type::value_type      value_type;
    typedef typename container_type::size_type       size_type;
    typedef typename container_type::reference       reference;
    typedef typename container_type::const_reference const_reference;
//clang-format on

public:
    explicit stack(const container_type& cont = container_type())
        : c(cont)
    {
    }

    stack(const stack& other)
        : c(other.c)
    {
    }

    stack& operator=(const stack& other)
    {
        c = other.c;
        return *this;
    }

    ~stack()
    {
    }

public:
    reference top()
    {
        return c.back();
    }

    const_reference top() const
    {
        return c.back();
    }

    bool empty() const
    {
        return c.empty();
    }

    size_type size() const
    {
        return c.size();
    }

    void push(const value_type& value)
    {
        c.push_back(value);
    }

    void pop()
    {
        c.pop_back();
    }

    template <typename T1, typename C1>
    friend bool operator==(const stack<T1, C1>& lhs, const stack<T1, C1>& rhs);

    template <typename T1, typename C1>
    friend bool operator<(const stack<T1, C1>& lhs, const stack<T1, C1>& rhs);

protected:
    container_type c;
};

template <typename T, typename Container>
inline bool operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
{
    return lhs.c == rhs.c;
}

template <typename T, typename Container>
inline bool operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
{
    return !(lhs == rhs);
}

template <typename T, typename Container>
inline bool operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
{
    return lhs.c < rhs.c;
}

template <typename T, typename Container>
inline bool operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
{
    return !(rhs < lhs);
}

template <typename T, typename Container>
inline bool operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
{
    return rhs < lhs;
}

template <typename T, typename Container>
inline bool operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
{
    return !(lhs < rhs);
}
} // namespace ft
