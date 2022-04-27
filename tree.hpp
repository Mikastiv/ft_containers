/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 22:03:04 by mleblanc          #+#    #+#             */
/*   Updated: 2022/04/27 17:51:25 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <algorithm>
#include <iterator>
#include <limits>

#include "tree_iterator.hpp"
#include "utility.hpp"

namespace ft
{
class tree_end_node
{
public:
    typedef tree_base_node_types::node_base_pointer node_base_pointer;

public:
    tree_end_node()
        : left(NULL)
    {
    }

public:
    node_base_pointer left;
};

class tree_base_node : public tree_base_node_types::end_node_type
{
public:
    typedef tree_base_node_types::iter_pointer iter_pointer;
    typedef tree_base_node_types::node_base_pointer node_base_pointer;

public:
    tree_base_node()
        : right(NULL),
          parent(NULL),
          is_black(false)
    {
    }

    node_base_pointer get_parent() const
    {
        return static_cast<node_base_pointer>(parent);
    }

public:
    node_base_pointer right;
    iter_pointer parent;
    bool is_black;
};

template <typename T>
class tree_node : public tree_node_types<T>::base_node_type
{
public:
    tree_node()
        : value(T())
    {
    }

public:
    T value;
};

template <typename T, typename Compare, typename Allocator>
class tree
{
public:
    typedef T value_type;
    typedef Compare value_compare;
    typedef Allocator allocator_type;
    typedef typename allocator_type::size_type size_type;
    typedef typename allocator_type::difference_type difference_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef typename allocator_type::pointer pointer;
    typedef typename allocator_type::const_pointer const_pointer;
    typedef tree_iterator<value_type, difference_type> iterator;
    typedef const_tree_iterator<value_type, difference_type> const_iterator;

private:
    typedef typename tree_node_types<value_type>::end_node_type end_node_type;
    typedef typename tree_node_types<value_type>::node_type node_type;
    typedef typename tree_node_types<value_type>::iter_pointer iter_pointer;
    typedef typename tree_node_types<value_type>::node_base_pointer node_base_pointer;
    typedef typename tree_node_types<value_type>::node_pointer node_pointer;
    typedef typename allocator_type::template rebind<node_type>::other node_allocator;

public:
    tree(const value_compare& comp)
        : alloc_(node_allocator()),
          value_alloc_(allocator_type()),
          comp_(comp),
          end_node_(),
          size_(0)
    {
        begin_iter_ = end_node();
    }

    tree(const tree& other)
        : alloc_(other.alloc_),
          value_alloc_(other.value_alloc_),
          comp_(other.comp_),
          end_node_(),
          size_(0)
    {
        begin_iter_ = end_node();
        insert(other.begin(), other.last());
    }

    tree(const value_compare& comp, const allocator_type& alloc)
        : alloc_(node_allocator()),
          value_alloc_(alloc),
          comp_(comp),
          end_node_(),
          size_(0)
    {
        begin_iter_ = end_node();
    }

    tree& operator=(const tree& other)
    {
        if (this == &other) {
            return *this;
        }

        tree tmp(other);

        swap(tmp);
        insert(other.begin(), other.end());
        return *this;
    }

    ~tree()
    {
        destroy(root());
    }

public:
    allocator_type get_allocator() const
    {
        return value_alloc_;
    }

    template <typename Key, typename Value>
    reference find_or_insert(const Key& key, const Value& value)
    {
        iter_pointer parent;
        node_base_pointer& child = find_pos(parent, key);

        iterator it(child);
        if (child == NULL) {
            it = insert_at(child, parent, value_type(key, value));
        }

        return *it;
    }

    iterator begin()
    {
        return iterator(begin_iter_);
    }

    const_iterator begin() const
    {
        return const_iterator(begin_iter_);
    }

    iterator end()
    {
        return iterator(end_node());
    }

    const_iterator end() const
    {
        return const_iterator(end_node());
    }

    bool empty() const
    {
        return size() == static_cast<size_type>(0);
    }

    size_type size() const
    {
        return size_;
    }

    size_type max_size() const
    {
        return std::min(alloc_.max_size(),
                        static_cast<size_type>(std::numeric_limits<difference_type>::max()));
    }

    void clear()
    {
        destroy(root());
        end_node_.left = NULL;
        begin_iter_ = end_node();
        size_ = 0;
    }

    value_compare& value_comp()
    {
        return comp_;
    }

    const value_compare& value_comp() const
    {
        return comp_;
    }

    pair<iterator, bool> insert(const value_type& value)
    {
        iter_pointer parent;
        node_base_pointer& child = find_pos(parent, value);
        bool inserted = false;

        iterator it(child);
        if (child == NULL) {
            it = insert_at(child, parent, value);
            inserted = true;
        }

        return make_pair(it, inserted);
    }

    iterator insert(iterator hint, const value_type& value)
    {
        iter_pointer parent;
        node_base_pointer dummy;
        node_base_pointer& child = find_pos(hint, parent, value, dummy);

        iterator it(child);
        if (child == NULL) {
            it = insert_at(child, parent, value);
        }

        return it;
    }

    template <typename InputIt>
    void insert(InputIt first, InputIt last)
    {
        for (; first != last; ++first) {
            insert(*first);
        }
    }

    void erase(iterator pos)
    {
        (void)pos;
    }

    void erase(iterator first, iterator last)
    {
        for (; first != last; ++first) {
            erase(first);
        }
    }

    template <typename Key>
    size_type erase(const Key& key)
    {
        size_type s = size();
        iter_pointer ptr = find_pointer(key);

        erase(iterator(ptr));

        return s == size() ? static_cast<size_type>(0) : static_cast<size_type>(1);
    }

    void swap(tree& other)
    {
        std::swap(begin_iter_, other.begin_iter_);
        std::swap(end_node_, other.end_node_);
        std::swap(size_, other.size_);
        std::swap(comp_, other.comp_);

        if (size() == 0) {
            begin_iter_ = end_node();
        } else {
            end_node()->left->parent = end_node();
        }

        if (other.size() == 0) {
            other.begin_iter_ = other.end_node();
        } else {
            other.end_node()->left->parent = other.end_node();
        }
    }

    template <typename Key>
    size_type count(const Key& key) const
    {
        return find_pointer(key) == NULL ? static_cast<size_type>(0) : static_cast<size_type>(1);
    }

    template <typename Key>
    iterator find(const Key& key)
    {
        return find_key<iterator>(key);
    }

    template <typename Key>
    const_iterator find(const Key& key) const
    {
        return find_key<const_iterator>(key);
    }

    template <typename Key>
    pair<iterator, iterator> equal_range(const Key& key)
    {
        return make_pair(lower_bound(key), upper_bound(key));
    }

    template <typename Key>
    pair<const_iterator, const_iterator> equal_range(const Key& key) const
    {
        return make_pair(lower_bound(key), upper_bound(key));
    }

    template <typename Key>
    iterator lower_bound(const Key& key)
    {
        return low_bound<iterator>(key);
    }

    template <typename Key>
    const_iterator lower_bound(const Key& key) const
    {
        return low_bound<const_iterator>(key);
    }

    template <typename Key>
    iterator upper_bound(const Key& key)
    {
        return up_bound<iterator>(key);
    }

    template <typename Key>
    const_iterator upper_bound(const Key& key) const
    {
        return up_bound<const_iterator>(key);
    }

private:
    template <typename Iter, typename Key>
    Iter find_key(const Key& key) const
    {
        iter_pointer ptr = find_pointer(key);

        if (ptr == NULL) {
            return Iter(end_node());
        }
        return Iter(ptr);
    }

    template <typename Iter, typename Key>
    Iter low_bound(const Key& key)
    {
        node_pointer ptr = root();
        iter_pointer pos = end_node();

        while (ptr != NULL) {
            if (!value_comp()(ptr->value, key)) {
                pos = static_cast<iter_pointer>(ptr);
                ptr = static_cast<node_pointer>(ptr->left);
            } else {
                ptr = static_cast<node_pointer>(ptr->right);
            }
        }

        return Iter(pos);
    }

    template <typename Iter, typename Key>
    Iter up_bound(const Key& key)
    {
        node_pointer ptr = root();
        iter_pointer pos = end_node();

        while (ptr != NULL) {
            if (value_comp()(key, ptr->value)) {
                pos = static_cast<iter_pointer>(ptr);
                ptr = static_cast<node_pointer>(ptr->left);
            } else {
                ptr = static_cast<node_pointer>(ptr->right);
            }
        }

        return Iter(pos);
    }

    iterator insert_at(node_base_pointer& pos, iter_pointer parent, const value_type& value)
    {
        pos = construct_node(value);
        pos->parent = parent;
        if (begin_iter_->left != NULL)
            begin_iter_ = begin_iter_->left;
        ++size_;

        // Balance tree

        return iterator(pos);
    }

    node_pointer root() const
    {
        return static_cast<node_pointer>(end_node()->left);
    }

    node_base_pointer* root_ptr() const
    {
        return static_cast<node_base_pointer*>(&(end_node()->left));
    }

    iter_pointer end_node()
    {
        return static_cast<iter_pointer>(&end_node_);
    }

    iter_pointer end_node() const
    {
        return const_cast<iter_pointer>(&end_node_);
    }

    node_pointer construct_node(const value_type& value)
    {
        node_pointer new_node = alloc_.allocate(1);
        new_node->left = NULL;
        new_node->right = NULL;
        new_node->is_black = false;
        value_alloc_.construct(&new_node->value, value);
        return new_node;
    }

    template <typename Key>
    iter_pointer find_pointer(const Key& key) const
    {
        node_pointer ptr = root();
        while (ptr != NULL) {
            if (value_comp()(key, ptr->value)) {
                ptr = static_cast<node_pointer>(ptr->left);
            } else if (value_comp()(ptr->value, key)) {
                ptr = static_cast<node_pointer>(ptr->right);
            } else {
                return static_cast<iter_pointer>(ptr);
            }
        }
        return NULL;
    }

    template <typename Key>
    node_base_pointer& find_pos(iter_pointer& parent, const Key& key) const
    {
        node_pointer node = root();
        node_base_pointer* ptr = root_ptr();

        if (node != NULL) {
            while (true) {
                if (value_comp()(key, node->value)) {
                    // key < node->value
                    if (node->left != NULL) {
                        ptr = &node->left;
                        node = static_cast<node_pointer>(node->left);
                    } else {
                        parent = static_cast<iter_pointer>(node);
                        return node->left;
                    }
                } else if (value_comp()(node->value, key)) {
                    // key > node->value
                    if (node->right != NULL) {
                        ptr = &node->right;
                        node = static_cast<node_pointer>(node->right);
                    } else {
                        parent = static_cast<iter_pointer>(node);
                        return node->right;
                    }
                } else {
                    // key == node->value
                    parent = static_cast<iter_pointer>(node);
                    return *ptr;
                }
            }
        }
        parent = static_cast<iter_pointer>(end_node());
        return parent->left;
    }

    node_base_pointer& find_pos(iterator hint, iter_pointer& parent, const value_type& value,
                                node_base_pointer& dummy) const
    {
        if (hint == end() || value_comp()(value, *hint)) {
            // value < *__hint
            const_iterator prev = hint;
            if (prev == begin() || value_comp()(*--prev, value)) {
                // *prev < value < *hint
                if (hint.base()->left == NULL) {
                    parent = hint.base();
                    return parent->left;
                } else {
                    parent = prev.base();
                    return prev.node_ptr()->right;
                }
            }
            // value <= *prev
            return find_pos(parent, value);
        } else if (value_comp()(*hint, value)) {
            // *hint < value
            const_iterator next = hint;
            ++next;
            if (next == end() || value_comp()(value, *next)) {
                // *hint < value < *next
                if (hint.node_ptr()->right == NULL) {
                    parent = hint.base();
                    return hint.node_ptr()->right;
                } else {
                    parent = next.base();
                    return parent->left;
                }
            }
            // *next <= value
            return find_pos(parent, value);
        }
        parent = hint.base();
        dummy = static_cast<node_base_pointer>(hint.base());
        return dummy;
    }

    void destroy(node_pointer node)
    {
        if (node != NULL) {
            destroy(static_cast<node_pointer>(node->left));
            destroy(static_cast<node_pointer>(node->right));
            value_alloc_.destroy(&node->value);
            alloc_.deallocate(node, 1);
        }
    }

private:
    node_allocator alloc_;
    allocator_type value_alloc_;
    value_compare comp_;
    end_node_type end_node_;
    iter_pointer begin_iter_;
    size_type size_;
};
} // namespace ft
