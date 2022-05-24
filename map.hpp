/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 12:17:41 by mleblanc          #+#    #+#             */
/*   Updated: 2022/05/24 13:15:34 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>

#include "iterator.hpp"
#include "tree/tree.hpp"

namespace ft
{
template <typename Key, typename T, typename Compare>
class map_value_type_compare : public std::binary_function<Key, Key, bool>
{
public:
    typedef Key  first_argument_type;
    typedef Key  second_argument_type;
    typedef bool result_type;

public:
    map_value_type_compare()
        : comp_()
    {
    }

    map_value_type_compare(const Compare& c)
        : comp_(c)
    {
    }

public:
    const Compare& key_comp() const
    {
        return comp_;
    }

    bool operator()(const T& x, const T& y) const
    {
        return key_comp()(x.first, y.first);
    }

    bool operator()(const Key& x, const T& y) const
    {
        return key_comp()(x, y.first);
    }

    bool operator()(const T& x, const Key& y) const
    {
        return key_comp()(x.first, y);
    }

    void swap(map_value_type_compare& other)
    {
        std::swap(comp_, other.comp_);
    }

protected:
    Compare comp_;
};

template <typename Key, typename T, typename Compare>
void swap(map_value_type_compare<Key, T, Compare>& x, map_value_type_compare<Key, T, Compare>& y)
{
    x.swap(y);
}

template <typename Key, typename T, typename Compare = std::less<Key>,
          typename Allocator = std::allocator<pair<const Key, T> > >
class map
{
public:
    // clang-format off
    typedef Key                                      key_type;
    typedef T                                        mapped_type;
    typedef pair<const key_type, mapped_type>        value_type;
    typedef Compare                                  key_compare;
    typedef Allocator                                allocator_type;
    typedef typename allocator_type::size_type       size_type;
    typedef typename allocator_type::difference_type difference_type;
    typedef value_type&                              reference;
    typedef const value_type&                        const_reference;
    typedef typename allocator_type::pointer         pointer;
    typedef typename allocator_type::const_pointer   const_pointer;

private:
    typedef map_value_type_compare<key_type, value_type, key_compare> vt_compare;
    typedef tree<value_type, vt_compare, allocator_type>              base;

public:
    typedef typename base::iterator              iterator;
    typedef typename base::const_iterator        const_iterator;
    typedef ft::reverse_iterator<iterator>       reverse_iterator;
    typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
    // clang-format on

public:
    class value_compare : public std::binary_function<value_type, value_type, bool>
    {
        friend class map;

    public:
        typedef value_type first_argument_type;
        typedef value_type second_argument_type;
        typedef bool       result_type;

    public:
        bool operator()(const value_type& x, const value_type& y) const
        {
            return comp(x.first, y.first);
        }

    protected:
        value_compare(const key_compare& c)
            : comp(c)
        {
        }

    protected:
        key_compare comp;
    };

public:
    map()
        : tree_(vt_compare())
    {
    }

    explicit map(const key_compare& comp, const allocator_type& alloc = allocator_type())
        : tree_(vt_compare(comp), alloc)
    {
    }

    template <typename InputIt>
    map(InputIt first, InputIt last, const key_compare& comp = key_compare(),
        const allocator_type& alloc = allocator_type())
        : tree_(vt_compare(comp), alloc)
    {
        insert(first, last);
    }

    map(const map& other)
        : tree_(other.tree_)
    {
    }

    map& operator=(const map& other)
    {
        tree_ = other.tree_;
        return *this;
    }

    ~map()
    {
    }

public:
    allocator_type get_allocator() const
    {
        return tree_.get_allocator();
    }

    T& at(const key_type& key)
    {
        iterator it = find(key);
        if (it == end()) {
            throw std::out_of_range("Key not found");
        }
        return it->second;
    }

    const T& at(const key_type& key) const
    {
        const_iterator it = find(key);
        if (it == end()) {
            throw std::out_of_range("Key not found");
        }
        return it->second;
    }

    T& operator[](const key_type& key)
    {
        return insert(ft::make_pair(key, T())).first->second;
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

    void swap(map& other)
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
        return tree_.value_comp().key_comp();
    }

    value_compare value_comp() const
    {
        return value_compare(tree_.value_comp().key_comp());
    }

private:
    base tree_;
};

template <typename Key, typename T, typename Compare, typename Allocator>
inline void swap(map<Key, T, Compare, Allocator>& x, map<Key, T, Compare, Allocator>& y)
{
    x.swap(y);
}

template <typename Key, typename T, typename Compare, typename Allocator>
inline bool operator==(const map<Key, T, Compare, Allocator>& lhs,
                       const map<Key, T, Compare, Allocator>& rhs)
{
    return (lhs.size() == rhs.size()) && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <typename Key, typename T, typename Compare, typename Allocator>
inline bool operator!=(const map<Key, T, Compare, Allocator>& lhs,
                       const map<Key, T, Compare, Allocator>& rhs)
{
    return !(lhs == rhs);
}

template <typename Key, typename T, typename Compare, typename Allocator>
inline bool operator<(const map<Key, T, Compare, Allocator>& lhs,
                      const map<Key, T, Compare, Allocator>& rhs)
{
    return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename Key, typename T, typename Compare, typename Allocator>
inline bool operator<=(const map<Key, T, Compare, Allocator>& lhs,
                       const map<Key, T, Compare, Allocator>& rhs)
{
    return !(rhs < lhs);
}

template <typename Key, typename T, typename Compare, typename Allocator>
inline bool operator>(const map<Key, T, Compare, Allocator>& lhs,
                      const map<Key, T, Compare, Allocator>& rhs)
{
    return rhs < lhs;
}

template <typename Key, typename T, typename Compare, typename Allocator>
inline bool operator>=(const map<Key, T, Compare, Allocator>& lhs,
                       const map<Key, T, Compare, Allocator>& rhs)
{
    return !(lhs < rhs);
}
} // namespace ft
