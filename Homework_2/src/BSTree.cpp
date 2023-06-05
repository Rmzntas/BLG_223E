/* @Author
Name: Ramazan Taş
*/

#include"BSTree.h"
#include <chrono>

BSTree::BSTree(){

}

BSTree::~BSTree(){
    delete root;
}

BSTNode* BSTree::get_root(){
    return root;
}

void BSTree::set_root(BSTNode* a){
    root = a;
}

void BSTree::insert_node(int chromo, int pos, char alt_base){

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

void BSTree::add_node(int chromo, int pos, char alt_base){
    auto start_time = std::chrono::high_resolution_clock::now(); //starting time


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
    auto end_time = std::chrono::high_resolution_clock::now();  //end time
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    std::cout<<chromo<<" "<<pos<<" "<<alt_base<<" was added in " <<duration.count()<<" ms"<<std::endl;  

}

BSTNode* BSTree::finding_node_to_deleting(int chromo, int pos, char alt_base, bool& flag){
    BSTNode* temp = root;
    flag = false;

    while(true){
        if(chromo < temp->get_chromo()){
            if(temp->get_leftchild() == nullptr){
               flag = false;
               return nullptr; 
               break;       
            }
            temp = temp->get_leftchild();
        }
        else if(chromo > temp->get_chromo()){
            if(temp->get_rightchild() == nullptr){
                flag = false;
                return nullptr; 
                break; 
            }
            temp = temp->get_rightchild();
        }
        else{   //chromo == temp.chromo
            if(pos < temp->get_pos()){
                if(temp->get_leftchild() == nullptr){
                    flag = false;
                    return nullptr; 
                    break;       
                }
                temp = temp->get_leftchild();
            }
            else if( pos > temp->get_pos()){
                if(temp->get_rightchild() == nullptr){
                    flag = false;
                    return nullptr; 
                    break; 
                }
                temp = temp->get_rightchild();
            }
            else{   //pos == temp.pos
                if(alt_base == temp->get_alt_base()){
                    flag = true;
                    return temp;
                    break;
                }
                else{   //chromo == chromo , pos == pos, altbase != alt_base
                    flag = false;
                    return nullptr;
                    break;     
                }
            }
        }
    }
}

void BSTree::delete_node(int chromo, int pos, char alt_base){
    auto start_time = std::chrono::high_resolution_clock::now(); //starting time


    bool find_flag = false;
    BSTNode* temp = finding_node_to_deleting(chromo, pos, alt_base,find_flag);
    
    if(! find_flag ){ //could not found
       std::cout<<chromo<<" "<<pos<<" "<<alt_base<<" could not be deleted because it could not be found"<<std::endl; 
    }
    else if(temp == root){  //found and it is root
        //case 1 : there is no child
        //case 2 : there is 1 child
        //case 3 : there are 2 children
        
        //case 1
        if(temp->get_leftchild() == nullptr && temp->get_rightchild() == nullptr ){
            root = nullptr;
            delete temp;
        }
        
        //case 2
        else if( temp->get_leftchild() == nullptr || temp->get_rightchild() == nullptr ){
            if (temp->get_leftchild() == nullptr){
                root = temp->get_rightchild();
                temp->set_rightchild(nullptr);
            }
            else{   //temp has leftchild
                root = temp->get_leftchild();
                temp->set_leftchild(nullptr);
            }
            delete temp;
        }

        //case 3
        else{
            BSTNode* min = temp;

            min = min->get_rightchild();

            if( min->get_leftchild() == nullptr){
                root = min;
                min->set_leftchild(temp->get_leftchild());
                temp->get_leftchild()->set_parent(min);

                temp->set_leftchild(nullptr);
                temp->set_rightchild(nullptr);
                delete temp;
            }
            else{   // min != temp.rightchild
                while(min->get_leftchild()== nullptr){
                    min = min->get_leftchild();
                }
                root = min;
                min->set_leftchild(temp->get_leftchild());
                temp->get_leftchild()->set_parent(min);
                min->get_parent()->set_leftchild(min->get_rightchild());
                if(min->get_rightchild() != nullptr){
                    min->get_rightchild()->set_parent(min->get_parent());
                }
                min->set_rightchild(temp->get_rightchild());
                temp->get_rightchild()->set_parent(min);
                min->set_parent(nullptr);

                temp->set_leftchild(nullptr);
                temp->set_rightchild(nullptr);
                delete temp;
            }
        }
    }
    else{   //was found
        //case 1 : there is no child
        //case 2 : there is 1 child
        //case 3 : there are 2 children

        //case 1
        if( temp->get_leftchild() == nullptr && temp->get_rightchild() == nullptr ){
            BSTNode* temp_parent = temp->get_parent();
            if (temp_parent->get_rightchild()->get_chromo()== temp->get_chromo() && temp_parent->get_rightchild()->get_pos() == temp->get_pos() && temp_parent->get_rightchild()->get_alt_base() == temp->get_alt_base()){
                temp_parent->set_rightchild(nullptr);
            }
            else{
                temp_parent->set_leftchild(nullptr);
            }
            delete temp;
        }

        //case 2
        else if ( temp->get_leftchild() == nullptr || temp->get_rightchild() == nullptr ){
            BSTNode* temp_parent = temp->get_parent();

            if (temp_parent->get_rightchild() == temp){
                if(temp->get_leftchild()==nullptr){
                    temp_parent->set_rightchild(temp->get_rightchild());
                    temp->get_rightchild()->set_parent(temp_parent);
                    temp->set_rightchild(nullptr);
                }
                else{
                    temp_parent->set_rightchild(temp->get_leftchild());
                    temp->get_leftchild()->set_parent(temp_parent);
                    temp->set_leftchild(nullptr);
                }
            }
            else{
                if(temp->get_leftchild()==nullptr){
                    temp_parent->set_leftchild(temp->get_rightchild());
                    temp->get_rightchild()->set_parent(temp_parent);
                    temp->set_rightchild(nullptr);
                }
                else{
                    temp_parent->set_leftchild(temp->get_leftchild());
                    temp->get_leftchild()->set_parent(temp_parent);
                    temp->set_leftchild(nullptr);
                }
            }
            delete temp;
        }

        //case 3
        else{
            // find min value of right tree and replace with deleted node
            BSTNode* min = temp;
            BSTNode* temp_parent = temp->get_parent();
            
            min = min->get_rightchild();
            
            if(min->get_leftchild() == nullptr){ //min = temp.rightchild
                if(temp->get_parent()->get_leftchild() == temp){    //temp is leftchild
                    temp->get_parent()->set_leftchild(min);
                }
                else{   //temp is rightchild
                    temp->get_parent()->set_rightchild(min);
                }
                min->set_parent(temp->get_parent());
                min->set_leftchild(temp->get_leftchild());
                temp->get_leftchild()->set_parent(min);
                //connected
                
                temp->set_leftchild(nullptr);
                temp->set_rightchild(nullptr);
                temp->set_parent(nullptr);
                delete temp;
            }
            else{ //min.left != nullptr
                while(min->get_leftchild() == nullptr){
                    min = min->get_leftchild();
                }
                if(temp->get_parent()->get_leftchild() == temp){    //if temp leftchild
                    temp->get_parent()->set_leftchild(min);
                }
                else{   //if temp rightchild
                    temp->get_parent()->set_rightchild(min);
                }
                min->get_parent()->set_leftchild(min->get_rightchild());
                if(min->get_rightchild() != nullptr){
                    min->get_rightchild()->set_parent(min->get_parent());
                }
                min->set_parent(temp->get_parent());
                min->set_leftchild(temp->get_leftchild());
                temp->get_leftchild()->set_parent(min);
                min->set_rightchild(temp->get_rightchild());
                temp->get_rightchild()->set_parent(min);    

                temp->set_leftchild(nullptr);
                temp->set_rightchild(nullptr);
                temp->set_parent(nullptr);
                delete temp; 
            }
        }
    }
    if(find_flag){
        auto end_time = std::chrono::high_resolution_clock::now();  //end time
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
        std::cout<<chromo<<" "<<pos<<" "<<alt_base<< " was deleted in " <<duration.count()<<" ms"<<std::endl; 
    }
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
    
    auto start_time = std::chrono::high_resolution_clock::now(); //starting time

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
                    auto end_time = std::chrono::high_resolution_clock::now();  //end time
                    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
                    std::cout<<chromo<<" "<<pos<<" "<<alt_base<<" was found in "<<duration.count()<<" ms"<<std::endl;
                    break;
                }
                else{   //chromo == chromo , pos == pos, altbase != alt_base
                    std::cout<<chromo<<" "<<pos<<" "<<alt_base<<" could not be found"<<std::endl;
                    break;     
                }
            }
        }
    }
}

void BSTree::convert_to_vector(BSTNode* root, std::vector<struct line_bst>& vec){
    if(root == nullptr){
        return;
    }
    convert_to_vector(root->get_leftchild(),vec);
    line_bst data;
    data.chromo = root->get_chromo();
    data.pos = root->get_pos();
    data.alt_base = root->get_alt_base();
    vec.push_back(data);
    convert_to_vector(root->get_rightchild(),vec);
}

void BSTree::true_counter(BSTree* gt) {

    auto start_time = std::chrono::high_resolution_clock::now(); //starting time
    int counter{};

    std:: vector <line_bst> first,second;
    
    convert_to_vector(this->root, first);
    convert_to_vector(gt->get_root(), second);

    for (const auto& data1 : first) {
        for (const auto& data2 : second) {
            if (data1.chromo == data2.chromo && data1.pos == data2.pos && data1.alt_base == data2.alt_base) {
                counter++;
                break;
            }
        }
    }
    auto end_time = std::chrono::high_resolution_clock::now();  //end time
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    std::cout<<"True positive variant count is "<<counter<<". It took "<<duration.count()<<" ms to calculate"<<std::endl;


}