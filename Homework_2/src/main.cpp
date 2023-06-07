/* @Author
Name: Ramazan Taş
*/

//g++ -Wall -Werror src/main.cpp src/ListNode.cpp src/LinkedList.cpp src/BSTree.cpp src/BSTNode.cpp src/AVLTree.cpp src/AVLNode.cpp -I include -o bin/main
//bin/main

#include <iostream>
#include <vector>
#include "LinkedList.h"
#include "AVLTree.h"
#include "BSTree.h"
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>

using namespace std;

void print_ds_menu();
void print_operation_menu();
bool perform_operation(char, LinkedList*, LinkedList*);
bool perform_operation(char, BSTree*, BSTree*);  
bool perform_operation(char, AVLTree*, AVLTree*);

// I made global because I want to access in perform_operation functions
string file_gt = "./gt.txt";
string file_predict = "./predict.txt";

//for not add files 2 or more times
bool gt_flag = false;           
bool predic_flag = false;       

int main()
{
    
    bool end = false;
    char choice_ds, choice_op;
    
    print_ds_menu();
    cin >> choice_ds;

    if (choice_ds == '1') //Binary Search Tree Selection
    {
        BSTree* p_bst = new BSTree();           //for predictions
        BSTree* gt_bst = new BSTree();          //for ground truth

        while (!end)
        {
            print_operation_menu();
            cin >> choice_op;
            end = perform_operation(choice_op,p_bst,gt_bst);
        }
    }

    else if (choice_ds == '2') //AVL Tree Selection
    {
        AVLTree* p_avltree = new AVLTree();         //for predictions
        AVLTree* gt_avltree = new AVLTree();        //for ground truth

        while (!end)
        {
            print_operation_menu();
            cin >> choice_op;
            end = perform_operation(choice_op,p_avltree,gt_avltree);
        }
    }

    else if (choice_ds == '3') //Linked List Selection
    {
        LinkedList* p_linkedlist = new LinkedList();  //for predictions
        LinkedList* gt_linkedlist = new LinkedList();  //for ground truth

        while (!end)
        {
            print_operation_menu();
            cin >> choice_op;
            end = perform_operation(choice_op,p_linkedlist,gt_linkedlist);
        }
    }

    else
    {
        cout << "Error: You have entered an invalid choice" << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

void print_ds_menu()
{
    cout << "Choose a data structure" << endl;
    cout << "1: Binary Search Tree" << endl;
    cout << "2: AVL Tree"<< endl;
    cout << "3: Unsorted Singly Linked List"<< endl;
    cout << "Enter a choice {1,2,3}:";
}

void print_operation_menu()
{
    cout << "Choose an operation" << endl;
    cout << "1: Create ground truth data structure from file" << endl;
    cout << "2: Create prediction data structure from file"<< endl;
    cout << "3: Add a variant prediction"<< endl;
    cout << "4: Delete a variant prediction"<< endl;
    cout << "5: List predictions"<< endl;
    cout << "6: Search a prediction variant from predictions"<< endl;
    cout << "7: Calculate true positive variant count"<< endl;
    cout << "0: Exit" << endl;
    cout << "Enter a choice {1,2,3,4,5,6,7,0}:";
}

bool perform_operation(char choice, LinkedList* p_list, LinkedList* gt_list){
    bool terminate = false;
    ifstream file;
    string line;
    int chromo, pos;
    char alt_base;
    int in_chromo, in_pos;char in_altbase;
    chrono::_V2::system_clock::time_point start_time,end_time;
    chrono::milliseconds duration;

    switch (choice)
    {
    case '1':

        if(gt_flag){
            cout<<"That data structer has already created !!"<<endl;
            break;
        }

        start_time = std::chrono::high_resolution_clock::now(); //starting time

        file.open(file_gt);
        if (file.is_open()) {
        getline(file, line);  //skip first line
        ListNode* temp_ll ;
        ListNode* temp_head;
        

        getline(file,line);
        istringstream iss1(line);
        if(iss1>> chromo >> pos>>alt_base){
            
            temp_head = new ListNode(chromo,pos,alt_base);
            gt_list->set_head(temp_head);
        }

        while (getline(file, line)) {
            istringstream iss(line);

            if (iss >> chromo >> pos >> alt_base) {
                temp_ll = new ListNode(chromo,pos,alt_base);
                temp_head->set_next(temp_ll);
                temp_head = temp_head->get_next();    
            } 
            else {}
        }

        file.close();
        end_time = std::chrono::high_resolution_clock::now();  //end time
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
        cout<<"Ground truth data structure was created from file in "<<duration.count()<<" ms"<<std::endl; 
        } 
        else {
            cout<< "file could not opened"<<endl;
        } // file could not be opened
        
        gt_flag = true;

        print_operation_menu();
        cin >> choice;
        terminate = perform_operation(choice, p_list, gt_list);
        break;
    
    case '2':

        if(predic_flag){
            cout<<"That data structer has already created !!"<<endl;
            break;
        }

        start_time = std::chrono::high_resolution_clock::now(); //starting time

        file.open(file_predict);
        if (file.is_open()) {
        getline(file, line);  //skip first line
        ListNode* temp_ll ;
        ListNode* temp_head;
        

        getline(file,line);
        istringstream iss1(line);
        if(iss1>> chromo >> pos>>alt_base){
            
            temp_head = new ListNode(chromo,pos,alt_base);
            p_list->set_head(temp_head);
        }

        while (getline(file, line)) {
            istringstream iss(line);

            if (iss >> chromo >> pos >> alt_base) {
                temp_ll = new ListNode(chromo,pos,alt_base);
                temp_head->set_next(temp_ll);
                temp_head = temp_head->get_next();    
            } 
            else {}
        }

        file.close();
        end_time = std::chrono::high_resolution_clock::now();  //end time
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
        cout<<"Ground truth data structure was created from file in "<<duration.count()<<" ms"<<std::endl; 
        } 
        else {
            cout<< "file could not opened"<<endl;
        } // file could not be opened
        
        predic_flag = true;

        print_operation_menu();
        cin >> choice;
        terminate = perform_operation(choice, p_list, gt_list);
        break;

    case '3':
        
        cout<<"Enter the CHROM POS and ALT BASE information with a space in between: ";
        cin>>in_chromo>>in_pos>>in_altbase;
        p_list->add_node(in_chromo,in_pos,in_altbase);

        print_operation_menu();
        cin >> choice;
        terminate = perform_operation(choice, p_list, gt_list);
        break;

    case '4':
        
        cout<<"Enter the CHROM POS and ALT BASE information with a space in between: ";
        cin>>in_chromo>>in_pos>>in_altbase;
        p_list->delete_node(in_chromo,in_pos,in_altbase);
        
        print_operation_menu();
        cin >> choice;
        terminate = perform_operation(choice, p_list, gt_list);
        break;

    case '5':
        
        start_time =  std::chrono::high_resolution_clock::now(); //starting time
        
        p_list->list();
        
        end_time = std::chrono::high_resolution_clock::now();  //end time
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
        //cout<<"Listing with Linked List structure: "<<duration.count()<<" ms"<<std::endl;
        
        print_operation_menu();
        cin >> choice;
        terminate = perform_operation(choice, p_list, gt_list);
        break;

    case '6':
        
        cout<<"Enter the CHROM POS and ALT BASE information with a space in between: ";
        cin>>in_chromo>>in_pos>>in_altbase;
        p_list->finding(in_chromo,in_pos,in_altbase);
        
        print_operation_menu();
        cin >> choice;
        terminate = perform_operation(choice, p_list, gt_list);
        break;

    case '7':
        p_list->true_counter(gt_list);

        print_operation_menu();
        cin >> choice;
        terminate = perform_operation(choice, p_list, gt_list);
        break;

    case '0':
        terminate = true;
        delete gt_list;
        delete p_list;
        break;

    default:
        cout << "ERROR: You have entered an invalid choice" << endl << endl;
        print_operation_menu();
        cin >> choice;
        terminate = perform_operation(choice, p_list, gt_list);
        break;
    }
    return terminate;
}

bool perform_operation(char choice, BSTree* p_bst, BSTree* gt_bst){
    bool terminate = false;
    ifstream file;
    string line;
    int chromo, pos;
    char alt_base;
    int in_chromo, in_pos;char in_altbase;
    chrono::_V2::system_clock::time_point start_time,end_time;
    chrono::milliseconds duration;
    BSTNode* temp_bst;
    


    switch (choice)
    {
    case '1':

        if(gt_flag){
            cout<<"That data structer has already created !!"<<endl;
            break;
        }

        start_time = std::chrono::high_resolution_clock::now(); //starting time

        file.open(file_gt);
        if (file.is_open()) {
        getline(file, line);  // skip first line

        while (getline(file, line)) {
            istringstream iss(line);
           

            if (iss >> chromo >> pos >> alt_base) {
                // Verileri kullan
                gt_bst->insert_node(chromo,pos,alt_base);
            } 
            else {}
        }

        file.close();
        end_time = std::chrono::high_resolution_clock::now();  //end time
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
        cout<<"Ground truth data structure was created from file in "<<duration.count()<<" ms"<<std::endl; 
        } 
        else {
            cout<< "file could not opened"<<endl;
        } // file could not be opened
        
        
        gt_flag = true;

        print_operation_menu();
        cin >> choice;
        terminate = perform_operation(choice, p_bst, gt_bst);
        break;
    
    case '2':

        if(predic_flag ){
            cout<<"That data structer has already created !!"<<endl;
            break;
        }

        start_time = std::chrono::high_resolution_clock::now(); //starting time

        file.open(file_predict);
        if (file.is_open()) {
        getline(file, line);  // İlk satırı atla

        while (getline(file, line)) {
            istringstream iss(line);

            if (iss >> chromo >> pos >> alt_base) {
                // Verileri kullan
                p_bst->insert_node(chromo,pos,alt_base);
            } 
            else {}
        }

        file.close();
        end_time = std::chrono::high_resolution_clock::now();  //end time
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
        cout<<"Prediction data structure was created in "<<duration.count()<<" ms"<<std::endl; 
        } 
        else {
            cout<< "file could not opened"<<endl;
        } // file could not be opened
        
        predic_flag = true;

        print_operation_menu();
        cin >> choice;
        terminate = perform_operation(choice, p_bst, gt_bst);
        break;

    case '3':
        
        cout<<"Enter the CHROM POS and ALT BASE information with a space in between: ";
        cin>>in_chromo>>in_pos>>in_altbase;
        p_bst->add_node(in_chromo,in_pos,in_altbase);

        print_operation_menu();
        cin >> choice;
        terminate = perform_operation(choice, p_bst, gt_bst);
        break;

    case '4':
        
        cout<<"Enter the CHROM POS and ALT BASE information with a space in between: ";
        cin>>in_chromo>>in_pos>>in_altbase;
        p_bst->delete_node(in_chromo,in_pos,in_altbase);
        
        print_operation_menu();
        cin >> choice;
        terminate = perform_operation(choice, p_bst, gt_bst);
        break;

    case '5':
            
        start_time = std::chrono::high_resolution_clock::now(); //starting time

        temp_bst = p_bst->get_root();
        while(temp_bst->get_rightchild() != nullptr){
            temp_bst = temp_bst->get_rightchild();
        }
        p_bst->list(p_bst->get_root(),temp_bst);
        
        end_time = std::chrono::high_resolution_clock::now();  //end time
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
        //cout<<"Listing with Binary Search Tree structure: "<<duration.count()<<" ms"<<std::endl;

        print_operation_menu();
        cin >> choice;
        terminate = perform_operation(choice, p_bst, gt_bst);
        break;

    case '6':
        
        cout<<"Enter the CHROM POS and ALT BASE information with a space in between: ";
        cin>>in_chromo>>in_pos>>in_altbase;
        p_bst->finding(in_chromo,in_pos,in_altbase);
        
        print_operation_menu();
        cin >> choice;
        terminate = perform_operation(choice, p_bst, gt_bst);
        break;

    case '7':
        
        p_bst->true_counter(gt_bst);

        print_operation_menu();
        cin >> choice;
        terminate = perform_operation(choice, p_bst, gt_bst);
        break;

    case '0':
        terminate = true;
        delete p_bst;
        delete gt_bst;
        break;

    default:
        cout << "ERROR: You have entered an invalid choice" << endl << endl;
        print_operation_menu();
        cin >> choice;
        terminate = perform_operation(choice, p_bst, gt_bst);
        break;
    }
    return terminate;
}

bool perform_operation(char choice, AVLTree* p_avltree, AVLTree* gt_avltree){
    bool terminate = false;
    ifstream file;
    string line;
    int chromo, pos;
    char alt_base;
    int in_chromo, in_pos;char in_altbase;
    chrono::_V2::system_clock::time_point start_time,end_time;
    chrono::milliseconds duration;
    AVLNode* temp_avl ;


    switch (choice)
    {
    case '1':

        if(gt_flag ){
            cout<<"That data structer has already created !!"<<endl;
            break;
        }

        start_time = std::chrono::high_resolution_clock::now(); //starting time

        file.open(file_gt);
        if (file.is_open()) {
        getline(file, line);  // İlk satırı atla

        while (getline(file, line)) {
            istringstream iss(line);
            

            if (iss >> chromo >> pos >> alt_base) {
                // Verileri kullan
                gt_avltree->insert_node(gt_avltree->get_root2(),chromo,pos,alt_base);
            } 
            else {}
        }

        file.close();
        end_time = std::chrono::high_resolution_clock::now();  //end time
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
        cout<<"Ground truth data structure was created from file in "<<duration.count()<<" ms"<<std::endl; 
        } 
        else {
            cout<< "file could not opened"<<endl;
        } // file could not be opened
        
        gt_flag = true;

        print_operation_menu();
        cin >> choice;
        terminate = perform_operation(choice, p_avltree, gt_avltree);
        break;
    
    case '2':

        if(predic_flag ){
            cout<<"That data structer has already created !!"<<endl;
            break;
        }

        start_time = std::chrono::high_resolution_clock::now(); //starting time

        file.open(file_predict);
        if (file.is_open()) {
        getline(file, line);  // İlk satırı atla

        while (getline(file, line)) {
            istringstream iss(line);

            if (iss >> chromo >> pos >> alt_base) {
                // Verileri kullan
                p_avltree->insert_node(p_avltree->get_root2(),chromo,pos,alt_base);
            } 
            else {}
        }

        file.close();
        end_time = std::chrono::high_resolution_clock::now();  //end time
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
        cout<<"Prediction data structure was created in "<<duration.count()<<" ms"<<std::endl; 
        } 
        else {
            cout<< "file could not opened"<<endl;
        } // file could not be opened

        predic_flag = true;

        print_operation_menu();
        cin >> choice;
        terminate = perform_operation(choice, p_avltree, gt_avltree);
        break;

    case '3':
        
        cout<<"Enter the CHROM POS and ALT BASE information with a space in between: ";
        cin>>in_chromo>>in_pos>>in_altbase;
        p_avltree->add_node(in_chromo,in_pos,in_altbase);

        print_operation_menu();
        cin >> choice;
        terminate = perform_operation(choice, p_avltree, gt_avltree);
        break;

    case '4':

        cout<<"Enter the CHROM POS and ALT BASE information with a space in between: ";
        cin>>in_chromo>>in_pos>>in_altbase;
        p_avltree->delete_node_main(in_chromo,in_pos,in_altbase);
        
        print_operation_menu();
        cin >> choice;
        terminate = perform_operation(choice, p_avltree, gt_avltree);
        break;

    case '5':

        start_time = std::chrono::high_resolution_clock::now(); //starting time

        temp_avl = p_avltree->get_root();
        while(temp_avl-> right != nullptr){
            temp_avl = temp_avl->right;
        }
        p_avltree->list(p_avltree->get_root(),temp_avl);

        end_time = std::chrono::high_resolution_clock::now();  //end time
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
        //cout<<"Listing with AVL Tree structure: "<<duration.count()<<" ms"<<std::endl;
        
        print_operation_menu();
        cin >> choice;
        terminate = perform_operation(choice, p_avltree, gt_avltree);
        break;

    case '6':
        
        cout<<"Enter the CHROM POS and ALT BASE information with a space in between: ";
        cin>>in_chromo>>in_pos>>in_altbase;
        p_avltree->find_node(in_chromo,in_pos,in_altbase);
        
        print_operation_menu();
        cin >> choice;
        terminate = perform_operation(choice, p_avltree, gt_avltree);
        break;

    case '7':
        
        p_avltree->true_counter(gt_avltree);

        print_operation_menu();
        cin >> choice;
        terminate = perform_operation(choice, p_avltree, gt_avltree);
        break;

    case '0':
        terminate = true;
        delete gt_avltree;
        delete p_avltree;
        break;

    default:
        cout << "ERROR: You have entered an invalid choice" << endl << endl;
        print_operation_menu();
        cin >> choice;
        terminate = perform_operation(choice, p_avltree, gt_avltree);
        break;
    }
    return terminate;
}