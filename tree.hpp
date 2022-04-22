/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 22:03:04 by mleblanc          #+#    #+#             */
/*   Updated: 2022/04/22 00:04:31 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

template <typename T>
struct node {
    node(const T& v) : value(v), parent(), left(), right(), is_black(false)
    {
    }

    T value;
    T* parent;
    T* left;
    T* right;
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

  public:
    tree();
    tree(const tree& other);
    tree& operator=(const tree& other);
    ~tree();

  private:
    typedef node<value_type> node_type;

  private:
    node_type* root_;
};
