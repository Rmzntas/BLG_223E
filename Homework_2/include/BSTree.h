/* @Author
Name: Ramazan Taş
*/

#include<iostream>
#include <vector>
#include"BSTNode.h"

struct line{
    int chromo,pos;
    char alt_base;
};


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
        void convert_to_vector(BSTNode*, std::vector<struct line>&);
        void true_counter(BSTree*) ;
};