/* @Author
Name: Ramazan Taş
*/

#include "ListNode.h"

class LinkedList{
    private:
        ListNode* head {nullptr};
    
    public:
        LinkedList();
        ~LinkedList();
        ListNode* get_head() const;
        void set_head(ListNode*);
        void add_node(int, int, char);           //3
        void delete_node(int, int, char);        //4
        void list() const;                       //5
        void finding(int, int, char) const;      //6
        void true_counter(LinkedList* ) const;   //7
};