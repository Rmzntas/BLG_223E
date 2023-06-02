/* @Author
Name: Ramazan Taş
*/

class AVLNode{
    private:
        int chromo {};
        int pos {};
        char alt_base {};
        
    
    public:
        AVLNode(int, int, char);
        ~AVLNode();
        int get_chromo();
        int get_pos();
        char get_alt_base();
        void set_chromo(int);
        void set_pos(int);
        void set_alt_base(char);
        
        AVLNode* left {nullptr};
        AVLNode* right {nullptr};
        int height;
};