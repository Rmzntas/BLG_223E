/* @Author
Name: Ramazan Taş
*/

#include"AVLNode.h"

AVLNode::AVLNode(int chromo, int pos, char alt_base){
    this->chromo = chromo;
    this->pos = pos;
    this->alt_base = alt_base;
}

AVLNode::~AVLNode(){
    delete left;
    delete right;
}

int AVLNode::get_chromo(){
    return chromo;
}
int AVLNode::get_pos(){
    return pos;
}
char AVLNode::get_alt_base(){
    return alt_base;
}