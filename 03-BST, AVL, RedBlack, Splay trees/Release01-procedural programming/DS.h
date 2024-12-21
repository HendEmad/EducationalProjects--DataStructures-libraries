#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

// === Binary Search Tree ===
struct BSTNode {
    int key;
    BSTNode* left;
    BSTNode* right;
};
BSTNode* bst_create_node(int key);
BSTNode* bst_insert(BSTNode* root, int key);
BSTNode* bst_delete(BSTNode* root, int key);
BSTNode* bst_search(BSTNode* root, int key);
void bst_inorder_traversal(BSTNode* root);
void bst_preorder_traversal(BSTNode* root);
void bst_postorder_traversal(BSTNode* root);
int bst_height(BSTNode* root);
int bst_count_nodes(BSTNode* root);
int bst_kth_smallest(BSTNode* root, int k);

// === AVL Tree ===
struct AVLNode {
    int key;
    AVLNode* left;
    AVLNode* right;
    int height;
};
AVLNode* avl_create_node(int key);
AVLNode* avl_insert(AVLNode* root, int key);
AVLNode* avl_delete(AVLNode* root, int key);
AVLNode* avl_search(AVLNode* root, int key);
void avl_inorder_traversal(AVLNode* root);
void avl_preorder_traversal(AVLNode* root);
void avl_postorder_traversal(AVLNode* root);
int avl_height(AVLNode* root);
int avl_count_nodes(AVLNode* root);
int avl_kth_smallest(AVLNode* root, int k);

// === Red-Black Tree ===
enum RBColor { RED, BLACK };
struct RBNode {
    int key;
    RBColor color;
    RBNode* left;
    RBNode* right;
    RBNode* parent;
};
RBNode* rb_create_node(int key);
RBNode* rb_insert(RBNode* root, int key);
RBNode* rb_delete(RBNode* root, int key);
RBNode* rb_search(RBNode* root, int key);
void rb_inorder_traversal(RBNode* root);
void rb_preorder_traversal(RBNode* root);
void rb_postorder_traversal(RBNode* root);
int rb_height(RBNode* root);
int rb_count_nodes(RBNode* root);
int rb_kth_smallest(RBNode* root, int k);

// === Splay Tree ===
struct SplayNode {
    int key;
    SplayNode* left;
    SplayNode* right;
};
SplayNode* splay_create_node(int key);
SplayNode* splay_insert(SplayNode* root, int key);
SplayNode* splay_delete(SplayNode* root, int key);
SplayNode* splay_search(SplayNode* root, int key);
void splay_inorder_traversal(SplayNode* root);
void splay_preorder_traversal(SplayNode* root);
void splay_postorder_traversal(SplayNode* root);
int splay_height(SplayNode* root);
int splay_count_nodes(SplayNode* root);
int splay_kth_smallest(SplayNode* root, int k);

#endif