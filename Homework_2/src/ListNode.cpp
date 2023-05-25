/* @Author
Name: Ramazan Taş
*/


#include "ListNode.h"

ListNode::ListNode(int chromo, int pos, char alt_base){
    this->chromo = chromo;
    this->alt_base = alt_base;
    this->pos = pos;
}

ListNode::~ListNode(){
    delete next;
}

ListNode* ListNode::get_next() const{
    return next;
}

void ListNode::set_next(ListNode* a){
    next = a;
}

int ListNode::get_chromo() const{
    return chromo;
}

int ListNode::get_pos() const{
    return pos;
}

char ListNode::get_alt_base() const{
    return alt_base;
}
