/* @Author
Name: Ramazan Taş
*/


#include "ListNode.h"

ListNode::ListNode(int chromo, int pos, char alt_base){
    this->chromo = chromo;
    this->alt_base = alt_base;
    this->pos = pos;
}

ListNode* ListNode::get_next(){
    return next;
}

void ListNode::set_next(ListNode* a){
    next = a;
}

int ListNode::get_chromo(){
    return chromo;
}

int ListNode::get_pos(){
    return pos;
}

char ListNode::get_alt_base(){
    return alt_base;
}
