/* @Author
Name: Ramazan Taş
*/
#include<vector>
#include "AVLNode.h"

struct line{
    int chromo,pos;
    char alt_base;
};

class AVLTree{
    private:
        AVLNode* root {nullptr};

    public:
        AVLTree();
        ~AVLTree();
        void delete_tree(AVLNode*&);
        AVLNode* get_root();
        AVLNode*& get_root2();
        
        AVLNode* node_minimum(AVLNode*);
        void right_rotate(AVLNode*& );
        void left_rotate(AVLNode*& );
        int get_balance(AVLNode*);
        int cal_height(AVLNode*);
        int maximum(int,int);
        void insert_node(AVLNode*&, int, int, char);


        void add_node(int, int, char);                                //3
        void delete_node(AVLNode*&, int, int, char, bool&);        
        void delete_node_main(int, int, char);                        //4
        void list(AVLNode*,AVLNode*) const;                           //5
        void find_node(int, int, char) const;                         //6
        void convert_to_vector(AVLNode*, std::vector<struct line>&);
        void true_counter(AVLTree*);                                  //7

};