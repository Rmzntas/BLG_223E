/* @Author
Name: Ramazan Taş
*/

#include<iostream>
#include"BSTNode.h"

class BSTree{
    private:
        BSTNode* root {nullptr};
    
    public:
        BSTree();
        ~BSTree();
        BSTNode* get_root();
        void set_root(BSTNode*);
        void add_node(int, int, char);
        void delete_node(int, int, char);
        void list(BSTNode*,BSTNode*) const;  // root and last element as parametre
        void finding(int, int, char) const;
        void true_counter(BSTree*) const;
    
};