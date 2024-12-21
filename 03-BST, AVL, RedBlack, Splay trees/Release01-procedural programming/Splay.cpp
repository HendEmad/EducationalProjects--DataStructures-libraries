#include "DS.h"
#include <iostream>
using namespace std;

// Function to create a new SplayNode
SplayNode* splay_create_node(int key) {
    SplayNode* node = new SplayNode;
    node->key = key;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

// Function to perform a right rotation
SplayNode* splay_rotate_right(SplayNode* x) {
    SplayNode* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

// Function to perform a left rotation
SplayNode* splay_rotate_left(SplayNode* x) {
    SplayNode* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

// Splay operation to move the key to root
SplayNode* splay(SplayNode* root, int key) {
    if (!root || root->key == key) return root;

    if (key < root->key) {
        if (!root->left) return root;

        if (key < root->left->key) {
            root->left->left = splay(root->left->left, key);
            root = splay_rotate_right(root);
        } else if (key > root->left->key) {
            root->left->right = splay(root->left->right, key);
            if (root->left->right) root->left = splay_rotate_left(root->left);
        }

        return root->left ? splay_rotate_right(root) : root;
    } else {
        if (!root->right) return root;

        if (key > root->right->key) {
            root->right->right = splay(root->right->right, key);
            root = splay_rotate_left(root);
        } else if (key < root->right->key) {
            root->right->left = splay(root->right->left, key);
            if (root->right->left) root->right = splay_rotate_right(root->right);
        }

        return root->right ? splay_rotate_left(root) : root;
    }
}

// Function to insert a key into the Splay Tree
SplayNode* splay_insert(SplayNode* root, int key) {
    if (!root) return splay_create_node(key);

    root = splay(root, key);

    if (root->key == key) return root;

    SplayNode* node = splay_create_node(key);

    if (key < root->key) {
        node->right = root;
        node->left = root->left;
        root->left = nullptr;
    } else {
        node->left = root;
        node->right = root->right;
        root->right = nullptr;
    }

    return node;
}

// Function to delete a key from the Splay Tree
SplayNode* splay_delete(SplayNode* root, int key) {
    if (!root) return nullptr;

    root = splay(root, key);

    if (root->key != key) return root;

    if (!root->left) {
        SplayNode* temp = root;
        root = root->right;
        delete temp;
    } else {
        SplayNode* temp = root;
        root = splay(root->left, key);
        root->right = temp->right;
        delete temp;
    }

    return root;
}

// Function to search for a key in the Splay Tree
SplayNode* splay_search(SplayNode* root, int key) {
    return splay(root, key);
}

// Function for inorder traversal of the Splay Tree
void splay_inorder_traversal(SplayNode* root) {
    if (!root) return;
    splay_inorder_traversal(root->left);
    cout << root->key << " ";
    splay_inorder_traversal(root->right);
}

// Function for preorder traversal of the Splay Tree
void splay_preorder_traversal(SplayNode* root) {
    if (!root) return;
    cout << root->key << " ";
    splay_preorder_traversal(root->left);
    splay_preorder_traversal(root->right);
}

// Function for postorder traversal of the Splay Tree
void splay_postorder_traversal(SplayNode* root) {
    if (!root) return;
    splay_postorder_traversal(root->left);
    splay_postorder_traversal(root->right);
    cout << root->key << " ";
}

// Function to calculate the height of the Splay Tree
int splay_height(SplayNode* root) {
    if (!root) return 0;
    int left_height = splay_height(root->left);
    int right_height = splay_height(root->right);
    return max(left_height, right_height) + 1;
}

// Function to count the number of nodes in the Splay Tree
int splay_count_nodes(SplayNode* root) {
    if (!root) return 0;
    return 1 + splay_count_nodes(root->left) + splay_count_nodes(root->right);
}

// Function for finding the kth smallest element in the Splay Tree
void splay_kth_smallest_helper(SplayNode* root, int& k, int& result) {
    if (!root || k <= 0) return;
    splay_kth_smallest_helper(root->left, k, result);
    if (--k == 0) {
        result = root->key;
        return;
    }
    splay_kth_smallest_helper(root->right, k, result);
}

// Function to find the kth smallest element in the Splay Tree
int splay_kth_smallest(SplayNode* root, int k) {
    int result = -1;
    splay_kth_smallest_helper(root, k, result);
    return result;
}
