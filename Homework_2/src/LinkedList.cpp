/* @Author
Name: Ramazan Taş
*/

#include"LinkedList.h"
#include<vector>
#include <chrono>

LinkedList::LinkedList(){
    
}

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
    auto start_time = std::chrono::high_resolution_clock::now(); //starting time

    ListNode* new_node = new ListNode(chromo,pos,alt_base);
    ListNode* temp = head;

    while(temp->get_next() != nullptr){
        temp = temp->get_next();
    }
    temp->set_next(new_node);

    auto end_time = std::chrono::high_resolution_clock::now();  //end time
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    std::cout<<chromo<<" "<<pos<<" "<<alt_base<<" was added in " <<duration.count()<<" ms"<<std::endl;  // chrono

}

void LinkedList::delete_node(int chromo, int pos, char alt_base){

    auto start_time = std::chrono::high_resolution_clock::now(); //starting time


    ListNode* temp = this->head;
    bool del_flag = true;

    //if head, delete
    if (temp->get_chromo() == chromo && temp->get_pos() == pos && temp->get_alt_base() == alt_base){
        head = head->get_next();
        temp->set_next(nullptr);
        delete temp;
        del_flag = false;
        auto end_time = std::chrono::high_resolution_clock::now();  //end time
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
        std::cout<<chromo<<" "<<pos<<" "<<alt_base<< " was deleted in " <<duration.count()<<" ms"<<std::endl;  
    }
    else{
        //if next element of temp is the node
        while(temp->get_next() != nullptr){  //until last node
            if(temp->get_next()->get_chromo() == chromo && temp->get_next()->get_pos() == pos && temp->get_next()->get_alt_base() == alt_base){
                ListNode* temp2 = temp->get_next();
                temp->set_next(temp2->get_next());
                temp2->set_next(nullptr);
                delete temp2;
                del_flag = false;
                auto end_time = std::chrono::high_resolution_clock::now();  //end time
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
                std::cout<<chromo<<" "<<pos<<" "<<alt_base<< " was deleted in " <<duration.count()<<" ms"<<std::endl;  
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

    auto start_time = std::chrono::high_resolution_clock::now(); //starting time

    ListNode* temp = head;
    bool find_flag = true;

    while(temp != nullptr){
        if (temp->get_chromo() == chromo && temp->get_pos() == pos && temp->get_alt_base() == alt_base){
            auto end_time = std::chrono::high_resolution_clock::now();  //end time
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
            std::cout<<chromo<<" "<<pos<<" "<<alt_base<<" was found in "<<duration.count()<<" ms"<<std::endl;
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
    auto start_time = std::chrono::high_resolution_clock::now(); //starting time


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
        second.push_back(data);
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
    auto end_time = std::chrono::high_resolution_clock::now();  //end time
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
            
    std::cout<<"True positive variant count is "<<counter<<". It took "<<duration.count()<<" ms to calculate"<<std::endl;
    
}