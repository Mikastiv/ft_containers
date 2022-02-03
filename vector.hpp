/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 15:27:15 by mleblanc          #+#    #+#             */
/*   Updated: 2022/02/02 23:29:10 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>
#include <stdexcept>

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
    vector() : start_(), end_(), end_capacity_(){};
    vector(const vector& other){};
    explicit vector(const allocator_type& alloc);
    explicit vector(
        size_type count, const T& value = T(), const allocator_type& alloc = allocator_type());
    template <typename InputIt>
    vector(InputIt first, InputIt last, const allocator_type& alloc = allocator_type());
    ~vector() { allocator_type().deallocate(data(), capacity()); }

public:
    template <typename InputIt>
    void           assign(InputIt first, InputIt last) {}
    void           assign(size_type count, const T& value) {}
    allocator_type get_allocator() const { return allocator_type(); }

    reference       at(size_type pos) {}
    const_reference at(size_type pos) const {}
    reference       operator[](size_type pos) { return *(start_ + pos); }
    const_reference operator[](size_type pos) const { return *(start_ + pos); }
    reference       front() { return *begin(); }
    const_reference front() const { return *begin(); }
    reference       back() { return *(end() - 1); }
    const_reference back() const { return *(end() - 1); }
    pointer         data() { return start_; }
    const_pointer   data() const { return start_; }

    iterator               begin() { return iterator(start_); }
    const_iterator         begin() const { return const_iterator(start_); }
    iterator               end() { return iterator(end_); }
    const_iterator         end() const { return const_iterator(end_); }
    reverse_iterator       rbegin() { return reverse_iterator(end()); }
    const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
    reverse_iterator       rend() { return reverse_iterator(begin()); }
    const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

    bool      empty() const { return begin() == end(); }
    size_type size() const { return static_cast<size_type>(end_ - start_); }
    size_type max_size() const { return allocator_type().max_size(); }
    void      reserve(size_type new_cap) {}
    size_type capacity() const { return static_cast<size_type>(end_capacity_ - start_); }

    template <class InputIt>
    void     insert(iterator pos, InputIt first, InputIt last) {}
    iterator insert(iterator pos, const T& value) {}
    void     insert(iterator pos, size_type count, const T& value) {}
    void     clear() {}
    iterator erase(iterator pos) {}
    iterator erase(iterator first, iterator last) {}
    void     push_back(const T& value) {}
    void     pop_back() {}
    void     resize(size_type count, T value = T()) {}
    void     swap(vector& other) {}

private:
    bool      should_grow() const { return end_ == end_capacity_; }
    size_type calculate_growth() const {
        const size_type old_cap = capacity();
        const size_type max = max_size();

        if (max / 2 < old_cap) {
            return max;
        }

        return old_cap * 2;
    }
    void grow() {
        const size_type old_cap = capacity();
        if (old_cap == max_size()) {
            throw std::length_error("vector is at max size and can't grow");
        }

        const size_type new_cap = calculate_growth();
        allocator_type  alloc = get_allocator();
        const_pointer   new_start = alloc.allocate(new_cap);
    }
    void shrink(size_type new_cap) {}

private:
    pointer start_;
    pointer end_;
    pointer end_capacity_;
};
}
