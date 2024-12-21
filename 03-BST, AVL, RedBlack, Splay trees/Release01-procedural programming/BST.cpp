#include "DS.h"
#include <iostream>
#include <stack>
using namespace std;

// Function to create a new BSTNode
BSTNode* bst_create_node(int key) {
    BSTNode* node = new BSTNode;
    node->key = key;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

// Function to insert a key into the BST
BSTNode* bst_insert(BSTNode* root, int key) {
    if (!root) return bst_create_node(key);

    if (key < root->key)
        root->left = bst_insert(root->left, key);
    else if (key > root->key)
        root->right = bst_insert(root->right, key);

    return root;
}

// Function to find the minimum value node in the BST
BSTNode* bst_find_min(BSTNode* root) {
    while (root && root->left)
        root = root->left;
    return root;
}

// Function to delete a key from the BST
BSTNode* bst_delete(BSTNode* root, int key) {
    if (!root) return nullptr;

    if (key < root->key)
        root->left = bst_delete(root->left, key);
    else if (key > root->key)
        root->right = bst_delete(root->right, key);
    else {
        if (!root->left) {
            BSTNode* temp = root->right;
            delete root;
            return temp;
        } else if (!root->right) {
            BSTNode* temp = root->left;
            delete root;
            return temp;
        }

        BSTNode* temp = bst_find_min(root->right);
        root->key = temp->key;
        root->right = bst_delete(root->right, temp->key);
    }

    return root;
}

// Function to search for a key in the BST
BSTNode* bst_search(BSTNode* root, int key) {
    if (!root || root->key == key) return root;

    if (key < root->key)
        return bst_search(root->left, key);
    else
        return bst_search(root->right, key);
}

// Function for inorder traversal of the BST
void bst_inorder_traversal(BSTNode* root) {
    if (!root) return;
    bst_inorder_traversal(root->left);
    cout << root->key << " ";
    bst_inorder_traversal(root->right);
}

// Function for preorder traversal of the BST
void bst_preorder_traversal(BSTNode* root) {
    if (!root) return;
    cout << root->key << " ";
    bst_preorder_traversal(root->left);
    bst_preorder_traversal(root->right);
}

// Function for postorder traversal of the BST
void bst_postorder_traversal(BSTNode* root) {
    if (!root) return;
    bst_postorder_traversal(root->left);
    bst_postorder_traversal(root->right);
    cout << root->key << " ";
}

// Function to calculate the height of the BST
int bst_height(BSTNode* root) {
    if (!root) return 0;
    int left_height = bst_height(root->left);
    int right_height = bst_height(root->right);
    return max(left_height, right_height) + 1;
}

// Function to count the number of nodes in the BST
int bst_count_nodes(BSTNode* root) {
    if (!root) return 0;
    return 1 + bst_count_nodes(root->left) + bst_count_nodes(root->right);
}

// Function for finding the kth smallest element in the BST
void bst_kth_smallest_helper(BSTNode* root, int& k, int& result) {
    if (!root || k <= 0) return;

    bst_kth_smallest_helper(root->left, k, result);
    if (--k == 0) {
        result = root->key;
        return;
    }
    bst_kth_smallest_helper(root->right, k, result);
}

// Function to find the kth smallest element in the BST
int bst_kth_smallest(BSTNode* root, int k) {
    int result = -1;
    bst_kth_smallest_helper(root, k, result);
    return result;
}
