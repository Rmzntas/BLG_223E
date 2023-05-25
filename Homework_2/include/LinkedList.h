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
        void add_node(int, int, char); //adding new node
        void delete_node(int, int, char);  //finding node and deleting
        void list() const;
        void finding(int, int, char) const;
        void true_counter(LinkedList* ) const;
};