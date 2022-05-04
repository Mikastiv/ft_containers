/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_algorithm.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 23:01:54 by mleblanc          #+#    #+#             */
/*   Updated: 2022/05/04 16:04:29 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstddef>

namespace ft
{
template <typename NodePtr>
inline bool tree_is_left_child(NodePtr ptr)
{
    return ptr == ptr->parent->left;
}

template <typename NodePtr>
NodePtr tree_node_sibling(NodePtr ptr)
{
    if (tree_is_left_child(ptr)) {
        return ptr->get_parent()->right;
    } else {
        return ptr->parent->left;
    }
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
    return ptr->parent;
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
    return nptr->parent;
}

template <typename NodePtr>
void tree_rotate_left(NodePtr node)
{
    NodePtr ptr = node->right;

    node->right = ptr->left;
    if (ptr->left != NULL) {
        ptr->left->set_parent(node);
    }
    ptr->left = node;
    ptr->parent = node->parent;
    if (tree_is_left_child(node)) {
        node->parent->left = ptr;
    } else {
        node->get_parent()->right = ptr;
    }
    node->set_parent(ptr);
}

template <typename NodePtr>
void tree_rotate_right(NodePtr node)
{
    NodePtr ptr = node->left;

    node->left = ptr->right;
    if (ptr->right != NULL) {
        ptr->right->set_parent(node);
    }
    ptr->right = node;
    ptr->parent = node->parent;
    if (tree_is_left_child(node)) {
        node->parent->left = ptr;
    } else {
        node->get_parent()->right = ptr;
    }
    node->set_parent(ptr);
}

template <typename NodePtr>
bool tree_node_is_black(NodePtr node)
{
    if (node == NULL || node->is_black) {
        return true;
    }
    return false;
}

template <typename NodePtr>
NodePtr tree_balance_case_1(NodePtr root, NodePtr z, NodePtr uncle)
{
    uncle->is_black = true;
    z = z->get_parent();
    z->is_black = true;
    z = z->get_parent();
    z->is_black = z == root;
    return z;
}

template <typename NodePtr>
void tree_balance_case_3(NodePtr z, void (*rotate)(NodePtr))
{
    z = z->get_parent();
    z->is_black = true;
    z = z->get_parent();
    z->is_black = false;
    rotate(z);
}

/*
// Case 0: Z == root
// Case 1: Z->uncle == RED
// Case 2: Z->uncle == BLACK (triangle)
//
// -Triangle: Right->Left || Left->Right relation
//
//                  O   \
//                 / \   \
//       Uncle->  O   O   \
//                   /    /
//              Z-> O    /
//
// Case 3: Z->uncle == BLACK (line)
//
// -Line: Left->Left || Right->Right relation
//
//                  O   \
//                 / \   \
//       Uncle->  O   O   \
//                     \   \
//                  Z-> O   \
//
*/

template <typename NodePtr>
void tree_balance_after_insert(NodePtr root, NodePtr z)
{
    z->is_black = z == root; // case 0
    while (z != root && !z->get_parent()->is_black) {
        if (tree_is_left_child(z->get_parent())) {
            NodePtr uncle = z->get_parent()->get_parent()->right;

            if (!tree_node_is_black(uncle)) {
                z = tree_balance_case_1(root, z, uncle); // case 1
            } else {
                if (!tree_is_left_child(z)) { // case 2
                    z = z->get_parent();
                    tree_rotate_left(z);
                }
                tree_balance_case_3(z, &tree_rotate_right); // case 3
                return;
            }
        } else {
            NodePtr uncle = z->get_parent()->parent->left;

            if (!tree_node_is_black(uncle)) {
                z = tree_balance_case_1(root, z, uncle); // case 1
            } else {
                if (tree_is_left_child(z)) { // case 2
                    z = z->get_parent();
                    tree_rotate_right(z);
                }
                tree_balance_case_3(z, &tree_rotate_left); // case 3
                return;
            }
        }
    }
}

template <typename NodePtr>
void tree_balance_after_remove(NodePtr root, NodePtr x, NodePtr w)
{
    (void)root;
    (void)x;
    (void)w;
}

template <typename NodePtr>
void tree_remove_node(NodePtr root, NodePtr target)
{
    NodePtr y = target;
    // Find node to replace target if target has 2 child (in order successor)
    if (y->left != NULL && y->right != NULL) {
        y = tree_min(target->right);
    }

    // x is NULL or y's only child
    NodePtr x;
    if (y->left != NULL) {
        x = y->left;
    } else {
        x = y->right;
    }

    // w is x's sibling
    NodePtr w = NULL;
    if (y != root) {
        w = tree_node_sibling(y);
    }

    // Replace y with x
    if (x != NULL) {
        x->parent = y->parent;
    }
    if (tree_is_left_child(y)) {
        y->parent->left = x;
    } else {
        y->get_parent()->right = x;
    }

    // Keep track of removed color before possibly transplanting y into target's place
    bool removed_black = y->is_black;

    // If y is target's in order successor, transplant y into target's place
    if (y != target) {
        y->is_black = target->is_black;
        y->parent = target->parent;
        if (tree_is_left_child(target)) {
            y->parent->left = y;
        } else {
            y->get_parent()->right = y;
        }
        y->left = target->left;
        y->left->set_parent(y);
        y->right = target->right;
        if (y->right) {
            y->right->set_parent(y);
        }
        if (target == root) {
            root = y;
        }
    }

    // Balance tree only if a black node was removed
    if (removed_black && root != NULL) {
        tree_balance_after_remove(root, x, w);
    }
}
} // namespace ft
