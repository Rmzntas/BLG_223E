/* @Author
Name: Ramazan Taş
*/
#include<iostream>
#include "AVLTree.h"
#include <chrono>

AVLTree::AVLTree(){
}

AVLTree::~AVLTree(){
    delete root;
}

AVLNode* AVLTree::get_root(){
    return root;
}

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

void AVLTree::right_rotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = maximum(cal_height(y->left), cal_height(y->right)) + 1;
    x->height = maximum(cal_height(y->left), cal_height(y->right)) + 1;
    y = x;
}

void AVLTree::left_rotate(AVLNode* x) {
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
void AVLTree::insert_node(AVLNode* node, int chromo, int pos, char alt_base) {
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

void AVLTree::add_node(int chromo, int pos, char alt_base) {
    // Find the correct position and insert the node
    auto start_time = std::chrono::high_resolution_clock::now(); //starting time

    insert_node(root,chromo,pos,alt_base);

    auto end_time = std::chrono::high_resolution_clock::now();  //end time
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    std::cout<<chromo<<" "<<pos<<" "<<alt_base<<" was added in " <<duration.count()<<" ms"<<std::endl; 

}

// Node with minimum value
AVLNode* AVLTree::node_minimum(AVLNode* node) {
    AVLNode* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

// Delete a node
void AVLTree::delete_node(AVLNode* root, int chromo, int pos, char alt_base, bool& is_deleted) {
    
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
             if (root->left == NULL && root->right == NULL) {
                delete root;
                root = NULL;
                is_deleted = true;
            }
            else if (root->left == NULL) {
                AVLNode* temp = root->right;
                *root = *temp;
                delete temp;
                is_deleted = true;
            }
            else if (root->right == NULL) {
                AVLNode* temp = root->left;
                *root = *temp;
                delete temp;
                is_deleted = true;
            }
            else {
                AVLNode* temp = node_minimum(root->right);
                
                root->set_chromo(temp->get_chromo());
                root->set_pos(temp->get_pos());
                root->set_alt_base(temp->get_alt_base());
                delete_node(root->right, temp->get_chromo(), temp->get_pos(), temp->get_alt_base(), is_deleted);
            }
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

void AVLTree::delete_node_main(int chromo, int pos, char alt_base){

    auto start_time = std::chrono::high_resolution_clock::now(); //starting time
    bool del_flag = false;

    delete_node(root, chromo, pos, alt_base, del_flag);

    if(del_flag){   
        auto end_time = std::chrono::high_resolution_clock::now();  //end time
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
        std::cout<<chromo<<" "<<pos<<" "<<alt_base<< " was deleted in " <<duration.count()<<" ms"<<std::endl; 
    }
    else{
       std::cout<<chromo<<" "<<pos<<" "<<alt_base<<" could not be deleted because it could not be found"<<std::endl; 
    }
}

void AVLTree::list(AVLNode* root,AVLNode* last) const{  // inorder -> left - root - right
    if(root == nullptr){
        return; 
    }
    list(root->left,last);
    if(root == last){
            std::cout<<root->get_chromo()<<" "<<root->get_pos()<<" "<<root->get_alt_base()<<std::endl;
    }
    else{
        std::cout<<root->get_chromo()<<" "<<root->get_pos()<<" "<<root->get_alt_base()<<",";
    }
    list(root->right,last);
}

void AVLTree::find_node(int chromo, int pos, char alt_base) const{
        
    auto start_time = std::chrono::high_resolution_clock::now(); //starting time
    AVLNode* temp = root;

    while(true){
        if(chromo < temp->get_chromo()){
            if(temp->left == nullptr){
               std::cout<<chromo<<" "<<pos<<" "<<alt_base<<" could not be found"<<std::endl; 
               break;       
            }
            temp = temp->left;
        }
        else if(chromo > temp->get_chromo()){
            if(temp->right == nullptr){
                std::cout<<chromo<<" "<<pos<<" "<<alt_base<<" could not be found"<<std::endl; 
                break; 
            }
            temp = temp->right;
        }
        else{   //chromo == temp.chromo
            if(pos < temp->get_pos()){
                if(temp->left == nullptr){
                    std::cout<<chromo<<" "<<pos<<" "<<alt_base<<" could not be found"<<std::endl; 
                    break;       
                }
                temp = temp->left;
            }
            else if( pos > temp->get_pos()){
                if(temp->right == nullptr){
                    std::cout<<chromo<<" "<<pos<<" "<<alt_base<<" could not be found"<<std::endl; 
                    break; 
                }
                temp = temp->right;
            }
            else{   //pos == temp.pos
                if(alt_base == temp->get_alt_base()){
                    auto end_time = std::chrono::high_resolution_clock::now();  //end time
                    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
                    std::cout<<chromo<<" "<<pos<<" "<<alt_base<<" was found in "<<duration.count()<<" ms"<<std::endl;
                    break;
                }
                else{   //chromo == chromo , pos == pos, altbase != alt_base
                    std::cout<<chromo<<" "<<pos<<" "<<alt_base<<" could not be found"<<std::endl;
                    break;     
                }
            }
        }
    }
}

void AVLTree::convert_to_vector(AVLNode* root, std::vector<struct line>& vec){
    if(root == nullptr){
        return;
    }
    convert_to_vector(root->left,vec);
    line data;
    data.chromo = root->get_chromo();
    data.pos = root->get_pos();
    data.alt_base = root->get_alt_base();
    vec.push_back(data);
    convert_to_vector(root->right,vec);
}

void AVLTree::true_counter(AVLTree* gt) {

    auto start_time = std::chrono::high_resolution_clock::now(); //starting time
    int counter{};

    std:: vector <line> first,second;
    
    convert_to_vector(this->root, first);
    convert_to_vector(gt->get_root(), second);

    for (const auto& data1 : first) {
        for (const auto& data2 : second) {
            if (data1.chromo == data2.chromo && data1.pos == data2.pos && data1.alt_base == data2.alt_base) {
                counter++;
                break;
            }
        }
    }
    auto end_time = std::chrono::high_resolution_clock::now();  //end time
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    std::cout<<"True positive variant count is "<<counter<<". It took "<<duration.count()<<" ms to calculate"<<std::endl;
}