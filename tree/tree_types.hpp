/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_types.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 17:35:55 by mleblanc          #+#    #+#             */
/*   Updated: 2022/05/05 15:59:24 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstddef>

namespace ft
{
template <typename T>
class tree_end_node;

template <typename T>
class tree_node;

template <typename T>
struct tree_node_types {
    // clang-format off
    typedef tree_end_node<T> end_node_type;
    typedef end_node_type*   end_node_pointer;
    typedef tree_node<T>     node_type;
    typedef node_type*       node_pointer;
    // clang-format on
};

template <typename T>
class tree_end_node
{
public:
    typedef typename tree_node_types<T>::node_pointer node_pointer;

public:
    tree_end_node()
        : left(NULL)
    {
    }

public:
    node_pointer left;
};

template <typename T>
class tree_node : public tree_node_types<T>::end_node_type
{
public:
    typedef typename tree_node_types<T>::end_node_pointer end_node_pointer;
    typedef typename tree_node_types<T>::node_pointer node_pointer;

public:
    tree_node()
        : right(NULL),
          parent(NULL),
          is_black(false)
    {
    }

    node_pointer get_parent() const
    {
        return static_cast<node_pointer>(parent);
    }

    void set_parent(node_pointer ptr)
    {
        parent = static_cast<end_node_pointer>(ptr);
    }

public:
    node_pointer right;
    end_node_pointer parent;
    bool is_black;
    T value;
};
} // namespace ft
