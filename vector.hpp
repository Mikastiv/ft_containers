/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 15:27:15 by mleblanc          #+#    #+#             */
/*   Updated: 2022/02/01 17:01:47 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>

namespace ft {
template <typename T, typename Alloc = std::allocator<T> >
class vector {
public:
    typedef T      value_type;
    typedef Alloc  allocator_type;
    typedef size_t size_type;

public:
    vector() : alloc_(Alloc()), size_(0), capacity_(0), elems_(NULL){};
    vector(const vector& other)
        : alloc_(other.alloc_), size_(other.size_), capacity_(other.capacity_) {
        elems = alloc_.allocate(sizeof(T) * capacity_);
    };
    explicit vector(const Alloc& alloc);
    explicit vector(size_t count, const T& value = T(), const Alloc& alloc = Alloc());
    template <template It>
    vector(It first, It last, const Alloc& alloc = Alloc());

public:
    size_t capacity() const { return capacity_; }

private:
    Alloc  alloc_;
    size_t size_;
    size_t capacity_;
    T*     elems_;
};
}
