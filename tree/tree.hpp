/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 22:03:04 by mleblanc          #+#    #+#             */
/*   Updated: 2022/05/04 12:12:43 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <algorithm>
#include <iterator>
#include <limits>

#include "../utility.hpp"
#include "tree_iterator.hpp"

#include "tree_print.hpp"

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
    typedef tree_base_node_types::end_node_pointer end_node_pointer;
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

    void set_parent(node_base_pointer ptr)
    {
        parent = static_cast<end_node_pointer>(ptr);
    }

public:
    node_base_pointer right;
    end_node_pointer parent;
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
    // clang-format off
    typedef T                                                value_type;
    typedef Compare                                          value_compare;
    typedef Allocator                                        allocator_type;
    typedef typename allocator_type::size_type               size_type;
    typedef typename allocator_type::difference_type         difference_type;
    typedef value_type&                                      reference;
    typedef const value_type&                                const_reference;
    typedef typename allocator_type::pointer                 pointer;
    typedef typename allocator_type::const_pointer           const_pointer;
    typedef tree_iterator<value_type, difference_type>       iterator;
    typedef const_tree_iterator<value_type, difference_type> const_iterator;

private:
    typedef typename tree_node_types<value_type>::end_node_type        end_node_type;
    typedef typename tree_node_types<value_type>::node_type            node_type;
    typedef typename tree_node_types<value_type>::end_node_pointer     end_node_pointer;
    typedef typename tree_node_types<value_type>::node_base_pointer    node_base_pointer;
    typedef typename tree_node_types<value_type>::node_pointer         node_pointer;
    typedef typename allocator_type::template rebind<node_type>::other node_allocator;
    // clang-format on

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
        end_node_pointer parent;
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
        return size() == size_type(0);
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
        end_node_pointer parent;
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
        end_node_pointer parent;
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
        if (begin_iter_ == pos.base()) {
            iterator it(pos);
            ++it;
            begin_iter_ = it.base();
        }

        node_pointer ptr = pos.node_ptr();

        tree_remove_node(end_node()->left, static_cast<node_base_pointer>(ptr));
        value_alloc_.destroy(&ptr->value);
        alloc_.deallocate(ptr, 1);
        size_--;
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
        iterator it = find(key);

        if (it == end()) {
            return size_type(0);
        }

        erase(it);

        return size_type(1);
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
        return find_pointer(key) == NULL ? size_type(0) : size_type(1);
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

    void print_tree() const
    {
        std::cout << traverse_root(static_cast<node_pointer>(root()));
    }

private:
    template <typename Iter, typename Key>
    Iter find_key(const Key& key) const
    {
        end_node_pointer ptr = find_pointer(key);

        if (ptr == NULL) {
            return Iter(end_node());
        }
        return Iter(ptr);
    }

    template <typename Iter, typename Key>
    Iter low_bound(const Key& key)
    {
        node_pointer ptr = root();
        end_node_pointer pos = end_node();

        while (ptr != NULL) {
            if (!value_comp()(ptr->value, key)) {
                pos = static_cast<end_node_pointer>(ptr);
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
        end_node_pointer pos = end_node();

        while (ptr != NULL) {
            if (value_comp()(key, ptr->value)) {
                pos = static_cast<end_node_pointer>(ptr);
                ptr = static_cast<node_pointer>(ptr->left);
            } else {
                ptr = static_cast<node_pointer>(ptr->right);
            }
        }

        return Iter(pos);
    }

    iterator insert_at(node_base_pointer& pos, end_node_pointer parent, const value_type& value)
    {
        pos = construct_node(value);
        pos->parent = parent;
        if (begin_iter_->left != NULL)
            begin_iter_ = begin_iter_->left;
        ++size_;

        tree_balance_after_insert(end_node()->left, pos);

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

    end_node_pointer end_node()
    {
        return static_cast<end_node_pointer>(&end_node_);
    }

    end_node_pointer end_node() const
    {
        return const_cast<end_node_pointer>(&end_node_);
    }

    node_pointer construct_node(const value_type& value)
    {
        node_pointer new_node = alloc_.allocate(1);
        new_node->left = NULL;
        new_node->right = NULL;
        new_node->parent = NULL;
        new_node->is_black = false;
        value_alloc_.construct(&new_node->value, value);
        return new_node;
    }

    template <typename Key>
    end_node_pointer find_pointer(const Key& key) const
    {
        node_pointer ptr = root();
        while (ptr != NULL) {
            if (value_comp()(key, ptr->value)) {
                ptr = static_cast<node_pointer>(ptr->left);
            } else if (value_comp()(ptr->value, key)) {
                ptr = static_cast<node_pointer>(ptr->right);
            } else {
                return static_cast<end_node_pointer>(ptr);
            }
        }
        return NULL;
    }

    template <typename Key>
    node_base_pointer& find_pos(end_node_pointer& parent, const Key& key) const
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
                        parent = static_cast<end_node_pointer>(node);
                        return node->left;
                    }
                } else if (value_comp()(node->value, key)) {
                    // key > node->value
                    if (node->right != NULL) {
                        ptr = &node->right;
                        node = static_cast<node_pointer>(node->right);
                    } else {
                        parent = static_cast<end_node_pointer>(node);
                        return node->right;
                    }
                } else {
                    // key == node->value
                    parent = static_cast<end_node_pointer>(node);
                    return *ptr;
                }
            }
        }
        parent = static_cast<end_node_pointer>(end_node());
        return parent->left;
    }

    template <typename Key>
    node_base_pointer& find_pos(iterator hint, end_node_pointer& parent, const Key& key,
                                node_base_pointer& dummy) const
    {
        if (hint == end() || value_comp()(key, *hint)) {
            // value < *__hint
            const_iterator prev = hint;
            if (prev == begin() || value_comp()(*--prev, key)) {
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
            return find_pos(parent, key);
        } else if (value_comp()(*hint, key)) {
            // *hint < value
            const_iterator next = hint;
            ++next;
            if (next == end() || value_comp()(key, *next)) {
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
            return find_pos(parent, key);
        }
        parent = hint.base();
        dummy = static_cast<node_base_pointer>(hint.base());
        return dummy;
    }

    void delete_node(node_pointer node)
    {
        value_alloc_.destroy(&node->value);
        alloc_.deallocate(node, 1);
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
    end_node_pointer begin_iter_;
    size_type size_;
};
} // namespace ft