/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 16:29:45 by mleblanc          #+#    #+#             */
/*   Updated: 2022/05/23 21:45:00 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>

#include "iterator.hpp"
#include "tree/tree.hpp"

namespace ft
{
template <typename Key, typename Compare = std::less<Key>,
          typename Allocator = std::allocator<Key> >
class set
{
public:
    // clang-format off
    typedef Key                                      key_type;
    typedef Key                                      value_type;
    typedef Compare                                  key_compare;
    typedef Compare                                  value_compare;
    typedef Allocator                                allocator_type;
    typedef typename allocator_type::difference_type difference_type;
    typedef typename allocator_type::size_type       size_type;
    typedef value_type&                              reference;
    typedef const value_type&                        const_reference;
    typedef typename allocator_type::pointer         pointer;
    typedef typename allocator_type::const_pointer   const_pointer;

private:
    typedef tree<value_type, value_compare, Allocator> base;

public:
    typedef typename base::const_iterator              iterator;
    typedef typename base::const_iterator        const_iterator;
    typedef ft::reverse_iterator<iterator>       reverse_iterator;
    typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
    // clang-format on

public:
    set()
        : tree_(value_compare())
    {
    }

    explicit set(const key_compare& comp, const allocator_type& alloc = allocator_type())
        : tree_(comp, alloc)
    {
    }

    template <class InputIt>
    set(InputIt first, InputIt last, const key_compare& comp = key_compare(),
        const allocator_type& alloc = allocator_type())
        : tree_(comp, alloc)
    {
        insert(first, last);
    }

    set(const set& other)
        : tree_(other.tree_)
    {
    }

    set& operator=(const set& other)
    {
        tree_ = other.tree_;
        return *this;
    }

    ~set()
    {
    }

public:
    allocator_type get_allocator() const
    {
        return tree_.get_allocator();
    }

    iterator begin()
    {
        return tree_.begin();
    }

    const_iterator begin() const
    {
        return tree_.begin();
    }

    iterator end()
    {
        return tree_.end();
    }

    const_iterator end() const
    {
        return tree_.end();
    }

    reverse_iterator rbegin()
    {
        return reverse_iterator(end());
    }

    const_reverse_iterator rbegin() const
    {
        return const_reverse_iterator(end());
    }

    reverse_iterator rend()
    {
        return reverse_iterator(begin());
    }

    const_reverse_iterator rend() const
    {
        return const_reverse_iterator(begin());
    }

    bool empty() const
    {
        return tree_.empty();
    }

    size_type size() const
    {
        return tree_.size();
    }

    size_type max_size() const
    {
        return tree_.max_size();
    }

    void clear()
    {
        tree_.clear();
    }

    pair<iterator, bool> insert(const value_type& value)
    {
        return tree_.insert(value);
    }

    iterator insert(iterator hint, const value_type& value)
    {
        return tree_.insert(hint, value);
    }

    template <typename InputIt>
    void insert(InputIt first, InputIt last)
    {
        tree_.insert(first, last);
    }

    void erase(iterator pos)
    {
        tree_.erase(const_iterator(pos));
    }

    void erase(iterator first, iterator last)
    {
        tree_.erase(first, last);
    }

    size_type erase(const key_type& key)
    {
        return tree_.erase(key);
    }

    void swap(set& other)
    {
        tree_.swap(other.tree_);
    }

    size_type count(const key_type& key) const
    {
        return tree_.count(key);
    }

    iterator find(const key_type& key)
    {
        return tree_.find(key);
    }

    const_iterator find(const key_type& key) const
    {
        return tree_.find(key);
    }

    pair<iterator, iterator> equal_range(const key_type& key)
    {
        return tree_.equal_range(key);
    }

    pair<const_iterator, const_iterator> equal_range(const key_type& key) const
    {
        return tree_.equal_range(key);
    }

    iterator lower_bound(const key_type& key)
    {
        return tree_.lower_bound(key);
    }

    const_iterator lower_bound(const key_type& key) const
    {
        return tree_.lower_bound(key);
    }

    iterator upper_bound(const key_type& key)
    {
        return tree_.upper_bound(key);
    }

    const_iterator upper_bound(const key_type& key) const
    {
        return tree_.upper_bound(key);
    }

    key_compare key_comp() const
    {
        return tree_.value_comp();
    }

    value_compare value_comp() const
    {
        return tree_.value_comp();
    }

private:
    base tree_;
};

template <typename Key, typename Compare, typename Allocator>
void swap(set<Key, Compare, Allocator>& x, set<Key, Compare, Allocator>& y)
{
    x.swap(y);
}

template <typename Key, typename Compare, typename Allocator>
inline bool operator==(const set<Key, Compare, Allocator>& lhs,
                       const set<Key, Compare, Allocator>& rhs)
{
    return (lhs.size() == rhs.size()) && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <typename Key, typename Compare, typename Allocator>
inline bool operator!=(const set<Key, Compare, Allocator>& lhs,
                       const set<Key, Compare, Allocator>& rhs)
{
    return !(lhs == rhs);
}

template <typename Key, typename Compare, typename Allocator>
inline bool operator<(const set<Key, Compare, Allocator>& lhs,
                      const set<Key, Compare, Allocator>& rhs)
{
    return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename Key, typename Compare, typename Allocator>
inline bool operator<=(const set<Key, Compare, Allocator>& lhs,
                       const set<Key, Compare, Allocator>& rhs)
{
    return !(rhs < lhs);
}

template <typename Key, typename Compare, typename Allocator>
inline bool operator>(const set<Key, Compare, Allocator>& lhs,
                      const set<Key, Compare, Allocator>& rhs)
{
    return rhs < lhs;
}

template <typename Key, typename Compare, typename Allocator>
inline bool operator>=(const set<Key, Compare, Allocator>& lhs,
                       const set<Key, Compare, Allocator>& rhs)
{
    return !(lhs < rhs);
}
} // namespace ft
