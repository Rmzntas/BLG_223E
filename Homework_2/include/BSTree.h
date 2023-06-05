/* @Author
Name: Ramazan Taş
*/

#include<iostream>
#include <vector>
#include"BSTNode.h"

struct line_bst{
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
        void insert_node(int, int, char);
        void add_node(int, int, char);          //3
        BSTNode* finding_node_to_deleting(int,int,char,bool&);
        void delete_node(int, int, char);       //4
        void list(BSTNode*,BSTNode*) const;     //5 ->root and last element as parametre
        void finding(int, int, char) const;     //6
        void convert_to_vector(BSTNode*, std::vector<struct line_bst>&);
        void true_counter(BSTree*) ;            //7
};