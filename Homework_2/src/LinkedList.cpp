/* @Author
Name: Ramazan Taş
*/

// delete_node'da ve add_node'da chrono ile ms ekle

#include"LinkedList.h"

LinkedList::~LinkedList(){ // delete head and it will delete all linked list beacuse of destructor of Listnode will delete next
    delete head;
}

ListNode* LinkedList::get_head() const{
    return head;
}

void LinkedList::set_head(ListNode* a){
    head = a;
}

void LinkedList::add_node(int chromo, int pos, char alt_base){

}

void LinkedList::delete_node(int chromo, int pos, char alt_base){
    ListNode* temp = this->head;
    bool del_flag = true;

    //if head, delete
    if (temp->get_chromo() == chromo && temp->get_pos() == pos && temp->get_alt_base() == alt_base){
        head = head->get_next();
        delete temp;
        del_flag = false;
        std::cout<<chromo<<" "<<pos<<" "<<alt_base<< " was deleted"<<std::endl;  // chrono

    }
    else{
        //if next element of temp is the node
        while(temp->get_next() != nullptr){  //until last node
            if(temp->get_next()->get_chromo() == chromo && temp->get_next()->get_pos() == pos && temp->get_next()->get_alt_base() == alt_base){
                temp->set_next(temp->get_next()->get_next());
                delete temp->get_next();
                del_flag = false;
                std::cout<<chromo<<" "<<pos<<" "<<alt_base<< " was deleted"<<std::endl;  // chrono
                break;       
            }
            else{
                temp = temp->get_next();
            }
        }

        if (del_flag){
            std::cout<<chromo<<" "<<pos<<" "<<alt_base<<" could not be deleted because it could not be found"<<std::endl;
        }
    }
}