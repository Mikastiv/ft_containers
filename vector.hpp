/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 15:27:15 by mleblanc          #+#    #+#             */
/*   Updated: 2022/03/09 00:31:29 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <algorithm>
#include <memory>
#include <sstream>
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
    vector() : alloc_(), start_(), end_(), end_capacity_() {}
    vector(const vector& other) : alloc_(other.alloc) {
        allocator_type  alloc = get_allocator();
        const size_type cap = other.capacity();
        const size_type s = other.size();
        start_ = alloc.allocate(cap);
        end_ = start_ + s;
        end_capacity_ = start_ + cap;
        construct_range(start_, other.start_, other.end_);
    }
    explicit vector(const allocator_type& alloc)
        : alloc_(alloc), start_(), end_(), end_capacity_() {}
    explicit vector(
        size_type count, const T& value = T(), const allocator_type& alloc = allocator_type())
        : alloc_(alloc) {
        // if (count > max_size()) {
        //     length_exception();
        // }

        start_ = alloc_.allocate(count);
        end_ = start_ + count;
        end_capacity_ = end_;
        construct_range(start_, end_, value);
    }
    template <typename InputIt>
    vector(InputIt first, InputIt last, const allocator_type& alloc = allocator_type())
        : alloc_(alloc), start_(), end_(), end_capacity_() {
        typedef typename enable_if<is_iterator<InputIt>::value, InputIt>::type _type;
        (void)_type();

        for (; first != last; ++first) {
            push_back(*first);
        }
    }
    ~vector() {
        destroy_range(start_, end_);
        get_allocator().deallocate(start_, capacity());
    }

public:
    template <typename InputIt>
    void assign(InputIt first, InputIt last) {
        typedef typename enable_if<is_iterator<InputIt>::value, InputIt>::type _type;
        (void)_type();

        const size_type n = std::distance(first, last);
    }
    void assign(size_type count, const T& value) {
        if (count > capacity()) {
            vector tmp(count, value, get_allocator());
            tmp.swap(*this);
        } else if (count > size()) {
            const size_type extra = count - size();

            std::fill(begin(), end(), value);
            construct_range(end_, end_ + extra, value);
            end_ += extra;
        } else {
            const_pointer new_end = begin() + count;

            std::fill_n(begin(), count, value);
            destroy_range(new_end, end());
            end_ = new_end;
        }
    }
    allocator_type get_allocator() const { return alloc_; }

    reference at(size_type pos) {
        range_check(pos);
        return (*this)[pos];
    }
    const_reference at(size_type pos) const {
        range_check(pos);
        return (*this)[pos];
    }
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
    size_type max_size() const { return get_allocator().max_size(); }
    void      reserve(size_type new_cap) {
        if (new_cap > capacity()) {
            if (new_cap > max_size()) {
                length_exception();
            }

            reallocate(new_cap);
        }
    }
    size_type capacity() const { return static_cast<size_type>(end_capacity_ - start_); }

    template <class InputIt>
    void     insert(iterator pos, InputIt first, InputIt last) {}
    iterator insert(iterator pos, const T& value) {}
    void     insert(iterator pos, size_type count, const T& value) {}
    void     clear() {
        destroy_range(start_, end_);
        end_ = start_;
    }
    iterator erase(iterator pos) {}
    iterator erase(iterator first, iterator last) {}
    void     push_back(const T& value) {
        if (end_ == end_capacity_) {
            grow();
        }

        *end_ = value;
        ++end_;
    }
    void pop_back() {
        --end_;
        alloc_.destroy(end_);
    }
    void resize(size_type count, T value = T()) {}
    void swap(vector& other) {
        const_pointer ptr_start = start_;
        const_pointer ptr_end = end_;
        const_pointer ptr_end_cap = end_capacity_;

        start_ = other.start_;
        end_ = other.end_;
        end_capacity_ = other.end_capacity_;
        other.start_ = ptr_start;
        other.end_ = ptr_end;
        other.end_capacity_ = ptr_end_cap;
    }

private:
    size_type calculate_growth() const {
        const size_type old_cap = capacity();
        const size_type max = max_size();

        if (max / 2 < old_cap) {
            return max;
        }

        return old_cap == 0 ? 2 : old_cap * 2;
    }
    void grow() {
        const size_type old_cap = capacity();
        if (old_cap == max_size()) {
            length_exception();
        }

        allocator_type  alloc = get_allocator();
        const size_type new_cap = calculate_growth();
        reallocate(new_cap);
    }
    void reallocate(size_type n) {
        allocator_type alloc = get_allocator();
        pointer        new_start = alloc.allocate(n);
        pointer        new_end = new_start + size();

        construct_range(new_start, start_, end_);
        if (capacity() > 0) {
            destroy_range(start_, end_);
            alloc.deallocate(start_, capacity());
        }
        start_ = new_start;
        end_ = new_end;
        end_capacity_ = start_ + n;
    }
    void construct_range(pointer dst, const_pointer start, const_pointer end) {
        allocator_type alloc = get_allocator();
        for (; start != end; dst++, start++) {
            alloc.construct(dst, *start);
        }
    }
    void construct_range(pointer dst, const_pointer end, const_reference value) {
        allocator_type alloc = get_allocator();
        for (; dst != end; dst++) {
            alloc.construct(dst, value);
        }
    }
    void destroy_range(pointer start, pointer end) {
        allocator_type alloc = get_allocator();
        for (; start != end; start++) {
            alloc.destroy(start);
        }
    }
    void length_exception() {
        std::stringstream ss;

        ss << "vector is at max size ( " << max_size() << " and can't grow";
        throw std::length_error(ss.str());
    }
    void range_check(size_type n) {
        if (n >= size()) {
            std::stringstream ss;

            ss << "Index " << n << " is out of range (size = " << size();
            throw std::out_of_range(ss.str());
        }
    }

private:
    allocator_type alloc_;
    pointer        start_;
    pointer        end_;
    pointer        end_capacity_;
};
}
