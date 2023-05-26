/* @Author
Name: Ramazan Taş
*/

#include"BSTNode.h"

BSTNode::BSTNode(int chromo, int pos, char alt_base){
    this->chromo = chromo;
    this->pos = pos;
    this->alt_base = alt_base;
}

BSTNode::~BSTNode(){
    delete left_child;
    delete right_child;
}

int BSTNode::get_chromo() const{
    return chromo;
}

int BSTNode::get_pos() const{
    return pos;
}

char BSTNode::get_alt_base() const{
    return alt_base;
}

BSTNode* BSTNode::get_parent()const{
    return parent;
}

BSTNode* BSTNode::get_leftchild()const{
    return left_child;
}

BSTNode* BSTNode::get_rightchild()const{
    return right_child;
}

void BSTNode::set_parent(BSTNode* parent){
    this->parent = parent;
}

void BSTNode::set_leftchild(BSTNode* left){
    this->left_child = left;
}

void BSTNode::set_rightchild(BSTNode* right){
    this->right_child = right;
}