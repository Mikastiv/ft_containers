/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 15:27:15 by mleblanc          #+#    #+#             */
/*   Updated: 2022/04/09 23:42:59 by mleblanc         ###   ########.fr       */
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
    vector() : alloc_(), start_(), end_(), end_cap_() {}
    vector(const vector& other) : alloc_(other.alloc_), start_(), end_(), end_cap_() {
        const size_type cap = other.capacity();
        if (cap == 0) {
            return;
        }

        const size_type s = other.size();
        start_ = alloc_.allocate(cap);
        end_ = start_ + s;
        end_cap_ = start_ + cap;
        construct_range(start_, other.start_, other.end_);
    }
    explicit vector(const allocator_type& alloc) : alloc_(alloc), start_(), end_(), end_cap_() {}
    explicit vector(
        size_type count, const T& value = T(), const allocator_type& alloc = allocator_type())
        : alloc_(alloc), start_(), end_(), end_cap_() {
        if (count == 0) {
            return;
        }
        if (count > max_size()) {
            length_exception();
        }
        start_ = alloc_.allocate(count);
        end_ = start_ + count;
        end_cap_ = end_;
        construct_range(start_, end_, value);
    }
    template <typename InputIt>
    vector(InputIt first, typename enable_if<!is_integral<InputIt>::value, InputIt>::type last,
        const allocator_type& alloc = allocator_type())
        : alloc_(alloc), start_(), end_(), end_cap_() {
        typedef typename iterator_traits<InputIt>::iterator_category category;
        range_init(first, last, category());
    }
    ~vector() { deallocate_v(); }
    vector& operator=(const vector& other) {
        if (&other == this) {
            return *this;
        }

        const size_type len = other.size();
        if (len > capacity()) {
            pointer new_start = alloc_.allocate(len);
            construct_range(new_start, other.start_, other.end_);
            deallocate_v();
            start_ = new_start;
            end_cap_ = start_ + len;
        } else if (size() >= len) {
            iterator it = std::copy(other.begin(), other.end(), begin());
            destroy_range(it.base(), end_);
        } else {
            std::copy(other.start_, other.start_ + size(), start_);
            construct_range(end_, other.start_ + size(), other.end_);
        }
        end_ = start_ + len;
        return *this;
    }

public:
    template <typename InputIt>
    void assign(
        InputIt first, typename enable_if<!is_integral<InputIt>::value, InputIt>::type last) {
        typedef typename iterator_traits<InputIt>::iterator_category category;
        range_assign(first, last, category());
    }
    void assign(size_type count, const T& value) {
        if (count > capacity()) {
            pointer new_start = alloc_.allocate(count);
            pointer new_end = new_start + count;
            construct_range(new_start, new_end, value);
            deallocate_v();
            start_ = new_start;
            end_ = new_end;
            end_cap_ = new_end;
        } else if (count > size()) {
            std::fill(begin(), end(), value);
            const size_type extra = count - size();
            end_ = construct_range(end_, end_ + extra, value);
        } else {
            pointer it = std::fill_n(start_, count, value);
            erase_at_end(it);
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

    bool      empty() const { return start_ == end_; }
    size_type size() const { return static_cast<size_type>(end_ - start_); }
    size_type max_size() const { return alloc_.max_size(); }
    void      reserve(size_type new_cap) {
        if (new_cap > capacity()) {
            if (new_cap > max_size()) {
                length_exception();
            }

            reallocate(new_cap);
        }
    }
    size_type capacity() const { return static_cast<size_type>(end_cap_ - start_); }
    iterator  insert(iterator pos, const T& value) {
        const size_type index = pos - begin();
        if (should_grow()) {
            const size_type new_size = calculate_growth();
            const size_type index = pos - begin();
            pointer         new_start = alloc_.allocate(new_size);
            pointer         new_end = new_start;

            new_end = construct_range(new_start, start_, start_ + index);
            alloc_.construct(new_end, value);
            ++new_end;
            new_end = construct_range(new_end, start_ + index, end_);
            destroy_range(start_, end_);
            alloc_.deallocate(start_, capacity());
            start_ = new_start;
            end_ = new_end;
            end_cap_ = new_start + new_size;
        } else {
            if (pos == end()) {
                alloc_.construct(end_, value);
                ++end_;
            } else {
                alloc_.construct(end_, *(end_ - 1));
                std::copy_backward(pos.base(), end_ - 2, end_ - 1);
                *pos = value;
            }
        }

        return iterator(start_ + index);
    }
    void insert(iterator pos, size_type count, const T& value) {
        if (count != 0) {
            const size_type extra_space = end_cap_ - end_;

            if (extra_space >= count) {
                const size_type elems_after = end() - pos;
                pointer         old_end = end_;

                if (elems_after > count) {
                    end_ = construct_range(end_, end_ - count, end_);
                    std::copy_backward(pos.base(), old_end - count, old_end);
                    std::fill_n(pos, count, value);
                } else {
                    end_ = construct_range(end_, end_ + (count - elems_after), value);
                    end_ = construct_range(end_, pos.base(), old_end);
                    std::fill(pos.base(), old_end, value);
                }
            } else {
                const size_type new_size = check_length(count);
                pointer         new_start = alloc_.allocate(new_size);
                pointer         new_end = new_start;

                new_end = construct_range(new_start, start_, pos.base());
                new_end = construct_range(new_end, new_end + count, value);
                new_end = construct_range(new_end, pos.base(), end_);

                destroy_range(start_, end_);
                alloc_.deallocate(start_, capacity());
                start_ = new_start;
                end_ = new_end;
                end_cap_ = new_start + new_size;
            }
        }
    }
    template <class InputIt>
    void insert(iterator pos, InputIt first,
        typename enable_if<!is_integral<InputIt>::value, InputIt>::type last) {
        typedef typename iterator_traits<InputIt>::iterator_category category;
        range_insert(pos, first, last, category());
    }
    void     clear() { erase_at_end(start_); }
    iterator erase(iterator pos) {
        if (pos + 1 != end()) {
            std::copy(pos + 1, end(), pos);
        }
        --end_;
        alloc_.destroy(end_);
        return pos;
    }
    iterator erase(iterator first, iterator last) {
        if (first != last) {
            if (last != end()) {
                std::copy(last, end(), first);
            }
            pointer new_end = first.base() + (end() - last);
            erase_at_end(new_end);
        }
        return first;
    }
    void push_back(const T& value) {
        if (should_grow()) {
            grow();
        }

        alloc_.construct(end_, value);
        ++end_;
    }
    void pop_back() {
        --end_;
        alloc_.destroy(end_);
    }
    void resize(size_type count, T value = T()) {
        if (count > size()) {
            insert(end(), value);
        } else if (count < size()) {
            erase_at_end(start_ + count);
        }
    }
    void swap(vector& other) {
        pointer ptr_start = start_;
        pointer ptr_end = end_;
        pointer ptr_end_cap = end_cap_;

        start_ = other.start_;
        end_ = other.end_;
        end_cap_ = other.end_cap_;
        other.start_ = ptr_start;
        other.end_ = ptr_end;
        other.end_cap_ = ptr_end_cap;
    }

private:
    template <typename InputIt>
    void range_init(InputIt first, InputIt last, std::input_iterator_tag) {
        for (; first != last; ++first) {
            push_back(*first);
        }
    }
    template <typename ForwardIt>
    void range_init(ForwardIt first, ForwardIt last, std::forward_iterator_tag) {
        const size_type n = std::distance(first, last);
        if (n == 0) {
            return;
        }
        if (n > max_size()) {
            length_exception();
        }

        start_ = alloc_.allocate(n);
        end_cap_ = start_ + n;
        end_ = construct_range(start_, first, last);
    }

    template <typename InputIt>
    void range_assign(InputIt first, InputIt last, std::input_iterator_tag) {
        iterator it = begin();
        for (; first != last && it != end(); ++it, ++first) {
            *it = *first;
        }

        if (first == last) {
            erase_at_end(it.base());
        } else {
            insert(end(), first, last);
        }
    }
    template <typename ForwardIt>
    void range_assign(ForwardIt first, ForwardIt last, std::forward_iterator_tag) {
        const size_type count = std::distance(first, last);

        if (count < size()) {
            iterator it = std::copy(first, last, begin());
            erase_at_end(it.base());
        } else {
            ForwardIt it = first;
            std::advance(it, size());
            std::copy(first, it, begin());
            insert(end(), it, last);
        }
    }

    template <typename InputIt>
    void range_insert(iterator pos, InputIt first, InputIt last, std::input_iterator_tag) {
        if (pos == end()) {
            for (; first != last; ++first) {
                insert(end(), *first);
            }
        } else if (first != last) {
            vector tmp(first, last);
            insert(pos, tmp.begin(), tmp.end());
        }
    }
    template <typename ForwardIt>
    void range_insert(iterator pos, ForwardIt first, ForwardIt last, std::forward_iterator_tag) {
        if (first != last) {
            const size_type count = std::distance(first, last);
            const size_type extra_space = end_cap_ - end_;

            if (extra_space >= count) {
                const size_type elems_after = end() - pos;
                pointer         old_end = end_;

                if (elems_after > count) {
                    end_ = construct_range(end_, end_ - count, end_);
                    std::copy_backward(pos.base(), old_end - count, old_end);
                    std::copy(first, last, pos);
                } else {
                    ForwardIt mid = first;
                    std::advance(mid, elems_after);
                    end_ = construct_range(end_, mid, last);
                    end_ = construct_range(end_, pos.base(), old_end);
                    std::copy(first, mid, pos);
                }
            } else {
                const size_type new_size = check_length(count);
                pointer         new_start = alloc_.allocate(new_size);
                pointer         new_end = new_start;

                new_end = construct_range(new_start, start_, pos.base());
                new_end = construct_range(new_end, first, last);
                new_end = construct_range(new_end, pos.base(), end_);

                destroy_range(start_, end_);
                alloc_.deallocate(start_, capacity());
                start_ = new_start;
                end_ = new_end;
                end_cap_ = new_start + new_size;
            }
        }
    }

    bool      should_grow() const { return end_ == end_cap_; }
    size_type calculate_growth() const {
        const size_type old_cap = capacity();
        const size_type max = max_size();

        if (max / 2 < old_cap) {
            return max;
        }

        return old_cap == 0 ? 1 : old_cap * 2;
    }
    void grow() {
        const size_type old_cap = capacity();
        if (old_cap == max_size()) {
            length_exception();
        }

        const size_type new_cap = calculate_growth();
        reallocate(new_cap);
    }

    void reallocate(size_type n) {
        pointer new_start = alloc_.allocate(n);
        pointer new_end = new_start + size();

        construct_range(new_start, start_, end_);
        if (capacity() > 0) {
            destroy_range(start_, end_);
            alloc_.deallocate(start_, capacity());
        }
        start_ = new_start;
        end_ = new_end;
        end_cap_ = start_ + n;
    }
    void deallocate_v() {
        if (capacity() > 0) {
            destroy_range(start_, end_);
            alloc_.deallocate(start_, capacity());
        }
    }

    template <typename It>
    pointer construct_range(pointer dst, It start, It end) {
        for (; start != end; ++dst, ++start) {
            alloc_.construct(dst, *start);
        }
        return dst;
    }
    pointer construct_range(pointer dst, const_pointer end, const_reference value) {
        for (; dst != end; ++dst) {
            alloc_.construct(dst, value);
        }
        return dst;
    }

    void construct_range_backward(pointer dst, const_pointer start, const_pointer end) {
        --end;
        for (; end != start - 1; --dst, --end) {
            alloc_.construct(dst, *end);
        }
    }

    void destroy_range(pointer start, pointer end) {
        for (; start != end; start++) {
            alloc_.destroy(start);
        }
    }

    void erase_at_end(pointer pos) {
        destroy_range(pos, end_);
        end_ = pos;
    }

    void length_exception() const {
        throw std::length_error("cannot create ft::vector larger than max_size()");
    }
    size_type check_length(size_type count) const {
        if (max_size() - size() < count) {
            length_exception();
        }

        const size_type length = size() + std::max(size(), count);
        return (length < size() || length > max_size()) ? max_size() : length;
    }
    void range_check(size_type n) const {
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
    pointer        end_cap_;
};
}
