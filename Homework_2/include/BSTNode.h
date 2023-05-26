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
        int get_chromo() const;
        int get_pos() const;
        char get_alt_base() const;
        BSTNode* get_parent()const;
        BSTNode* get_leftchild() const;
        BSTNode* get_rightchild() const;
        void set_parent(BSTNode*);
        void set_leftchild(BSTNode*);
        void set_rightchild(BSTNode*);

};