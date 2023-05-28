/* @Author
Name: Ramazan Taş
*/

#include"BSTree.h"

BSTree::~BSTree(){
    delete root;
}

BSTNode* BSTree::get_root(){
    return root;
}

void BSTree::set_root(BSTNode* a){
    root = a;
}

void BSTree::add_node(int chromo, int pos, char alt_base){

    BSTNode* new_node = new BSTNode(chromo,pos,alt_base);

    if(root ==nullptr){     //if tree is empty
        root = new_node;
    }
    else{
        BSTNode* temp = root;

        while(true){
            if(new_node->get_chromo() < temp->get_chromo()){
                if(temp->get_leftchild() == nullptr){
                    temp->set_leftchild(new_node);
                    new_node->set_parent(temp);
                    break;
                }
                else{
                    temp->get_leftchild();
                }
            }
            else if(new_node->get_chromo() > temp->get_chromo()){
                if(temp->get_rightchild() == nullptr){
                    temp->set_rightchild(new_node);
                    new_node->set_parent(temp);
                    break;
                }
                else{
                    temp = temp->get_rightchild();
                }
            }
            else{  //chromos are equal
                if(new_node->get_pos() < temp->get_pos()){
                    if(temp->get_leftchild() == nullptr){
                        temp->set_leftchild(new_node);
                        new_node->set_parent(temp);
                        break;
                    }
                }
                else if(new_node->get_pos() > temp->get_pos()){
                    if(temp->get_rightchild() == nullptr){
                        temp->set_rightchild(new_node);
                        new_node->set_parent(temp);
                        break;
                    }
                    else{
                        temp = temp->get_rightchild();
                    }
                }
                else{}//chromo and pos are equal -> X
            }
        }
    }

}

void BSTree::delete_node(int chromo, int pos, char alt_base){

}

void BSTree::list(BSTNode* root,BSTNode* last) const{  // inorder -> left - root - right
    if(root == nullptr){
        return; 
    }
    list(root->get_leftchild(),last);
    if(root == last){
            std::cout<<root->get_chromo()<<" "<<root->get_pos()<<" "<<root->get_alt_base()<<std::endl;
    }
    else{
        std::cout<<root->get_chromo()<<" "<<root->get_pos()<<" "<<root->get_alt_base()<<",";
    }
    list(root->get_rightchild(),last);
}

void BSTree::finding(int chromo, int pos, char alt_base) const{
    BSTNode* temp = root;

    while(true){
        if(chromo < temp->get_chromo()){
            if(temp->get_leftchild() == nullptr){
               std::cout<<chromo<<" "<<pos<<" "<<alt_base<<" could not be found"<<std::endl; 
               break;       
            }
            temp = temp->get_leftchild();
        }
        else if(chromo > temp->get_chromo()){
            if(temp->get_rightchild() == nullptr){
                std::cout<<chromo<<" "<<pos<<" "<<alt_base<<" could not be found"<<std::endl; 
                break; 
            }
            temp = temp->get_rightchild();
        }
        else{   //chromo == temp.chromo
            if(pos < temp->get_pos()){
                if(temp->get_leftchild() == nullptr){
                    std::cout<<chromo<<" "<<pos<<" "<<alt_base<<" could not be found"<<std::endl; 
                    break;       
                }
                temp = temp->get_leftchild();
            }
            else if( pos > temp->get_pos()){
                if(temp->get_rightchild() == nullptr){
                    std::cout<<chromo<<" "<<pos<<" "<<alt_base<<" could not be found"<<std::endl; 
                    break; 
                }
                temp = temp->get_rightchild();
            }
            else{   //pos == temp.pos
                if(alt_base == temp->get_alt_base()){
                    std::cout<<chromo<<" "<<pos<<" "<<alt_base<<" was found"<<std::endl;
                    break;
                }
                else{   //chromo == chromo , pos == pos, altbase != alt_base
                    std::cout<<chromo<<" "<<pos<<" "<<alt_base<<" could not be found"<<std::endl;        
                }
            }
        }
    }
}

void BSTree::true_counter(BSTree* second) const{

}
