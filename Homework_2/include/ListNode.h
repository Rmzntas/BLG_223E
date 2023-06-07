/* @Author
Name: Ramazan Taş
*/

#include<iostream>

class ListNode{

    private:
        int chromo {};
        int pos {};
        char alt_base {};
        ListNode* next =nullptr;
    
    public:
        
        ListNode(int,int,char);
        ~ListNode();
        ListNode* get_next() const;
        void set_next (ListNode*);
        int get_chromo() const;
        int get_pos() const;
        char get_alt_base() const;
};