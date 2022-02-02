/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 12:33:36 by mleblanc          #+#    #+#             */
/*   Updated: 2022/02/02 13:34:03 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstddef>

namespace ft {
struct random_access_iterator_tag {};

template <typename It>
struct iterator_traits {
    typedef typename It::iterator_category iterator_category;
    typedef typename It::value_type        value_type;
    typedef typename It::difference_type   difference_type;
    typedef typename It::pointer           pointer;
    typedef typename It::reference         reference;
};

template <typename It>
struct iterator_traits<It*> {
    typedef random_access_iterator_tag iterator_category;
    typedef It                         value_type;
    typedef ptrdiff_t                  difference_type;
    typedef value_type*                pointer;
    typedef value_type&                reference;
};

template <typename It>
struct iterator_traits<const It*> {
    typedef random_access_iterator_tag iterator_category;
    typedef It                         value_type;
    typedef ptrdiff_t                  difference_type;
    typedef const value_type*          pointer;
    typedef const value_type&          reference;
};

template <typename It>
class normal_iterator {
  protected:
    typedef iterator_traits<It> traits_type;

  public:
    typedef It                                      iterator_type;
    typedef typename traits_type::iterator_category iterator_category;
    typedef typename traits_type::value_type        value_type;
    typedef typename traits_type::difference_type   difference_type;
    typedef typename traits_type::reference         reference;
    typedef typename traits_type::pointer           pointer;

  public:
    normal_iterator() : elem_(iterator_type()) {}
    explicit normal_iterator(const iterator_type& it) : elem_(it) {}

  public:
    reference        operator*() const { return *elem_; }
    pointer          operator->() const { return elem_; }
    normal_iterator& operator++() {
        ++elem_;
        return *this;
    }
    normal_iterator  operator++(int) { return normal_iterator(elem_++); }
    normal_iterator& operator--() {
        --elem_;
        return *this;
    }
    normal_iterator  operator--(int) { return normal_iterator(elem_--); }
    reference        operator[](difference_type n) { return elem_[n]; }
    normal_iterator& operator+=(difference_type n) {
        elem_ += n;
        return *this;
    }
    normal_iterator  operator+(difference_type n) { return normal_iterator(elem_ + n); }
    normal_iterator& operator-=(difference_type n) {
        elem_ -= n;
        return *this;
    }
    normal_iterator      operator-(difference_type n) { return normal_iterator(elem_ - n); }
    const iterator_type& base() const { return elem_; }

  protected:
    It elem_;
};
}
