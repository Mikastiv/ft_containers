/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 16:51:59 by mleblanc          #+#    #+#             */
/*   Updated: 2022/04/14 18:11:27 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "vector.hpp"

namespace ft
{
template <typename T, typename Container = ft::vector<T> >
class stack
{
  public:
    typedef Container container_type;
    typedef typename Container::value_type value_type;
    typedef typename Container::size_type size_type;
    typedef typename Container::reference reference;
    typedef typename Container::const_reference const_reference;

  public:
    explicit stack(const container_type& cont = container_type())
        : c(cont)
    {
    }

    stack(const stack& other)
        : c(other.c)
    {
    }

    ~stack()
    {
    }

    stack& operator=(const stack& other)
    {
        c = other.c;
        return *this;
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

  private:
    container_type c;
};
} // namespace ft
