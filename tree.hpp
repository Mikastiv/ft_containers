/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 22:03:04 by mleblanc          #+#    #+#             */
/*   Updated: 2022/04/23 00:25:16 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stddef.h>
#include <iterator>

class tree_end_node;

template <typename T>
class tree_node;

template <typename T>
struct tree_node_types {
    typedef tree_end_node end_node_type;
    typedef tree_end_node* end_node_ptr;
    typedef tree_end_node* iter_ptr;
    typedef tree_end_node* parent_pointer;
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
    typedef typename tree_node_types<T>::parent_pointer parent_pointer;
    typedef typename tree_node_types<T>::node_pointer node_pointer;

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
    parent_pointer parent;
    node_pointer right;
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
    typedef typename tree_node_types<T>::end_node_ptr end_node_ptr;
    typedef typename tree_node_types<T>::node_pointer node_pointer;
    typedef typename tree_node_types<T>::iter_pointer iter_pointer;

public:
    typedef std::bidirectional_iterator_tag iterator_category;
    typedef T value_type;
    typedef DiffType difference_type;
    typedef value_type& reference;
    typedef value_type* pointer;

public:
    tree_iterator() : ptr(NULL) {}
    tree_iterator(const tree_iterator& other) : ptr(other.ptr) {}
    tree_iterator(node_pointer p) : ptr(static_cast<iter_pointer>(p)) {}
    tree_iterator(end_node_ptr p) : ptr(static_cast<iter_pointer>(p)) {}
    tree_iterator& operator=(const tree_iterator& other)
    {
        ptr = other.ptr;
        return *this;
    }
    ~tree_iterator(){}

public:
    reference operator*() const
    {
        return get_node_ptr()->value;
    }

    pointer operator->() const
    {
        return &(operator*());
    }

    tree_iterator& operator++()
    {
        ptr = tree_iter_next<iter_pointer>(static_cast<node_pointer>(ptr));
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
        ptr = tree_iter_next<node_pointer>(ptr);
        return *this;
    }

    tree_iterator operator--(int)
    {
        tree_iterator t = *this;
        --(*this);
        return t;
    }

private:
    node_pointer get_node_ptr() const
    {
        return static_cast<node_pointer>(ptr);
    }

private:
    iter_pointer ptr;
};

template <typename T, typename Compare, typename Allocator>
class tree
{
public:
    typedef T value_type;
    typedef Compare compare_type;
    typedef Allocator allocator_type;
    typedef typename allocator_type::size_type size_type;
    typedef typename allocator_type::difference_type difference_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef typename allocator_type::pointer pointer;
    typedef typename allocator_type::const_pointer const_pointer;

private:
    typedef typename tree_node_types<value_type>::node_type node_type;
    typedef typename tree_node_types<value_type>::end_node_type end_node_type;
    typedef typename tree_node_types<value_type>::node_pointer node_pointer;
    typedef typename tree_node_types<value_type>::const_node_pointer const_node_pointer;
    typedef typename tree_node_types<value_type>::parent_pointer parent_pointer;
    typedef typename allocator_type::template rebind<node_type>::other node_allocator;

public:
    tree()
        : alloc_(node_allocator()),
          value_alloc_(allocator_type()),
          end_node_(),
          size_(0)
    {
    }

    tree(const tree& other)
        : alloc_(other.alloc_),
          value_alloc_(other.value_alloc_),
          end_node_(other.end_node),
          size_(other.size_)
    {
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
        if (end_node_.left == NULL) {
            end_node_.left = construct_node(value);
            return;
        }
    }

    node_pointer root()
    {
        return static_cast<node_pointer>(end_node_.left);
    }

    const_node_pointer root() const
    {
        return static_cast<const_node_pointer>(end_node_.left);
    }

private:
    node_pointer construct_node(const T& value)
    {
        node_pointer new_node = alloc_.allocate(1);
        alloc_.construct(new_node, node_type());
        value_alloc_.construct(&new_node->value, value);
        return new_node;
    }

private:
    node_allocator alloc_;
    allocator_type value_alloc_;
    end_node_type end_node_;
    size_type size_;
};
