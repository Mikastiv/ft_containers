/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 12:17:41 by mleblanc          #+#    #+#             */
/*   Updated: 2022/04/21 23:40:44 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>

#include "tree.hpp"
#include "utility.hpp"

namespace ft
{
template <typename Key, typename T, typename Compare = less<Key>,
          typename Allocator = std::allocator<pair<const Key, T> > >
class map
{
  public:
    typedef Key key_type;
    typedef T mapped_type;
    typedef pair<const key_type, mapped_type> value_type;
    typedef Compare key_compare;
    typedef Allocator allocator_type;
    typedef typename allocator_type::size_type size_type;
    typedef typename allocator_type::difference_type difference_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef typename allocator_type::pointer pointer;
    typedef typename allocator_type::const_pointer const_pointer;

  public:
    map();
    explicit map(const key_compare& comp, const allocator_type& alloc = allocator_type());
    template <typename InputIt>
    map(InputIt first, InputIt last, const key_compare& comp = key_compare(),
        const allocator_type& alloc = allocator_type());
    map(const map& other);
    map& operator=(const map& other);
    ~map();

  public:
    allocator_type get_allocator() const;
    reference at(const key_type& key);
    const_reference at(const key_type& key) const;
    reference operator[](const key_type& key);
    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;
    reverse_iterator rbegin();
    const_reverse_iterator rbegin() const;
    reverse_iterator rend();
    const_reverse_iterator rend() const;
    bool empty() const;
    size_type size() const;
    size_type max_size() const;
    void clear();
    pair<iterator, bool> insert(const value_type& value);
    iterator insert(iterator hint, const value_type& value);
    template <typename InputIt>
    void insert(InputIt first, InputIt last);
    void erase(iterator pos);
    void erase(iterator first, iterator last);
    size_type erase(const key_type& key);
    void swap(map& other);
    size_type count(const key_type& key) const;
    iterator find(const key_type& key);
    const_iterator find(const key_type& key) const;
    pair<iterator, iterator> equal_range(const key_type& key);
    pair<const_iterator, const_iterator> equal_range(const key_type& key) const;
    iterator lower_bound(const key_type& key);
    const_iterator lower_bound(const key_type& key) const;
    iterator upper_bound(const key_type& key);
    const_iterator upper_bound(const key_type& key) const;
    key_compare key_comp() const;
    // value_compare value_comp() const;

    private:
      tree<value_type, key_compare, allocator_type> tree_;
};

template <typename Key, typename T, typename Compare, typename Allocator>
inline void swap(map<Key, T, Compare, Allocator>& lhs, map<Key, T, Compare, Allocator>& rhs)
{
    lhs.swap(rhs);
}
} // namespace ft
