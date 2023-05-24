/* @Author
Name: Ramazan Taş
*/

class ListNode{

    private:
        int chromo {};
        int pos {};
        char alt_base {};
        ListNode* next =nullptr;
    
    public:
        
        ListNode(int,int,char);
        ListNode* get_next();
        void set_next (ListNode*);
        int get_chromo();
        int get_pos();
        char get_alt_base();
};
