#include "DS.h"
#include <iostream>
using namespace std;

// Function to create a new RBNode
RBNode* rb_create_node(int key) {
    RBNode* node = new RBNode;
    node->key = key;
    node->color = RED;
    node->left = nullptr;
    node->right = nullptr;
    node->parent = nullptr;
    return node;
}

// Function to perform a left rotation
RBNode* rb_rotate_left(RBNode* root, RBNode* x) {
    RBNode* y = x->right;
    x->right = y->left;
    if (y->left) y->left->parent = x;

    y->parent = x->parent;
    if (!x->parent)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;

    return root;
}

// Function to perform a right rotation
RBNode* rb_rotate_right(RBNode* root, RBNode* y) {
    RBNode* x = y->left;
    y->left = x->right;
    if (x->right) x->right->parent = y;

    x->parent = y->parent;
    if (!y->parent)
        root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    x->right = y;
    y->parent = x;

    return root;
}

// Function to transplant nodes in the Red-Black Tree
RBNode* rb_transplant(RBNode* root, RBNode* u, RBNode* v) {
    if (!u->parent)
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;

    if (v)
        v->parent = u->parent;

    return root;
}

// Function to fix violations after insertion
RBNode* rb_fix_insert(RBNode* root, RBNode* z) {
    while (z->parent && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            RBNode* y = z->parent->parent->right;
            if (y && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    root = rb_rotate_left(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                root = rb_rotate_right(root, z->parent->parent);
            }
        } else {
            RBNode* y = z->parent->parent->left;
            if (y && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    root = rb_rotate_right(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                root = rb_rotate_left(root, z->parent->parent);
            }
        }
    }
    root->color = BLACK;
    return root;
}

// Function to insert a key into the Red-Black Tree
RBNode* rb_insert(RBNode* root, int key) {
    RBNode* z = rb_create_node(key);
    RBNode* y = nullptr;
    RBNode* x = root;

    while (x) {
        y = x;
        if (key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;
    if (!y)
        root = z;
    else if (key < y->key)
        y->left = z;
    else
        y->right = z;

    return rb_fix_insert(root, z);
}

// Function to fix violations after deletion
RBNode* rb_fix_delete(RBNode* root, RBNode* x) {
    while (x != root && (!x || x->color == BLACK)) {
        if (x == x->parent->left) {
            RBNode* w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                root = rb_rotate_left(root, x->parent);
                w = x->parent->right;
            }
            if ((!w->left || w->left->color == BLACK) && (!w->right || w->right->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            } else {
                if (!w->right || w->right->color == BLACK) {
                    if (w->left) w->left->color = BLACK;
                    w->color = RED;
                    root = rb_rotate_right(root, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                if (w->right) w->right->color = BLACK;
                root = rb_rotate_left(root, x->parent);
                x = root;
            }
        } else {
            RBNode* w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                root = rb_rotate_right(root, x->parent);
                w = x->parent->left;
            }
            if ((!w->left || w->left->color == BLACK) && (!w->right || w->right->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            } else {
                if (!w->left || w->left->color == BLACK) {
                    if (w->right) w->right->color = BLACK;
                    w->color = RED;
                    root = rb_rotate_left(root, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                if (w->left) w->left->color = BLACK;
                root = rb_rotate_right(root, x->parent);
                x = root;
            }
        }
    }
    if (x) x->color = BLACK;
    return root;
}

// Function to find the minimum node in a subtree
RBNode* rb_find_min(RBNode* node) {
    while (node && node->left) {
        node = node->left;
    }
    return node;
}

// Function to delete a key from the Red-Black Tree
RBNode* rb_delete(RBNode* root, int key) {
    RBNode* z = rb_search(root, key);
    if (!z) return root;

    RBNode* y = z;
    RBNode* x = nullptr;
    RBColor original_color = y->color;

    if (!z->left) {
        x = z->right;
        root = rb_transplant(root, z, z->right);
    } else if (!z->right) {
        x = z->left;
        root = rb_transplant(root, z, z->left);
    } else {
        y = rb_find_min(z->right);
        original_color = y->color;
        x = y->right;
        if (y->parent == z) {
            if (x) x->parent = y;
        } else {
            root = rb_transplant(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        root = rb_transplant(root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    delete z;

    if (original_color == BLACK)
        root = rb_fix_delete(root, x);

    return root;
}

// Function to search for a key in the Red-Black Tree
RBNode* rb_search(RBNode* root, int key) {
    while (root && root->key != key) {
        if (key < root->key)
            root = root->left;
        else
            root = root->right;
    }
    return root;
}

// Function for inorder traversal of the Red-Black Tree
void rb_inorder_traversal(RBNode* root) {
    if (!root) return;
    rb_inorder_traversal(root->left);
    cout << root->key << " ";
    rb_inorder_traversal(root->right);
}

// Function for preorder traversal of the Red-Black Tree
void rb_preorder_traversal(RBNode* root) {
    if (!root) return;
    cout << root->key << " ";
    rb_preorder_traversal(root->left);
    rb_preorder_traversal(root->right);
}

// Function for postorder traversal of the Red-Black Tree
void rb_postorder_traversal(RBNode* root) {
    if (!root) return;
    rb_postorder_traversal(root->left);
    rb_postorder_traversal(root->right);
    cout << root->key << " ";
}

// Function to calculate the height of the Red-Black Tree
int rb_height(RBNode* root) {
    if (!root) return 0;
    int left_height = rb_height(root->left);
    int right_height = rb_height(root->right);
    return max(left_height, right_height) + 1;
}

// Function to count the number of nodes in the Red-Black Tree
int rb_count_nodes(RBNode* root) {
    if (!root) return 0;
    return 1 + rb_count_nodes(root->left) + rb_count_nodes(root->right);
}

// Function for finding the kth smallest element in the Red-Black Tree
void rb_kth_smallest_helper(RBNode* root, int& k, int& result) {
    if (!root || k <= 0) return;
    rb_kth_smallest_helper(root->left, k, result);
    if (--k == 0) {
        result = root->key;
        return;
    }
    rb_kth_smallest_helper(root->right, k, result);
}

// Function to find the kth smallest element in the Red-Black Tree
int rb_kth_smallest(RBNode* root, int k) {
    int result = -1;
    rb_kth_smallest_helper(root, k, result);
    return result;
}
