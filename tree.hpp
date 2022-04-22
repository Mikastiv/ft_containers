/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 22:03:04 by mleblanc          #+#    #+#             */
/*   Updated: 2022/04/22 15:32:25 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>

template <typename Ptr>
class tree_end_node;

template <typename T, typename VoidPtr>
class tree_node;

template <typename T, typename VoidPtr = void*>
struct tree_node_types {
    typedef tree_end_node<VoidPtr> end_node_type;
    typedef end_node_type* parent_pointer;
    typedef tree_node<T, VoidPtr> node_type;
    typedef node_type* node_pointer;
};

template <typename Ptr>
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
    Ptr left;
};

template <typename T, typename VoidPtr = void*>
class tree_node : public tree_node_types<T, VoidPtr>::end_node_type
{
  public:
    typedef tree_node_types<T, VoidPtr> node_types;
    typedef typename node_types::parent_pointer parent_pointer;
    typedef typename node_types::node_pointer node_pointer;

  public:
    tree_node()
        : tree_node_types<T, VoidPtr>::end_node_type(),
          parent(NULL),
          right(NULL),
          value(T()),
          is_black(false)
    {
    }

    tree_node(const T& v)
        : tree_node_types<T, VoidPtr>::end_node_type(),
          value(v),
          parent(NULL),
          right(NULL),
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

template <typename T, typename Compare, typename Allocator>
class tree
{
  public:
    typedef T value_type;
    typedef Compare compare_type;
    typedef Allocator allocator_type;
    typedef typename allocator_type::size_type size_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef typename allocator_type::pointer pointer;
    typedef typename allocator_type::const_pointer const_pointer;

  private:
    typedef tree_node_types<value_type> node_types;
    typedef typename node_types::node_type node_type;
    typedef typename node_types::end_node_type end_node_type;
    typedef typename node_types::node_pointer node_pointer;
    typedef typename node_types::parent_pointer parent_pointer;
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
        end_node_.left = construct_node(&end_node_, value);
    }

  private:
    node_pointer construct_node(parent_pointer p, const T& value)
    {
        node_pointer new_node = alloc_.allocate(1);
        alloc_.construct(new_node, node_type());
        new_node->parent = p;
        new_node->value = value;
        return new_node;
    }

  private:
    node_allocator alloc_;
    allocator_type value_alloc_;
    end_node_type end_node_;
    size_type size_;
};
