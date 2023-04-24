/* @Author
Name: Ramazan Taş
Date: 23.04.2023 */

#include <iostream>
#include <string>
#include <cstring>
#include "MultiList.h"

using namespace std;

MultiList::MultiList(){

}

void MultiList::add_uni_node(Department *depPTR, string faculty, string uni, string discount, string city, string language, string score_last, string range_last, string score_first, string range_first, string range_average, string score_average){
    University* new_uni = new University(faculty,uni,discount,city,language,score_last,range_last,score_first,range_first,range_average,score_average);
    University* temp = depPTR ->get_upp();

    if (depPTR ->get_numOfUni() ==1){
        if((uni < temp ->get_uni()) || uni == temp ->get_uni()){
            new_uni ->set_up(temp);
            depPTR ->set_upp(new_uni); 
        }
        else{
            temp ->set_up(new_uni);
        }
    }
    else{  // num_of_university > 1
        while(temp ->get_up() != NULL){      //while temp isn't last node
            if(uni == temp->get_uni()){
                new_uni ->set_up(temp);
                depPTR ->set_upp(new_uni); 
                break;
            }
            else if (uni < temp ->get_uni()){ // if it is smaller it is first up because this can be only called in the beginnig in my algorithm
                new_uni ->set_up(temp);
                depPTR ->set_upp(new_uni);
                break;
            }
            else{  //  uni > temp_uni  
                if(uni < temp ->get_up() ->get_uni() || uni == temp ->get_up() ->get_uni()){   
                    new_uni ->set_up(temp ->get_up());
                    temp ->set_up(new_uni);
                    break;
                }
                else{  // bigger than next
                    temp = temp ->get_up();
                }
            }
        }
        if (temp ->get_up() == NULL){  // when temp is last node
            temp ->set_up(new_uni);
        }
    }
    depPTR ->increase();
}

void MultiList::add_dep_uni_node(Department *preve, string department, string faculty, string uni, string discount, string city, string language, string score_last, string range_last, string score_first, string range_first, string range_average, string score_average){
    Department* new_dep = new Department(department);
    University* new_uni = new University(faculty,uni,discount,city,language,score_last,range_last,score_first,range_first,range_average,score_average);

    new_dep ->set_next(preve ->get_next());
    preve ->set_next(new_dep);
    new_dep ->set_prev(preve);
    new_dep ->get_next() ->set_prev(new_dep);
    new_dep ->set_upp(new_uni);
    new_dep ->increase();
    num_of_departmant++;

}

void MultiList::add_node(string department, string faculty, string uni, string discount, string city, string language, string score_last, string range_last, string score_first, string range_first, string range_average, string score_average){
    if (head == NULL && tail == NULL){  //list is empty
        
        Department* new_dep = new Department(department);
        University* new_uni = new University(faculty,uni,discount,city,language,score_last,range_last,score_first,range_first,range_average,score_average);
        new_dep->set_upp(new_uni);
        new_dep ->increase();
        head = new_dep;
        tail = new_dep;
        num_of_departmant++;
    }
    else{  // List is not empty
    //    Department* new_dep = new Department(department);
    //    University* new_uni = new University(faculty,uni,discount,city,language,score_last,range_last,score_first,range_first,range_average,score_average);
        Department* temp = head;

        if ( department == temp ->get_Department()){
            add_uni_node(head,faculty,uni,discount,city,language,score_last,range_last,score_first,range_first,range_average,score_average);
        }
        else if ( department < temp ->get_Department()){
            Department* new_dep = new Department(department);
            University* new_uni = new University(faculty,uni,discount,city,language,score_last,range_last,score_first,range_first,range_average,score_average);
            new_dep ->set_next(temp);
            new_dep ->set_upp(new_uni);
            new_dep ->increase();
            temp ->set_prev(new_dep);
            head=new_dep;
            num_of_departmant++;
        }
        else{   //bigger than head or temp
            if (head == tail){  // only 1 node
                Department* new_dep = new Department(department);
                University* new_uni = new University(faculty,uni,discount,city,language,score_last,range_last,score_first,range_first,range_average,score_average);
                new_dep ->set_prev(temp);
                temp ->set_next(new_dep);
                new_dep ->set_upp(new_uni);
                new_dep ->increase();
                tail = new_dep;
                num_of_departmant++;
            }
            else{  //more than 1 node and bigger than head
                while(temp != tail){
                    if (department == temp ->get_next() ->get_Department()){
                        add_uni_node(temp->get_next(),faculty,uni,discount,city,language,score_last,range_last,score_first,range_first,range_average,score_average);
                        break;
                    }
                    else if( department < temp ->get_next() ->get_Department()){
                        add_dep_uni_node(temp,department,faculty,uni,discount,city,language,score_last,range_last,score_first,range_first,range_average,score_average);
                        break;
                    }
                    else{  // department > temp.next
                        temp = temp->get_next();
                    }
                }
                if (temp == tail){
                    Department* new_dep = new Department(department);
                    University* new_uni = new University(faculty,uni,discount,city,language,score_last,range_last,score_first,range_first,range_average,score_average);
                    new_dep ->set_upp(new_uni);
                    new_dep ->increase();
                    temp ->set_next(new_dep);
                    new_dep->set_prev(temp);
                    tail = new_dep;
                    num_of_departmant++;
                }
            }
        }
    }
}

void MultiList::listDepartments(){

    auto start_list_dep = std::chrono::high_resolution_clock::now();
    Department* temp = head;

    while (temp != NULL)
    {
        cout<< "Department: " << temp ->get_Department() << endl; 
        cout<< "Number of University Department: "<< temp ->get_numOfUni() << endl;
        cout<< "-----------------"<<endl;

        temp = temp ->get_next();
    }
    auto end_list_dep = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<std::chrono::milliseconds>(end_list_dep - start_list_dep);
    //cout << "Department listing is : " << duration.count() << " milliseconds" << std::endl;
}

void MultiList::select_department(){
    int number{};
    Department* temp = head;

    auto start_list_uni = chrono::high_resolution_clock::now();

    do{   // loop until giving number between 0 and department number
        cout<< "To review a department, enter a number between 0 and the department number: ";
        cin >> number;
    }while ( number < 0 || number >= num_of_departmant);

    
    for(int i =0; i<number; i++){  //going temp = choosen department
        temp = temp ->get_next();
    }

    cout<<"Department: "<<temp ->get_Department()<<endl;
    University* temp_uni = temp->get_upp();

    for(int i = 0; i< temp->get_numOfUni();i++){
        cout<<i+1<<": "<<temp_uni->get_uni()<<endl;
        temp_uni->printDetails();
        if(temp_uni ->get_up() != NULL)
            temp_uni = temp_uni ->get_up();
    }

    auto end_list_uni = chrono::high_resolution_clock::now();
    auto time_list_uni = chrono::duration_cast<std::chrono::microseconds>(end_list_uni- start_list_uni);
    //cout << "Listing universities: " << time_list_uni.count() << " microseconds" << std::endl;
    

}

void MultiList::select_uni(){
    int number1{},number2{};
    Department* temp = head;

    auto start_selectUni = std::chrono::high_resolution_clock::now();

    do{   // loop until giving number between 0 and department number
        cout<< "To review a department, enter a number between 0 and the department number: ";
        cin >> number1;
    }while ( number1 < 0 || number1 >= num_of_departmant);
    
    


    for(int i =0; i<number1; i++){  //doing temp = choosen department
        temp = temp ->get_next();
    }
    cout<<"Department: "<<temp ->get_Department()<<endl<<endl;
    University* temp_uni = temp->get_upp();

    do{   // loop until giving number between 0 and department number
        cout<< "To review a university of selected department, enter a number between 0 and the university number: ";
        cin >> number2;
    }while ( number2 < 0 || number2 >= temp->get_numOfUni());

    
    
    for(int i =0; i < number2; i++){  //doing temp = choosen department
        temp_uni = temp_uni ->get_up();
    }

    cout<<temp_uni->get_uni()<<endl;
    temp_uni->printDetails();

    auto end_selectUni = chrono::high_resolution_clock::now();
    auto time_selectUni = chrono::duration_cast<std::chrono::microseconds>(end_selectUni- start_selectUni);
    //cout << "selecting uni: " << time_selectUni.count() << " microseconds" << std::endl;
}


MultiList::~MultiList() {
    Department* curr = head;
    while (curr != NULL) {
        Department* temp = curr;
        curr = curr->get_next();
        delete temp;
    }
}

