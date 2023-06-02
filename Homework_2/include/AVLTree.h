/* @Author
Name: Ramazan Taş
*/

#include "AVLNode.h"

class AVLTree{
    private:
        AVLNode* root {nullptr};

    public:
        AVLTree();
        ~AVLTree();
        AVLNode* get_root();
        AVLNode* new_node(int, int, char);
        void insert_node(AVLNode*&, int, int, char);
        AVLNode* node_minimum(AVLNode*);
        void right_rotate(AVLNode*& );
        void left_rotate(AVLNode*& );
        int get_balance(AVLNode*);
        int cal_height(AVLNode*);
        int maximum(int,int);


        AVLNode* add_node(AVLNode*, int, int, char);        //3
        void delete_node(AVLNode*&, int, int, char, bool&);     //4
        void list(AVLNode*,AVLNode*);                       //5
        void find_node(int, int, char);                     //6
        void true_counter(AVLTree*);                        //7

};