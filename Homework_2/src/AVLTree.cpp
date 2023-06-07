/* @Author
Name: Ramazan Taş
*/
#include<iostream>
#include "AVLTree.h"
#include <chrono>
#include<stack>

AVLTree::AVLTree(){
}

AVLTree::~AVLTree(){
    delete_tree(root);
}

void AVLTree::delete_tree(AVLNode* &node){
    if(node == nullptr){
        return;
    }

    delete_tree(node->left);
    delete_tree(node->right);

    delete node;
}

AVLNode* AVLTree::get_root(){
    return root;
}

AVLNode*& AVLTree::get_root2(){
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

void AVLTree::right_rotate(AVLNode* &main) {
    if (main == nullptr || main->left == nullptr) {
        return;
    }

    AVLNode* x = main->left;
    AVLNode* T2 = x->right;
    x->right = main;
    main->left = T2;
    main->height = maximum(cal_height(main->left), cal_height(main->right)) + 1;
    x->height = maximum(cal_height(x->left), cal_height(x->right)) + 1;
    main = x;
}

void AVLTree::left_rotate(AVLNode* &main) {
    if (main == nullptr || main->right == nullptr) {
        return;
    }

    AVLNode* y = main->right;
    AVLNode* T2 = y->left;
    y->left = main;
    main->right = T2;
    main->height = maximum(cal_height(main->left), cal_height(main->right)) + 1;
    y->height = maximum(cal_height(y->left), cal_height(y->right)) + 1;
    main = y;
}

int AVLTree::get_balance(AVLNode* node) {
    if (node == nullptr)
        return 0;
    return cal_height(node->left) - cal_height(node->right);
}

// Insert node
void AVLTree::insert_node(AVLNode* &node, int chromo, int pos, char alt_base) {
    // Find the correct position and insert the node
    if (node == nullptr) {
        node = new AVLNode(chromo, pos, alt_base);
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
void AVLTree::delete_node(AVLNode* &node, int chromo, int pos, char alt_base, bool& is_deleted) {
    
    // Find the node and delete it
    
    if (node == nullptr)
        return;
    if (chromo < node->get_chromo())
        delete_node(node->left, chromo, pos, alt_base, is_deleted);
    else if (chromo > node->get_chromo())
        delete_node(node->right, chromo, pos, alt_base, is_deleted);
    else {
        if (pos < node->get_pos())
            delete_node(node->left, chromo, pos, alt_base, is_deleted);
        else if (pos > node->get_pos())
            delete_node(node->right, chromo, pos, alt_base, is_deleted);
        else if (alt_base == node->get_alt_base()) {
             if (node->left == nullptr && node->right == nullptr) {
                delete node;
                node = nullptr;
                is_deleted = true;
            }
            else if (node->left == nullptr) {
                AVLNode* temp = node;
                node = node->right;
                //temp->right = nullptr;
                delete temp;
                is_deleted = true;
            }
            else if (node->right == nullptr) {
                AVLNode* temp = node;
                node = node->left;
                //temp->left = nullptr;
                delete temp;
                is_deleted = true;
            }
            else {
                AVLNode* temp = node_minimum(node->right);
                
                node->set_chromo(temp->get_chromo());
                node->set_pos(temp->get_pos());
                node->set_alt_base(temp->get_alt_base());
                delete_node(node->right, temp->get_chromo(), temp->get_pos(), temp->get_alt_base(), is_deleted);
            }
        }
    }

    if (node == nullptr)
        return;

    // Update the balance factor of each node and
    // balance the tree
    node ->height = maximum(cal_height(node->left), cal_height(node->right)) + 1;
    int balanceFactor = get_balance(node);
    if (balanceFactor > 1) {
        if (get_balance(node->left) >= 0) {
            right_rotate(node);
        }
        else {
            left_rotate(node->left);
            right_rotate(node);
        }
    }
    if (balanceFactor < -1) {
        if (get_balance(node->right) <= 0) {
            left_rotate(node);
        }
        else {
            right_rotate(node->right);
            left_rotate(node);
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

void AVLTree::list(AVLNode* node,AVLNode* last) const{  // inorder -> left - root - right
    if(node == nullptr){
        return; 
    }
    list(node->left,last);
    if(node == last){
            std::cout<<node->get_chromo()<<" "<<node->get_pos()<<" "<<node->get_alt_base()<<std::endl;
    }
    else{
        std::cout<<node->get_chromo()<<" "<<node->get_pos()<<" "<<node->get_alt_base()<<",";
    }
    list(node->right,last);
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
    
    
    std::stack<AVLNode*> nodeStack;
    AVLNode* current = root;

    while (current != nullptr || !nodeStack.empty()) {
        while (current != nullptr) {
            nodeStack.push(current);
            current = current->left;
        }

        current = nodeStack.top();
        nodeStack.pop();

        line data;
        data.chromo = current->get_chromo();
        data.pos = current->get_pos();
        data.alt_base = current->get_alt_base();
        vec.push_back(data);

        current = current->right;
    }
    
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