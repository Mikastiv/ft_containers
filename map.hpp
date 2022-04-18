/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 12:17:41 by mleblanc          #+#    #+#             */
/*   Updated: 2022/04/18 12:31:45 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>

#include "utility.hpp"

template<
    typename Key,
    typename T,
    typename Compare = ft::less<Key>,
    typename Allocator = std::allocator<ft::pair<const Key, T> >
> class map{};
