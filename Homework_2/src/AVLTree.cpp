/* @Author
Name: Ramazan Taş
*/

#include "AVLTree.h"

int AVLTree::cal_height(AVLNode* node){
    if(node == nullptr){
        return 0;
    }
    return node->height;
}

int AVLTree::maximum(int a, int b){
    if (a > b) return a;
    else return b;
}

void AVLTree::right_rotate(AVLNode*& y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = maximum(cal_height(y->left), cal_height(y->right)) + 1;
    x->height = maximum(cal_height(y->left), cal_height(y->right)) + 1;
    y = x;
}

void AVLTree::left_rotate(AVLNode*& x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = maximum(cal_height(y->left), cal_height(y->right)) + 1;
    y->height = maximum(cal_height(y->left), cal_height(y->right)) + 1;
    x = y;
}

int AVLTree::get_balance(AVLNode* node) {
    if (node == nullptr)
        return 0;
    return cal_height(node->left) - cal_height(node->right);
}

AVLNode* AVLTree::new_node(int chromo, int pos, char alt_base ) {
    AVLNode* node = new AVLNode(chromo,pos,alt_base);
    node->height = 1;
    return (node);
}

// Insert a node
void AVLTree::insert_node(AVLNode*& node, int chromo, int pos, char alt_base) {
    // Find the correct position and insert the node
    if (node == nullptr) {
        node = new_node(chromo,pos,alt_base);
        return;
    }
    if (chromo < node->get_chromo()){
        insert_node(node->left, chromo,pos,alt_base);
    }   
    else if (chromo > node->get_chromo()){
        insert_node(node->right, chromo,pos,alt_base);
    }
    else{
        if (pos < node->get_pos()){
            insert_node(node->left, chromo,pos,alt_base);
        }
        else if( pos > node->get_pos()){
            insert_node(node->right, chromo,pos,alt_base);
        }
        else {return;}
    }

    // Update the balance factor of each node and
    // balance the tree
    node->height = maximum(cal_height(node->left), cal_height(node->right)) + 1;
    int balance_factor = get_balance(node);
    if (balance_factor > 1) {
        if (chromo < node->left->get_chromo()) {
            right_rotate(node);
        }
        else if (chromo > node->left->get_chromo()) {
            left_rotate(node->left);
            right_rotate(node);
        }
        else{
            if( pos > node->left->get_pos()){
                left_rotate(node->left);
                right_rotate(node);
            }
        }
    }
    if (balance_factor < -1) {
        if (chromo > node->right->get_chromo()) {
            left_rotate(node);
        }
        else if (chromo < node->right->get_chromo()) {
            right_rotate(node->right);
            left_rotate(node);
        }
        else{
            if(pos < node->right->get_pos()){
                right_rotate(node->right);
                left_rotate(node);
            }
        }
    }
}

// Node with minimum value
AVLNode* AVLTree::node_minimum(AVLNode* node) {
    AVLNode* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

// Delete a node
void AVLTree::delete_node(AVLNode*& root, int chromo, int pos, char alt_base, bool& is_deleted) {
    // Find the node and delete it
    if (root == nullptr)
        return;
    if (chromo < root->get_chromo())
        delete_node(root->left, chromo, pos, alt_base, is_deleted);
    else if (chromo > root->get_chromo())
        delete_node(root->right, chromo, pos, alt_base, is_deleted);
    else {
        if (pos < root->get_pos())
            delete_node(root->left, chromo, pos, alt_base, is_deleted);
        else if (pos > root->get_pos())
            delete_node(root->right, chromo, pos, alt_base, is_deleted);
        else if (alt_base == root->get_alt_base()) {
            if ((root->left == nullptr) || (root->right == nullptr)) {
                AVLNode* temp = root->left ? root->left : root->right;
                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                }
                else
                    *root = *temp;
                delete temp;
            }
            else {
                AVLNode* temp = node_minimum(root->right);
                root->set_chromo(temp->get_chromo());
                root->set_pos(temp->get_pos());
                root->set_alt_base(temp->get_alt_base());
                delete_node(root->right, temp->get_chromo(), temp->get_pos(), temp->get_alt_base(), is_deleted);
            }
            is_deleted = true; // Silme işlemi gerçekleştiğinde bayrak değeri true olarak ayarlanır
        }
    }

    if (root == nullptr)
        return;

    // Update the balance factor of each node and
    // balance the tree
    root->height = maximum(cal_height(root->left), cal_height(root->right)) + 1;
    int balanceFactor = get_balance(root);
    if (balanceFactor > 1) {
        if (get_balance(root->left) >= 0) {
            right_rotate(root);
        }
        else {
            left_rotate(root->left);
            right_rotate(root);
        }
    }
    if (balanceFactor < -1) {
        if (get_balance(root->right) <= 0) {
            left_rotate(root);
        }
        else {
            right_rotate(root->right);
            left_rotate(root);
        }
    }
}
