/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 16:29:45 by mleblanc          #+#    #+#             */
/*   Updated: 2022/04/20 17:53:11 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "utility.hpp"
#include <memory>

namespace ft
{
template <typename Key, typename Compare = ft::less<Key>, typename Allocator = std::allocator<Key> >
class set
{
  public:
    typedef Key key_type;
    typedef Key value_type;
    typedef Compare key_compare;
    typedef Compare value_compare;
    typedef Allocator allocator_type;
    typedef typename allocator_type::difference_type difference_type;
    typedef typename allocator_type::size_type size_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef typename allocator_type::pointer pointer;
    typedef typename allocator_type::const_pointer const_pointer;

  public:
    set();
    explicit set(const key_compare& comp, const allocator_type& alloc = allocator_type());
    template <class InputIt>
    set(InputIt first, InputIt last, const key_compare& comp = key_compare(),
        const allocator_type& alloc = allocator_type());
    set(const set& other);
    set& operator=(const set& other);
    ~set();

  public:
    allocator_type get_allocator() const;
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
    void swap(set& other);
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
    value_compare value_comp() const;

};

template <typename Key, typename Compare, typename Allocator>
void swap(set<Key, Compare, Allocator>& lhs, set<Key, Compare, Allocator>& rhs)
{
    lhs.swap(rhs);
}
} // namespace ft
