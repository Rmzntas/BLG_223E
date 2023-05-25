/* @Author
Name: Ramazan Taş
*/

// corono ile zaman eklemesi yapılmadı

#include"LinkedList.h"
#include<vector>

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

void LinkedList::list() const{
    ListNode* temp = head;

    while(temp != nullptr){
        if(temp->get_next() == nullptr){ //last node
            std::cout<<temp->get_chromo()<<" "<<temp->get_pos()<<" "<<temp->get_alt_base()<<std::endl;
        }
        else{
            std::cout<<temp->get_chromo()<<" "<<temp->get_pos()<<" "<<temp->get_alt_base()<<",";
        }
        temp = temp->get_next();
    }
}

void LinkedList::finding(int chromo, int pos, char alt_base) const{
    ListNode* temp = head;
    bool find_flag = true;

    while(temp != nullptr){
        if (temp->get_chromo() == chromo && temp->get_pos() == pos && temp->get_alt_base() == alt_base){
            std::cout<<chromo<<" "<<pos<<" "<<alt_base<<" was found"<<std::endl;
            find_flag = false;
            break;
        }
        else{
            temp = temp->get_next();
        }
    }

    if (find_flag){
        std::cout<<chromo<<" "<<pos<<" "<<alt_base<<" could not be found"<<std::endl;        
    }
}

void LinkedList::true_counter(LinkedList* gt) const{
    struct line
    {
        int chromo,pos;
        char alt_base;
    };
    int counter{};

    std::vector <line> first, second;

    ListNode* temp_1 = head;
    ListNode* temp_2 = gt->get_head();

    while(temp_1 != nullptr){
        line data;
        data.chromo = temp_1->get_chromo();
        data.pos = temp_1->get_pos();
        data.alt_base = temp_1->get_alt_base();
        first.push_back(data);
        temp_1 = temp_1->get_next();
    }

    while(temp_2 != nullptr){
        line data;
        data.chromo = temp_2->get_chromo();
        data.pos = temp_2->get_pos();
        data.alt_base = temp_2->get_alt_base();
        first.push_back(data);
        temp_2 = temp_2->get_next();
    }

    for (const auto& data1 : first) {
        for (const auto& data2 : second) {
            if (data1.chromo == data2.chromo && data1.pos == data2.pos && data1.alt_base == data2.alt_base) {
                counter++;
                break;
            }
        }
    }

    std::cout<<"True positive variant count is "<<counter<<"."<<std::endl;
    
}