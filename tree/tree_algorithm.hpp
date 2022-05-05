/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_algorithm.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 23:01:54 by mleblanc          #+#    #+#             */
/*   Updated: 2022/05/05 16:52:08 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "tree_types.hpp"
#include <cstddef>
#include <iostream>

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

template <typename NodePtr>
bool tree_invariant(NodePtr root)
{
    bool count_left = 0;
    if (root->left) {
        count_left = tree_invariant(root->left);
    }

    bool count_right = 0;
    if (root->right) {
        count_right = tree_invariant(root->right);
    }

    return count_left == count_right;
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
        NodePtr uncle = tree_node_sibling(z->get_parent());

        if (tree_is_left_child(z->get_parent())) {
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
void tree_transplant_node(NodePtr pos, NodePtr& node)
{
    node->is_black = pos->is_black;
    node->parent = pos->parent;
    if (tree_is_left_child(pos)) {
        node->parent->left = node;
    } else {
        node->get_parent()->right = node;
    }
    node->left = pos->left;
    node->left->set_parent(node);
    node->right = pos->right;
    if (node->right) {
        node->right->set_parent(node);
    }
}

/// This function should only be called to fix a double black node case
template <typename NodePtr>
void tree_balance_after_remove(NodePtr root, NodePtr x_parent)
{
    NodePtr x = NULL;

    ft::tree_node<int>* z = reinterpret_cast<ft::tree_node<int>*>(x_parent);
    std::cout << "Parent: " << z->value << std::endl;

    while (root != x && tree_node_is_black(x)) {
        if (x == x_parent->left) {
            NodePtr w = x_parent->right;
            if (!w->is_black) {
                x_parent->is_black = false;
                w->is_black = true;
                if (root == x_parent) {
                    root = w;
                }
                tree_rotate_left(x_parent);
                w = x_parent->right;
            }
            if (tree_node_is_black(w->left) && tree_node_is_black(w->right)) {
                w->is_black = false;
                x = x_parent;
                x_parent = x->get_parent();
            } else {
                if (tree_node_is_black(w->right)) {
                    w->left->is_black = true;
                    w->is_black = false;
                    tree_rotate_right(w);
                    w = x_parent->right;
                }
                w->is_black = x_parent->is_black;
                x_parent->is_black = true;
                w->right->is_black = true;
                tree_rotate_left(x_parent);
                break;
            }
        } else {
            NodePtr w = x_parent->left;
            if (!w->is_black) {
                if (root == x_parent) {
                    root = w;
                }
                x_parent->is_black = false;
                w->is_black = true;
                tree_rotate_right(x_parent);
                w = x_parent->left;
            }
            if (tree_node_is_black(w->right) && tree_node_is_black(w->left)) {
                w->is_black = false;
                x = x_parent;
                x_parent = x->get_parent();
            } else {
                if (tree_node_is_black(w->left)) {
                    w->right->is_black = true;
                    w->is_black = false;
                    tree_rotate_left(w);
                    w = x_parent->left;
                }
                w->is_black = x_parent->is_black;
                x_parent->is_black = true;
                w->left->is_black = true;
                tree_rotate_right(x_parent);
                break;
            }
        }
    }
    if (x) {
        x->is_black = true;
    }
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

    // Replace y with x
    if (x != NULL) {
        x->parent = y->parent;
    }
    if (tree_is_left_child(y)) {
        y->parent->left = x;
    } else {
        y->get_parent()->right = x;
    }

    NodePtr x_parent = y->get_parent();

    // Keep track of removed color before possibly transplanting y into target's place
    bool removed_black = y->is_black;

    // If y is target's in order successor, transplant y into target's place
    if (y != target) {
        tree_transplant_node(target, y);
        if (target == root) {
            root = y;
        }
    }

    // Balance tree only if a black node was removed
    if (removed_black) {
        // Tree is empty, nothing to do (root double black case)
        if (root == NULL) {
            return;
        }

        // x is red, color it black
        if (x != NULL) {
            x->is_black = true;
            return;
        }

        tree_balance_after_remove(root, x_parent);
    }
}
} // namespace ft
