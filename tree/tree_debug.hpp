/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_debug.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 00:16:52 by mleblanc          #+#    #+#             */
/*   Updated: 2022/05/18 16:45:11 by mleblanc         ###   ########.fr       */
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
    ss << root->value << (root->is_black ? "(B)" : "(R)");

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
        ss << node->value << (node->is_black ? "(B)" : "(R)");

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

template <typename NodePtr>
std::size_t tree_black_height(NodePtr ptr)
{
    if (ptr == NULL) {
        return 1;
    }

    if (ptr->left != NULL && ptr->left->parent != ptr)
        return 0;
    if (ptr->right != NULL && ptr->right->parent != ptr)
        return 0;
    if (ptr->left == ptr->right && ptr->left != NULL)
        return 0;

    if (!ptr->is_black) {
        if (ptr->left && !ptr->left->is_black)
            return 0;
        if (ptr->right && !ptr->right->is_black)
            return 0;
    }

    std::size_t h = tree_black_height(ptr->left);
    if (h == 0)
        return 0;
    if (h != tree_black_height(ptr->right))
        return 0;

    return h + ptr->is_black;
}

template <typename NodePtr>
bool tree_is_red_black_tree(NodePtr root)
{
    if (root == NULL) {
        return true;
    }

    if (root->parent == NULL) {
        return false;
    }

    if (!tree_is_left_child(root)) {
        return false;
    }

    if (!root->is_black) {
        return false;
    }

    return tree_black_height(root) != 0;
}
} // namespace ft
