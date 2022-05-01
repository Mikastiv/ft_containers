/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_print.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 00:16:52 by mleblanc          #+#    #+#             */
/*   Updated: 2022/05/01 00:18:05 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <sstream>

namespace ft
{
template <typename NodePtr>
std::string traverse_root(NodePtr root)
{

    if (root == NULL) {
        return "";
    }

    std::stringstream ss;
    ss << (root->is_black ? "B" : "R");

    traverse_nodes(ss, "", "\\──", static_cast<NodePtr>(root->right), root->left != NULL);
    traverse_nodes(ss, "", "└──", static_cast<NodePtr>(root->left), false);

    ss << "\n";
    return ss.str();
}

template <typename NodePtr>
void traverse_nodes(std::stringstream& ss, const std::string& padding, const std::string& pointer,
                    NodePtr node, bool has_left_sibling)
{
    if (node != NULL) {
        ss << "\n";
        ss << padding;
        ss << pointer;
        ss << (node->is_black ? "B" : "R");

        std::stringstream padding_builder;
        padding_builder << padding;
        if (has_left_sibling) {
            padding_builder << "│  ";
        } else {
            padding_builder << "   ";
        }

        std::string padding_for_both = padding_builder.str();

        traverse_nodes(ss, padding_for_both, "\\──", static_cast<NodePtr>(node->right),
                       node->left != NULL);
        traverse_nodes(ss, padding_for_both, "└──", static_cast<NodePtr>(node->left), false);
    }
}
} // namespace ft
