/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_types.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 17:35:55 by mleblanc          #+#    #+#             */
/*   Updated: 2022/04/28 01:01:06 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{
class tree_end_node;
class tree_base_node;
template <typename T>
class tree_node;

struct tree_base_node_types {
    typedef tree_end_node end_node_type;
    typedef end_node_type* end_node_pointer;
    typedef tree_base_node base_node_type;
    typedef base_node_type* node_base_pointer;
};

template <typename T>
struct tree_node_types : tree_base_node_types {
    typedef tree_node<T> node_type;
    typedef node_type* node_pointer;
    typedef const node_type* const_node_pointer;
};
} // namespace ft
