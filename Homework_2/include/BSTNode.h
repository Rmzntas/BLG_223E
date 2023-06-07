/* @Author
Name: Ramazan Taş
*/

class BSTNode{
    private:

        int chromo{};
        int pos{};
        char alt_base{};
        BSTNode* left_child {nullptr};
        BSTNode* right_child {nullptr};
        BSTNode* parent {nullptr};

    public:

        BSTNode(int,int,char);
        ~BSTNode();
        int get_chromo() ;
        int get_pos() ;
        char get_alt_base();
        BSTNode* get_parent() ;
        BSTNode* get_leftchild() ;
        BSTNode* get_rightchild() ;
        void set_parent(BSTNode*);
        void set_leftchild(BSTNode*);
        void set_rightchild(BSTNode*);

};