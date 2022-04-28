/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 17:39:51 by mleblanc          #+#    #+#             */
/*   Updated: 2022/04/28 18:18:51 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "type_traits.hpp"

namespace ft
{
template <typename It, typename Container>
class normal_iterator
{
//clang-format off
public:
    typedef It                                              iterator_type;
    typedef typename iterator_traits<It>::iterator_category iterator_category;
    typedef typename iterator_traits<It>::value_type        value_type;
    typedef typename iterator_traits<It>::difference_type   difference_type;
    typedef typename iterator_traits<It>::reference         reference;
    typedef typename iterator_traits<It>::pointer           pointer;
//clang-format on

public:
    normal_iterator()
        : elem_(iterator_type())
    {
    }

    explicit normal_iterator(const iterator_type& it)
        : elem_(it)
    {
    }

    template <typename Iter>
    normal_iterator(const normal_iterator<
                    Iter, typename enable_if<is_same<Iter, typename Container::pointer>::value,
                                             Container>::type>& it)
        : elem_(it.base())
    {
    }

    ~normal_iterator(){};

    normal_iterator& operator=(const normal_iterator& other)
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

    normal_iterator& operator++()
    {
        ++elem_;
        return *this;
    }

    normal_iterator operator++(int)
    {
        return normal_iterator(elem_++);
    }

    normal_iterator& operator--()
    {
        --elem_;
        return *this;
    }

    normal_iterator operator--(int)
    {
        return normal_iterator(elem_--);
    }

    reference operator[](difference_type n)
    {
        return *(elem_ + n);
    }

    normal_iterator& operator+=(difference_type n)
    {
        elem_ += n;
        return *this;
    }

    normal_iterator operator+(difference_type n) const
    {
        return normal_iterator(elem_ + n);
    }

    normal_iterator& operator-=(difference_type n)
    {
        elem_ -= n;
        return *this;
    }

    normal_iterator operator-(difference_type n) const
    {
        return normal_iterator(elem_ - n);
    }

protected:
    It elem_;
};

template <typename ItL, typename ItR, typename Container>
inline bool operator==(const normal_iterator<ItL, Container>& lhs,
                       const normal_iterator<ItR, Container>& rhs)
{
    return lhs.base() == rhs.base();
}

template <typename It, typename Container>
inline bool operator==(const normal_iterator<It, Container>& lhs,
                       const normal_iterator<It, Container>& rhs)
{
    return lhs.base() == rhs.base();
}

template <typename ItL, typename ItR, typename Container>
inline bool operator!=(const normal_iterator<ItL, Container>& lhs,
                       const normal_iterator<ItR, Container>& rhs)
{
    return lhs.base() != rhs.base();
}

template <typename It, typename Container>
inline bool operator!=(const normal_iterator<It, Container>& lhs,
                       const normal_iterator<It, Container>& rhs)
{
    return lhs.base() != rhs.base();
}

template <typename ItL, typename ItR, typename Container>
inline bool operator>(const normal_iterator<ItL, Container>& lhs,
                      const normal_iterator<ItR, Container>& rhs)
{
    return lhs.base() > rhs.base();
}

template <typename It, typename Container>
inline bool operator>(const normal_iterator<It, Container>& lhs,
                      const normal_iterator<It, Container>& rhs)
{
    return lhs.base() > rhs.base();
}

template <typename ItL, typename ItR, typename Container>
inline bool operator<(const normal_iterator<ItL, Container>& lhs,
                      const normal_iterator<ItR, Container>& rhs)
{
    return lhs.base() < rhs.base();
}

template <typename It, typename Container>
inline bool operator<(const normal_iterator<It, Container>& lhs,
                      const normal_iterator<It, Container>& rhs)
{
    return lhs.base() < rhs.base();
}

template <typename ItL, typename ItR, typename Container>
inline bool operator>=(const normal_iterator<ItL, Container>& lhs,
                       const normal_iterator<ItR, Container>& rhs)
{
    return lhs.base() >= rhs.base();
}

template <typename It, typename Container>
inline bool operator>=(const normal_iterator<It, Container>& lhs,
                       const normal_iterator<It, Container>& rhs)
{
    return lhs.base() >= rhs.base();
}

template <typename ItL, typename ItR, typename Container>
inline bool operator<=(const normal_iterator<ItL, Container>& lhs,
                       const normal_iterator<ItR, Container>& rhs)
{
    return lhs.base() <= rhs.base();
}

template <typename It, typename Container>
inline bool operator<=(const normal_iterator<It, Container>& lhs,
                       const normal_iterator<It, Container>& rhs)
{
    return lhs.base() <= rhs.base();
}

template <typename ItL, typename ItR, typename Container>
inline typename normal_iterator<ItL, Container>::difference_type
operator-(const normal_iterator<ItL, Container>& lhs, const normal_iterator<ItR, Container>& rhs)
{
    return lhs.base() - rhs.base();
}

template <typename It, typename Container>
inline typename normal_iterator<It, Container>::difference_type
operator-(const normal_iterator<It, Container>& lhs, const normal_iterator<It, Container>& rhs)
{
    return lhs.base() - rhs.base();
}

template <typename It, typename Container>
inline normal_iterator<It, Container>
operator+(typename normal_iterator<It, Container>::difference_type n,
          const normal_iterator<It, Container>& it)
{
    return normal_iterator<It, Container>(it.base() + n);
}
} // namespace ft
