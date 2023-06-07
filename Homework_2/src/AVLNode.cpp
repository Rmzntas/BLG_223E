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

void AVLNode::set_chromo(int a){
    chromo = a;
}
void AVLNode::set_pos(int a){
    pos = a;
}
void AVLNode::set_alt_base(char a){
    alt_base = a;
}