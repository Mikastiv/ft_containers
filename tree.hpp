/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 22:03:04 by mleblanc          #+#    #+#             */
/*   Updated: 2022/04/25 14:27:23 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <algorithm>
#include <iterator>
#include <limits>
#include <stddef.h>

class tree_end_node;

template <typename T>
class tree_node;

template <typename T>
struct tree_node_types {
    typedef tree_end_node end_node_type;
    typedef tree_end_node* node_base_pointer;
    typedef tree_node<T> node_type;
    typedef node_type* node_pointer;
    typedef const node_type* const_node_pointer;
};

class tree_end_node
{
public:
    tree_end_node()
        : left(NULL)
    {
    }

    tree_end_node(const tree_end_node& other)
        : left(other.left)
    {
    }

    tree_end_node& operator=(const tree_end_node& other)
    {
        left = other.left;
        return *this;
    }

    ~tree_end_node()
    {
    }

public:
    tree_end_node* left;
};

template <typename T>
class tree_node : public tree_node_types<T>::end_node_type
{
public:
    typedef typename tree_node_types<T>::node_base_pointer node_base_pointer;

public:
    tree_node()
        : tree_node_types<T>::end_node_type(),
          parent(NULL),
          right(NULL),
          value(T()),
          is_black(false)
    {
    }

    tree_node(const T& v)
        : tree_node_types<T>::end_node_type(),
          parent(NULL),
          right(NULL),
          value(v),
          is_black(false)
    {
    }

    tree_node& operator=(const tree_node& other)
    {
        this->left = other.left;
        value = other.value;
        parent = other.parent;
        right = other.right;
        is_black = other.is_black;
        return *this;
    }

    ~tree_node()
    {
    }

public:
    node_base_pointer parent;
    node_base_pointer right;
    T value;
    bool is_black;
};

template <typename NodePtr>
inline bool tree_is_left_child(NodePtr ptr)
{
    return ptr == ptr->parent->left;
}

template <typename NodePtr>
NodePtr tree_max(NodePtr ptr)
{
    while (ptr->right != NULL) {
        ptr = ptr->right;
    }
    return ptr;
}

template <typename NodePtr>
NodePtr tree_min(NodePtr ptr)
{
    while (ptr->left != NULL) {
        ptr = ptr->left;
    }
    return ptr;
}

template <typename IterPtr, typename NodePtr>
IterPtr tree_iter_next(NodePtr ptr)
{
    if (ptr->right != NULL) {
        return tree_min(ptr->right);
    }
    while (!tree_is_left_child(ptr)) {
        ptr = ptr->parent;
    }
    return static_cast<IterPtr>(ptr->parent);
}

template <typename NodePtr, typename IterPtr>
NodePtr tree_iter_prev(IterPtr ptr)
{
    if (ptr->left != NULL) {
        return tree_max(ptr->left);
    }
    NodePtr nptr = static_cast<NodePtr>(ptr);
    while (tree_is_left_child(nptr)) {
        nptr = nptr->parent;
    }
    return nptr->parent;
}

template <typename T, typename DiffType>
class tree_iterator
{
private:
    typedef typename tree_node_types<T>::node_base_pointer node_base_pointer;
    typedef typename tree_node_types<T>::node_pointer node_pointer;

public:
    typedef std::bidirectional_iterator_tag iterator_category;
    typedef T value_type;
    typedef DiffType difference_type;
    typedef value_type& reference;
    typedef value_type* pointer;

public:
    tree_iterator()
        : ptr(NULL)
    {
    }

    tree_iterator(const tree_iterator& other)
        : ptr(other.ptr)
    {
    }

    tree_iterator(node_pointer p)
        : ptr(static_cast<node_base_pointer>(p))
    {
    }

    tree_iterator(node_base_pointer p)
        : ptr(p)
    {
    }

    tree_iterator& operator=(const tree_iterator& other)
    {
        ptr = other.ptr;
        return *this;
    }

    ~tree_iterator()
    {
    }

public:
    reference operator*() const
    {
        return static_cast<node_pointer>(ptr)->value;
    }

    pointer operator->() const
    {
        return &(operator*());
    }

    tree_iterator& operator++()
    {
        ptr = tree_iter_next<node_base_pointer>(static_cast<node_pointer>(ptr));
        return *this;
    }

    tree_iterator operator++(int)
    {
        tree_iterator t = *this;
        ++(*this);
        return t;
    }

    tree_iterator& operator--()
    {
        ptr = static_cast<node_base_pointer>(tree_iter_next<node_pointer>(ptr));
        return *this;
    }

    tree_iterator operator--(int)
    {
        tree_iterator t = *this;
        --(*this);
        return t;
    }

    bool operator==(const tree_iterator& other) const
    {
        return ptr == other.ptr;
    }

    bool operator!=(const tree_iterator& other) const
    {
        return !(*this == other);
    }

private:
    node_base_pointer ptr;
};

template <typename T, typename DiffType>
class tree_const_iterator
{
private:
    typedef typename tree_node_types<T>::node_base_pointer node_base_pointer;
    typedef typename tree_node_types<T>::node_pointer node_pointer;

public:
    typedef std::bidirectional_iterator_tag iterator_category;
    typedef T value_type;
    typedef DiffType difference_type;
    typedef const value_type& reference;
    typedef const value_type* pointer;

public:
    tree_const_iterator()
        : ptr(NULL)
    {
    }

    tree_const_iterator(const tree_const_iterator& other)
        : ptr(other.ptr)
    {
    }

    tree_const_iterator(node_pointer p)
        : ptr(static_cast<node_base_pointer>(p))
    {
    }

    tree_const_iterator(node_base_pointer p)
        : ptr(p)
    {
    }

    tree_const_iterator& operator=(const tree_const_iterator& other)
    {
        ptr = other.ptr;
        return *this;
    }

    ~tree_const_iterator()
    {
    }

public:
    reference operator*() const
    {
        return static_cast<node_pointer>(ptr)->value;
    }

    pointer operator->() const
    {
        return &(operator*());
    }

    tree_const_iterator& operator++()
    {
        ptr = tree_iter_next<node_base_pointer>(static_cast<node_pointer>(ptr));
        return *this;
    }

    tree_const_iterator operator++(int)
    {
        tree_const_iterator t = *this;
        ++(*this);
        return t;
    }

    tree_const_iterator& operator--()
    {
        ptr = static_cast<node_base_pointer>(tree_iter_next<node_pointer>(ptr));
        return *this;
    }

    tree_const_iterator operator--(int)
    {
        tree_const_iterator t = *this;
        --(*this);
        return t;
    }

    bool operator==(const tree_const_iterator& other) const
    {
        return ptr == other.ptr;
    }

    bool operator!=(const tree_const_iterator& other) const
    {
        return !(*this == other);
    }

private:
    node_base_pointer ptr;
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
    typedef tree_const_iterator<value_type, difference_type> const_iterator;

private:
    typedef typename tree_node_types<value_type>::end_node_type end_node_type;
    typedef typename tree_node_types<value_type>::node_type node_type;
    typedef typename tree_node_types<value_type>::node_base_pointer node_base_pointer;
    typedef typename tree_node_types<value_type>::node_pointer node_pointer;
    typedef typename allocator_type::template rebind<node_type>::other node_allocator;

public:
    tree()
        : alloc_(node_allocator()),
          value_alloc_(allocator_type()),
          comp_(value_compare()),
          end_node_(),
          size_(0)
    {
        begin_iter_ = &end_node_;
    }

    tree(const tree& other)
        : alloc_(other.alloc_),
          value_alloc_(other.value_alloc_),
          comp_(value_compare()),
          end_node_(),
          size_(other.size_)
    {
        begin_iter_ = &end_node_;
    }

    tree& operator=(const tree& other)
    {
        end_node_ = other.end_node_;
        size_ = other.size_;
        return *this;
    }

    ~tree()
    {
    }

public:
    void insert(const T& value)
    {
        node_base_pointer parent;
        node_base_pointer& child = find_equal(parent, value);
        if (child == NULL) {
            node_pointer ptr = construct_node(value);
            ptr->parent = parent;
            child = static_cast<node_base_pointer>(ptr);
        }
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

    size_type size() const
    {
        return size_;
    }

    size_type max_size() const
    {
        return std::min(alloc_.max_size(),
                        static_cast<size_type>(std::numeric_limits<difference_type>::max()));
    }

    value_compare& value_comp()
    {
        return comp_;
    }

    const value_compare& value_comp() const
    {
        return comp_;
    }

private:
    node_pointer root()
    {
        return static_cast<node_pointer>(end_node_.left);
    }

    node_base_pointer* root_ptr()
    {
        return static_cast<node_base_pointer*>(&end_node_.left);
    }

    node_base_pointer end_node()
    {
        return static_cast<node_base_pointer>(&end_node_);
    }

private:
    node_pointer construct_node(const T& value)
    {
        node_pointer new_node = alloc_.allocate(1);
        alloc_.construct(new_node, node_type());
        value_alloc_.construct(&new_node->value, value);
        return new_node;
    }

    template <typename Key>
    node_base_pointer& find_equal(node_base_pointer& parent, const Key& value)
    {
        node_pointer node = root();
        node_base_pointer* ptr = root_ptr();

        if (node != NULL) {
            while (true) {
                if (value_comp()(value, node->value)) {
                    // value < node->value
                    if (node->left != NULL) {
                        ptr = &node->left;
                        node = static_cast<node_pointer>(node->left);
                    } else {
                        parent = static_cast<node_base_pointer>(node);
                        return node->left;
                    }
                } else if (value_comp()(node->value, value)) {
                    // value > node->value
                    if (node->right != NULL) {
                        ptr = &node->right;
                        node = static_cast<node_pointer>(node->right);
                    } else {
                        parent = static_cast<node_base_pointer>(node);
                        return node->right;
                    }
                } else {
                    // value == node->value
                    parent = static_cast<node_base_pointer>(node);
                    return *ptr;
                }
            }
        }
        parent = static_cast<node_base_pointer>(end_node());
        return parent->left;
    }

private:
    node_allocator alloc_;
    allocator_type value_alloc_;
    value_compare comp_;
    end_node_type end_node_;
    node_base_pointer begin_iter_;
    size_type size_;
};
