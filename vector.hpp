/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 15:27:15 by mleblanc          #+#    #+#             */
/*   Updated: 2022/02/02 18:40:27 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>

#include "iterator.hpp"

namespace ft {
template <typename T, typename Alloc = std::allocator<T> >
class vector {
  public:
    typedef T                                        value_type;
    typedef Alloc                                    allocator_type;
    typedef typename allocator_type::size_type       size_type;
    typedef typename allocator_type::difference_type difference_type;
    typedef value_type&                              reference;
    typedef const value_type&                        const_reference;
    typedef typename allocator_type::pointer         pointer;
    typedef typename allocator_type::const_pointer   const_pointer;
    typedef normal_iterator<pointer, vector>         iterator;
    typedef normal_iterator<const_pointer, vector>   const_iterator;
    typedef ft::reverse_iterator<iterator>           reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>     const_reverse_iterator;

  public:
    vector() : alloc_(allocator_type()), start_(NULL), end_(NULL), end_capacity_(NULL){};
    vector(const vector& other) : alloc_(other.alloc_){};
    explicit vector(const allocator_type& alloc);
    explicit vector(
        size_type count, const T& value = T(), const allocator_type& alloc = allocator_type());
    template <typename It>
    vector(It first, It last, const allocator_type& alloc = allocator_type());

  public:
    allocator_type get_allocator() const { return alloc_; }
    size_type      size() const { return static_cast<size_type>(end_ - start_); }
    size_type      capacity() const { return static_cast<size_type>(end_capacity_ - start_); }

  private:
    allocator_type alloc_;
    pointer        start_;
    pointer        end_;
    pointer        end_capacity_;
};
}
