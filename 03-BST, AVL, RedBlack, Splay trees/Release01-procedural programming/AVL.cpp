#include "DS.h"
#include <iostream>
using namespace std;

// Function to create a new AVLNode
AVLNode* avl_create_node(int key) {
    AVLNode* node = new AVLNode;
    node->key = key;
    node->left = nullptr;
    node->right = nullptr;
    node->height = 1; 
    return node;
}

// Function to get the height of an AVLNode
int avl_height(AVLNode* node) {
    return node ? node->height : 0;
}

// Function to calculate the balance factor of an AVLNode
int avl_get_balance(AVLNode* node) {
    return node ? avl_height(node->left) - avl_height(node->right) : 0;
}

// Function to perform a right rotation
AVLNode* avl_rotate_right(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T = x->right;

    x->right = y;
    y->left = T;

    y->height = max(avl_height(y->left), avl_height(y->right)) + 1;
    x->height = max(avl_height(x->left), avl_height(x->right)) + 1;

    return x;
}

// Function to perform a left rotation
AVLNode* avl_rotate_left(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T = y->left;

    y->left = x;
    x->right = T;

    x->height = max(avl_height(x->left), avl_height(x->right)) + 1;
    y->height = max(avl_height(y->left), avl_height(y->right)) + 1;

    return y;
}

// Function to insert a key into the AVL Tree
AVLNode* avl_insert(AVLNode* root, int key) {
    if (!root) return avl_create_node(key);

    if (key < root->key)
        root->left = avl_insert(root->left, key);
    else if (key > root->key)
        root->right = avl_insert(root->right, key);
    else
        return root; 

    root->height = 1 + max(avl_height(root->left), avl_height(root->right));

    int balance = avl_get_balance(root);

    // Left Left Case
    if (balance > 1 && key < root->left->key)
        return avl_rotate_right(root);

    // Right Right Case
    if (balance < -1 && key > root->right->key)
        return avl_rotate_left(root);

    // Left Right Case
    if (balance > 1 && key > root->left->key) {
        root->left = avl_rotate_left(root->left);
        return avl_rotate_right(root);
    }

    // Right Left Case
    if (balance < -1 && key < root->right->key) {
        root->right = avl_rotate_right(root->right);
        return avl_rotate_left(root);
    }

    return root;
}

// Function to find the node with the smallest key
AVLNode* avl_find_min(AVLNode* root) {
    while (root->left)
        root = root->left;
    return root;
}

// Function to delete a key from the AVL Tree
AVLNode* avl_delete(AVLNode* root, int key) {
    if (!root) return nullptr;

    if (key < root->key)
        root->left = avl_delete(root->left, key);
    else if (key > root->key)
        root->right = avl_delete(root->right, key);
    else {
        if (!root->left || !root->right) {
            AVLNode* temp = root->left ? root->left : root->right;
            delete root;
            return temp;
        }

        AVLNode* temp = avl_find_min(root->right);
        root->key = temp->key;
        root->right = avl_delete(root->right, temp->key);
    }

    root->height = 1 + max(avl_height(root->left), avl_height(root->right));

    int balance = avl_get_balance(root);

    // Left Left Case
    if (balance > 1 && avl_get_balance(root->left) >= 0)
        return avl_rotate_right(root);

    // Left Right Case
    if (balance > 1 && avl_get_balance(root->left) < 0) {
        root->left = avl_rotate_left(root->left);
        return avl_rotate_right(root);
    }

    // Right Right Case
    if (balance < -1 && avl_get_balance(root->right) <= 0)
        return avl_rotate_left(root);

    // Right Left Case
    if (balance < -1 && avl_get_balance(root->right) > 0) {
        root->right = avl_rotate_right(root->right);
        return avl_rotate_left(root);
    }

    return root;
}

// Function to search for a key in the AVL Tree
AVLNode* avl_search(AVLNode* root, int key) {
    if (!root || root->key == key) return root;

    if (key < root->key)
        return avl_search(root->left, key);
    else
        return avl_search(root->right, key);
}

// Function for inorder traversal of the AVL Tree
void avl_inorder_traversal(AVLNode* root) {
    if (!root) return;
    avl_inorder_traversal(root->left);
    cout << root->key << " ";
    avl_inorder_traversal(root->right);
}

// Function for preorder traversal of the AVL Tree
void avl_preorder_traversal(AVLNode* root) {
    if (!root) return;
    cout << root->key << " ";
    avl_preorder_traversal(root->left);
    avl_preorder_traversal(root->right);
}

// Function for postorder traversal of the AVL Tree
void avl_postorder_traversal(AVLNode* root) {
    if (!root) return;
    avl_postorder_traversal(root->left);
    avl_postorder_traversal(root->right);
    cout << root->key << " ";
}

// Function to count the number of nodes in the AVL Tree
int avl_count_nodes(AVLNode* root) {
    if (!root) return 0;
    return 1 + avl_count_nodes(root->left) + avl_count_nodes(root->right);
}

// Function for finding the kth smallest element in the AVL Tree
void avl_kth_smallest_helper(AVLNode* root, int& k, int& result) {
    if (!root || k <= 0) return;

    avl_kth_smallest_helper(root->left, k, result);
    if (--k == 0) {
        result = root->key;
        return;
    }
    avl_kth_smallest_helper(root->right, k, result);
}

// Function to find the kth smallest element in the AVL Tree
int avl_kth_smallest(AVLNode* root, int k) {
    int result = -1;
    avl_kth_smallest_helper(root, k, result);
    return result;
}
