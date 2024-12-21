#include "DS.h"
#include <iostream>
using namespace std;

void test_bst() {
    cout << "\n=== Binary Search Tree ===\n";
    BSTNode* bst_root = nullptr;
    bst_root = bst_insert(bst_root, 50);
    bst_root = bst_insert(bst_root, 30);
    bst_root = bst_insert(bst_root, 70);
    bst_root = bst_insert(bst_root, 20);
    bst_root = bst_insert(bst_root, 40);
    bst_root = bst_insert(bst_root, 60);
    bst_root = bst_insert(bst_root, 80);

    cout << "Inorder Traversal: ";
    bst_inorder_traversal(bst_root);
    cout << endl;

    cout << "Deleting 20, 30, and 50...\n";
    bst_root = bst_delete(bst_root, 20);
    bst_root = bst_delete(bst_root, 30);
    bst_root = bst_delete(bst_root, 50);

    cout << "Inorder Traversal After Deletion: ";
    bst_inorder_traversal(bst_root);
    cout << endl;

    cout << "Tree Height: " << bst_height(bst_root) << endl;
    cout << "Node Count: " << bst_count_nodes(bst_root) << endl;

    cout << "3rd Smallest Element: " << bst_kth_smallest(bst_root, 3) << endl;
}

void test_avl() {
    cout << "\n=== AVL Tree ===\n";
    AVLNode* avl_root = nullptr;
    avl_root = avl_insert(avl_root, 50);
    avl_root = avl_insert(avl_root, 30);
    avl_root = avl_insert(avl_root, 70);
    avl_root = avl_insert(avl_root, 20);
    avl_root = avl_insert(avl_root, 40);
    avl_root = avl_insert(avl_root, 60);
    avl_root = avl_insert(avl_root, 80);

    cout << "Inorder Traversal: ";
    avl_inorder_traversal(avl_root);
    cout << endl;

    cout << "Deleting 20, 30, and 50...\n";
    avl_root = avl_delete(avl_root, 20);
    avl_root = avl_delete(avl_root, 30);
    avl_root = avl_delete(avl_root, 50);

    cout << "Inorder Traversal After Deletion: ";
    avl_inorder_traversal(avl_root);
    cout << endl;

    cout << "Tree Height: " << avl_height(avl_root) << endl;
    cout << "Node Count: " << avl_count_nodes(avl_root) << endl;

    cout << "3rd Smallest Element: " << avl_kth_smallest(avl_root, 3) << endl;
}

void test_rbt() {
    cout << "\n=== Red-Black Tree ===\n";
    RBNode* rb_root = nullptr;
    rb_root = rb_insert(rb_root, 50);
    rb_root = rb_insert(rb_root, 30);
    rb_root = rb_insert(rb_root, 70);
    rb_root = rb_insert(rb_root, 20);
    rb_root = rb_insert(rb_root, 40);
    rb_root = rb_insert(rb_root, 60);
    rb_root = rb_insert(rb_root, 80);

    cout << "Inorder Traversal: ";
    rb_inorder_traversal(rb_root);
    cout << endl;

    cout << "Deleting 20, 30, and 50...\n";
    rb_root = rb_delete(rb_root, 20);
    rb_root = rb_delete(rb_root, 30);
    rb_root = rb_delete(rb_root, 50);

    cout << "Inorder Traversal After Deletion: ";
    rb_inorder_traversal(rb_root);
    cout << endl;

    cout << "Tree Height: " << rb_height(rb_root) << endl;
    cout << "Node Count: " << rb_count_nodes(rb_root) << endl;

    cout << "3rd Smallest Element: " << rb_kth_smallest(rb_root, 3) << endl;
}

void test_splay() {
    cout << "\n=== Splay Tree ===\n";
    SplayNode* splay_root = nullptr;
    splay_root = splay_insert(splay_root, 50);
    splay_root = splay_insert(splay_root, 30);
    splay_root = splay_insert(splay_root, 70);
    splay_root = splay_insert(splay_root, 20);
    splay_root = splay_insert(splay_root, 40);
    splay_root = splay_insert(splay_root, 60);
    splay_root = splay_insert(splay_root, 80);

    cout << "Inorder Traversal: ";
    splay_inorder_traversal(splay_root);
    cout << endl;

    cout << "Deleting 20, 30, and 50...\n";
    splay_root = splay_delete(splay_root, 20);
    splay_root = splay_delete(splay_root, 30);
    splay_root = splay_delete(splay_root, 50);

    cout << "Inorder Traversal After Deletion: ";
    splay_inorder_traversal(splay_root);
    cout << endl;

    cout << "Tree Height: " << splay_height(splay_root) << endl;
    cout << "Node Count: " << splay_count_nodes(splay_root) << endl;

    cout << "3rd Smallest Element: " << splay_kth_smallest(splay_root, 3) << endl;
}

int main() {
    test_bst();
    test_avl();
    test_rbt();
    test_splay();

    return 0;
}
