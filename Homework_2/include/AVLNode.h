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
        
        AVLNode* left {nullptr};
        AVLNode* right {nullptr};
        int height;
};