/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_types.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 17:35:55 by mleblanc          #+#    #+#             */
/*   Updated: 2022/05/05 01:03:32 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstddef>

namespace ft
{
class tree_end_node;
class tree_base_node;
template <typename T>
class tree_node;

struct tree_base_node_types {
    // clang-format off
    typedef tree_end_node   end_node_type;
    typedef end_node_type*  end_node_pointer;
    typedef tree_base_node  base_node_type;
    typedef base_node_type* node_base_pointer;
    // clang-format on
};

template <typename T>
struct tree_node_types : tree_base_node_types {
    // clang-format off
    typedef tree_node<T>     node_type;
    typedef node_type*       node_pointer;
    typedef const node_type* const_node_pointer;
    // clang-format on
};

class tree_end_node
{
public:
    typedef tree_base_node_types::node_base_pointer node_base_pointer;

public:
    tree_end_node() : left(NULL)
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
    tree_base_node() : right(NULL), parent(NULL), is_black(false)
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
    tree_node() : value(T())
    {
    }

public:
    T value;
};
} // namespace ft
