/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_iterator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 17:37:17 by mleblanc          #+#    #+#             */
/*   Updated: 2022/04/28 22:36:04 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "tree_types.hpp"

namespace ft
{
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
        ptr = ptr->get_parent();
    }
    return ptr->get_parent();
}

template <typename NodePtr, typename IterPtr>
IterPtr tree_iter_prev(IterPtr ptr)
{
    if (ptr->left != NULL) {
        return tree_max(ptr->left);
    }
    NodePtr nptr = static_cast<NodePtr>(ptr);
    while (tree_is_left_child(nptr)) {
        nptr = nptr->get_parent();
    }
    return nptr->get_parent();
}

template <typename T, typename DiffType>
class const_tree_iterator;

template <typename T, typename DiffType>
class tree_iterator
{
// clang-format off
public:
    typedef std::bidirectional_iterator_tag  iterator_category;
    typedef T                                value_type;
    typedef T&                               reference;
    typedef T*                               pointer;
    typedef DiffType                         difference_type;
    typedef const_tree_iterator<T, DiffType> const_iterator;

private:
    typedef typename tree_node_types<T>::node_base_pointer node_base_pointer;
    typedef typename tree_node_types<T>::end_node_pointer  end_node_pointer;
    typedef typename tree_node_types<T>::node_pointer      node_pointer;
// clang-format on

public:
    tree_iterator()
        : ptr(NULL)
    {
    }

    tree_iterator(end_node_pointer p)
        : ptr(p)
    {
    }

    tree_iterator(node_base_pointer p)
        : ptr(static_cast<end_node_pointer>(p))
    {
    }

    tree_iterator(node_pointer p)
        : ptr(static_cast<end_node_pointer>(p))
    {
    }

public:
    end_node_pointer& base()
    {
        return ptr;
    }

    const end_node_pointer& base() const
    {
        return ptr;
    }

    node_pointer node_ptr() const
    {
        return static_cast<node_pointer>(ptr);
    }

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
        ptr = tree_iter_next<end_node_pointer>(static_cast<node_base_pointer>(ptr));
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
        ptr = tree_iter_prev<node_base_pointer>(ptr);
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

    bool operator==(const const_iterator& other) const
    {
        return ptr == other.base();
    }

    bool operator!=(const tree_iterator& other) const
    {
        return !(*this == other);
    }

    bool operator!=(const const_iterator& other) const
    {
        return !(*this == other);
    }

private:
    end_node_pointer ptr;
};

template <typename T, typename DiffType>
class const_tree_iterator
{
// clang-format off
public:
    typedef std::bidirectional_iterator_tag iterator_category;
    typedef T                               value_type;
    typedef const T&                        reference;
    typedef const T*                        pointer;
    typedef DiffType                        difference_type;
    typedef tree_iterator<T, DiffType>      non_const_iterator;

private:
    typedef typename tree_node_types<T>::node_base_pointer node_base_pointer;
    typedef typename tree_node_types<T>::end_node_pointer  end_node_pointer;
    typedef typename tree_node_types<T>::node_pointer      node_pointer;
// clang-format on

public:
    const_tree_iterator()
        : ptr(NULL)
    {
    }

    const_tree_iterator(end_node_pointer p)
        : ptr(p)
    {
    }

    const_tree_iterator(node_base_pointer p)
        : ptr(static_cast<end_node_pointer>(p))
    {
    }

    const_tree_iterator(node_pointer p)
        : ptr(static_cast<end_node_pointer>(p))
    {
    }

    const_tree_iterator(non_const_iterator it)
        : ptr(it.base())
    {
    }

public:
    end_node_pointer& base()
    {
        return ptr;
    }

    const end_node_pointer& base() const
    {
        return ptr;
    }

    node_pointer node_ptr() const
    {
        return static_cast<node_pointer>(ptr);
    }

    reference operator*() const
    {
        return static_cast<node_pointer>(ptr)->value;
    }

    pointer operator->() const
    {
        return &(operator*());
    }

    const_tree_iterator& operator++()
    {
        ptr = tree_iter_next<end_node_pointer>(static_cast<node_base_pointer>(ptr));
        return *this;
    }

    const_tree_iterator operator++(int)
    {
        const_tree_iterator t = *this;
        ++(*this);
        return t;
    }

    const_tree_iterator& operator--()
    {
        ptr = tree_iter_prev<node_base_pointer>(ptr);
        return *this;
    }

    const_tree_iterator operator--(int)
    {
        const_tree_iterator t = *this;
        --(*this);
        return t;
    }

    bool operator==(const const_tree_iterator& other) const
    {
        return ptr == other.ptr;
    }

    bool operator==(const non_const_iterator& other) const
    {
        return ptr == other.base();
    }

    bool operator!=(const const_tree_iterator& other) const
    {
        return !(*this == other);
    }

    bool operator!=(const non_const_iterator& other) const
    {
        return !(*this == other);
    }

private:
    end_node_pointer ptr;
};

} // namespace ft
