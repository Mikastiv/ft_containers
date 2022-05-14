/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 17:39:51 by mleblanc          #+#    #+#             */
/*   Updated: 2022/05/14 15:56:26 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterator.hpp"

namespace ft
{
template <typename It, typename Container>
class vector_iterator
{
public:
    // clang-format off
    typedef It                                              iterator_type;
    typedef typename iterator_traits<It>::iterator_category iterator_category;
    typedef typename iterator_traits<It>::value_type        value_type;
    typedef typename iterator_traits<It>::difference_type   difference_type;
    typedef typename iterator_traits<It>::reference         reference;
    typedef typename iterator_traits<It>::pointer           pointer;
    // clang-format on

public:
    vector_iterator()
        : elem_(iterator_type())
    {
    }

    explicit vector_iterator(const iterator_type& it)
        : elem_(it)
    {
    }

    template <typename Iter>
    vector_iterator(const vector_iterator<
                    Iter, typename enable_if<is_same<Iter, typename Container::pointer>::value,
                                             Container>::type>& it)
        : elem_(it.base())
    {
    }

    ~vector_iterator(){};

    vector_iterator& operator=(const vector_iterator& other)
    {
        elem_ = other.elem_;
        return *this;
    }

public:
    const iterator_type& base() const
    {
        return elem_;
    }

    reference operator*() const
    {
        return *elem_;
    }

    pointer operator->() const
    {
        return elem_;
    }

    vector_iterator& operator++()
    {
        ++elem_;
        return *this;
    }

    vector_iterator operator++(int)
    {
        return vector_iterator(elem_++);
    }

    vector_iterator& operator--()
    {
        --elem_;
        return *this;
    }

    vector_iterator operator--(int)
    {
        return vector_iterator(elem_--);
    }

    reference operator[](difference_type n)
    {
        return *(elem_ + n);
    }

    vector_iterator& operator+=(difference_type n)
    {
        elem_ += n;
        return *this;
    }

    vector_iterator operator+(difference_type n) const
    {
        return vector_iterator(elem_ + n);
    }

    vector_iterator& operator-=(difference_type n)
    {
        elem_ -= n;
        return *this;
    }

    vector_iterator operator-(difference_type n) const
    {
        return vector_iterator(elem_ - n);
    }

private:
    It elem_;
};

template <typename ItL, typename ItR, typename Container>
inline bool operator==(const vector_iterator<ItL, Container>& lhs,
                       const vector_iterator<ItR, Container>& rhs)
{
    return lhs.base() == rhs.base();
}

template <typename It, typename Container>
inline bool operator==(const vector_iterator<It, Container>& lhs,
                       const vector_iterator<It, Container>& rhs)
{
    return lhs.base() == rhs.base();
}

template <typename ItL, typename ItR, typename Container>
inline bool operator!=(const vector_iterator<ItL, Container>& lhs,
                       const vector_iterator<ItR, Container>& rhs)
{
    return lhs.base() != rhs.base();
}

template <typename It, typename Container>
inline bool operator!=(const vector_iterator<It, Container>& lhs,
                       const vector_iterator<It, Container>& rhs)
{
    return lhs.base() != rhs.base();
}

template <typename ItL, typename ItR, typename Container>
inline bool operator>(const vector_iterator<ItL, Container>& lhs,
                      const vector_iterator<ItR, Container>& rhs)
{
    return lhs.base() > rhs.base();
}

template <typename It, typename Container>
inline bool operator>(const vector_iterator<It, Container>& lhs,
                      const vector_iterator<It, Container>& rhs)
{
    return lhs.base() > rhs.base();
}

template <typename ItL, typename ItR, typename Container>
inline bool operator<(const vector_iterator<ItL, Container>& lhs,
                      const vector_iterator<ItR, Container>& rhs)
{
    return lhs.base() < rhs.base();
}

template <typename It, typename Container>
inline bool operator<(const vector_iterator<It, Container>& lhs,
                      const vector_iterator<It, Container>& rhs)
{
    return lhs.base() < rhs.base();
}

template <typename ItL, typename ItR, typename Container>
inline bool operator>=(const vector_iterator<ItL, Container>& lhs,
                       const vector_iterator<ItR, Container>& rhs)
{
    return lhs.base() >= rhs.base();
}

template <typename It, typename Container>
inline bool operator>=(const vector_iterator<It, Container>& lhs,
                       const vector_iterator<It, Container>& rhs)
{
    return lhs.base() >= rhs.base();
}

template <typename ItL, typename ItR, typename Container>
inline bool operator<=(const vector_iterator<ItL, Container>& lhs,
                       const vector_iterator<ItR, Container>& rhs)
{
    return lhs.base() <= rhs.base();
}

template <typename It, typename Container>
inline bool operator<=(const vector_iterator<It, Container>& lhs,
                       const vector_iterator<It, Container>& rhs)
{
    return lhs.base() <= rhs.base();
}

template <typename ItL, typename ItR, typename Container>
inline typename vector_iterator<ItL, Container>::difference_type
operator-(const vector_iterator<ItL, Container>& lhs, const vector_iterator<ItR, Container>& rhs)
{
    return lhs.base() - rhs.base();
}

template <typename It, typename Container>
inline typename vector_iterator<It, Container>::difference_type
operator-(const vector_iterator<It, Container>& lhs, const vector_iterator<It, Container>& rhs)
{
    return lhs.base() - rhs.base();
}

template <typename It, typename Container>
inline vector_iterator<It, Container>
operator+(typename vector_iterator<It, Container>::difference_type n,
          const vector_iterator<It, Container>& it)
{
    return vector_iterator<It, Container>(it.base() + n);
}
} // namespace ft
