/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 12:33:36 by mleblanc          #+#    #+#             */
/*   Updated: 2022/04/20 16:20:52 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstddef>
#include <iterator>

#include "type_traits.hpp"

namespace ft
{
template <typename It>
struct iterator_traits {
    typedef typename It::iterator_category iterator_category;
    typedef typename It::value_type value_type;
    typedef typename It::difference_type difference_type;
    typedef typename It::pointer pointer;
    typedef typename It::reference reference;
};

template <typename It>
struct iterator_traits<It*> {
    typedef std::random_access_iterator_tag iterator_category;
    typedef It value_type;
    typedef std::ptrdiff_t difference_type;
    typedef value_type* pointer;
    typedef value_type& reference;
};

template <typename It>
struct iterator_traits<const It*> {
    typedef std::random_access_iterator_tag iterator_category;
    typedef It value_type;
    typedef std::ptrdiff_t difference_type;
    typedef const value_type* pointer;
    typedef const value_type& reference;
};

template <typename It, typename Container>
class normal_iterator
{
  public:
    typedef It iterator_type;
    typedef typename iterator_traits<It>::iterator_category iterator_category;
    typedef typename iterator_traits<It>::value_type value_type;
    typedef typename iterator_traits<It>::difference_type difference_type;
    typedef typename iterator_traits<It>::reference reference;
    typedef typename iterator_traits<It>::pointer pointer;

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

template <typename It>
class reverse_iterator
    : public std::iterator<
          typename iterator_traits<It>::iterator_category, typename iterator_traits<It>::value_type,
          typename iterator_traits<It>::difference_type, typename iterator_traits<It>::pointer,
          typename iterator_traits<It>::reference>
{
  public:
    typedef It iterator_type;
    typedef typename iterator_traits<It>::value_type value_type;
    typedef typename iterator_traits<It>::difference_type difference_type;
    typedef typename iterator_traits<It>::reference reference;
    typedef typename iterator_traits<It>::pointer pointer;

  public:
    reverse_iterator()
        : elem_()
    {
    }

    reverse_iterator(const reverse_iterator& it)
        : elem_(it.elem_)
    {
    }

    explicit reverse_iterator(iterator_type it)
        : elem_(it)
    {
    }

    template <typename Iter>
    reverse_iterator(const reverse_iterator<Iter>& it)
        : elem_(it.base())
    {
    }

    ~reverse_iterator()
    {
    }

    reverse_iterator& operator=(const reverse_iterator& other)
    {
        elem_ = other.elem_;
        return *this;
    }

  public:
    iterator_type base() const
    {
        return elem_;
    }

    reference operator*() const
    {
        It tmp = elem_;
        return *--tmp;
    }

    pointer operator->() const
    {
        return &(operator*());
    }

    reverse_iterator& operator++()
    {
        --elem_;
        return *this;
    }

    reverse_iterator operator++(int)
    {
        return reverse_iterator(elem_--);
    }

    reverse_iterator& operator--()
    {
        ++elem_;
        return *this;
    }

    reverse_iterator operator--(int)
    {
        return reverse_iterator(elem_++);
    }

    reverse_iterator operator+(difference_type n) const
    {
        return reverse_iterator(elem_ - n);
    }

    reverse_iterator& operator+=(difference_type n)
    {
        elem_ -= n;
        return *this;
    }

    reverse_iterator operator-(difference_type n) const
    {
        return reverse_iterator(elem_ + n);
    }

    reverse_iterator& operator-=(difference_type n)
    {
        elem_ += n;
        return *this;
    }

    reference operator[](difference_type n) const
    {
        return *(*this + n);
    }

  protected:
    It elem_;
};

template <typename ItL, typename ItR>
inline bool operator==(const reverse_iterator<ItL>& lhs, const reverse_iterator<ItR>& rhs)
{
    return lhs.base() == rhs.base();
}

template <typename It>
inline bool operator==(const reverse_iterator<It>& lhs, const reverse_iterator<It>& rhs)
{
    return lhs.base() == rhs.base();
}

template <typename ItL, typename ItR>
inline bool operator!=(const reverse_iterator<ItL>& lhs, const reverse_iterator<ItR>& rhs)
{
    return lhs.base() != rhs.base();
}

template <typename It>
inline bool operator!=(const reverse_iterator<It>& lhs, const reverse_iterator<It>& rhs)
{
    return lhs.base() != rhs.base();
}

template <typename ItL, typename ItR>
inline bool operator>(const reverse_iterator<ItL>& lhs, const reverse_iterator<ItR>& rhs)
{
    return lhs.base() < rhs.base();
}

template <typename It>
inline bool operator>(const reverse_iterator<It>& lhs, const reverse_iterator<It>& rhs)
{
    return lhs.base() < rhs.base();
}

template <typename ItL, typename ItR>
inline bool operator<(const reverse_iterator<ItL>& lhs, const reverse_iterator<ItR>& rhs)
{
    return lhs.base() > rhs.base();
}

template <typename It>
inline bool operator<(const reverse_iterator<It>& lhs, const reverse_iterator<It>& rhs)
{
    return lhs.base() > rhs.base();
}

template <typename ItL, typename ItR>
inline bool operator>=(const reverse_iterator<ItL>& lhs, const reverse_iterator<ItR>& rhs)
{
    return lhs.base() <= rhs.base();
}

template <typename It>
inline bool operator>=(const reverse_iterator<It>& lhs, const reverse_iterator<It>& rhs)
{
    return lhs.base() <= rhs.base();
}

template <typename ItL, typename ItR>
inline bool operator<=(const reverse_iterator<ItL>& lhs, const reverse_iterator<ItR>& rhs)
{
    return lhs.base() >= rhs.base();
}

template <typename It>
inline bool operator<=(const reverse_iterator<It>& lhs, const reverse_iterator<It>& rhs)
{
    return lhs.base() >= rhs.base();
}

template <typename ItL, typename ItR>
inline typename reverse_iterator<ItL>::difference_type operator-(const reverse_iterator<ItL>& lhs,
                                                                 const reverse_iterator<ItR>& rhs)
{
    return rhs.base() - lhs.base();
}

template <typename It>
inline typename reverse_iterator<It>::difference_type operator-(const reverse_iterator<It>& lhs,
                                                                const reverse_iterator<It>& rhs)
{
    return rhs.base() - lhs.base();
}

template <typename It>
inline reverse_iterator<It> operator+(typename reverse_iterator<It>::difference_type n,
                                      const reverse_iterator<It>& it)
{
    return reverse_iterator<It>(it.base() - n);
}

} // namespace ft
