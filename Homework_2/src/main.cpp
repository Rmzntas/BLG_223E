#include <iostream>
#include <vector>
#include "LinkedList.h"
#include "AVLTree.h"
#include "BSTree.h"
#include <fstream>
#include <string>

using namespace std;

void print_ds_menu();
void print_operation_menu();
bool perform_operation(char, LinkedList*, LinkedList*);
bool perform_operation(char, BSTree*, BSTree*);  
bool perform_operation(char, AVLTree*, AVLTree*);

int main()
{
    string file_gt = "../gt.txt";
    string file_predict = "../predict.txt";
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

    switch (choice)
    {
    case '1':
        
        print_operation_menu();
        cin >> choice;
        terminate = perform_operation(choice, p_list, gt_list);
        break;
    
    case '2':

        print_operation_menu();
        cin >> choice;
        terminate = perform_operation(choice, p_list, gt_list);
        break;

    case '3':
        int in_chromo, in_pos;char in_altbase;
        cout<<"Enter the CHROM POS and ALT BASE information with a space in between: ";
        cin>>in_chromo>>in_pos>>in_altbase;
        p_list->add_node(in_chromo,in_pos,in_altbase);

        print_operation_menu();
        cin >> choice;
        terminate = perform_operation(choice, p_list, gt_list);
        break;

    case '4':
        int in_chromo, in_pos;char in_altbase;
        cout<<"Enter the CHROM POS and ALT BASE information with a space in between: ";
        cin>>in_chromo>>in_pos>>in_altbase;
        p_list->delete_node(in_chromo,in_pos,in_altbase);
        
        print_operation_menu();
        cin >> choice;
        terminate = perform_operation(choice, p_list, gt_list);
        break;

    case '5':
        p_list->list();
        
        print_operation_menu();
        cin >> choice;
        terminate = perform_operation(choice, p_list, gt_list);
        break;

    case '6':
        int in_chromo, in_pos;char in_altbase;
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

    switch (choice)
    {
    case '1':
        
        print_operation_menu();
        cin >> choice;
        terminate = perform_operation(choice, p_bst, gt_bst);
        break;
    
    case '2':

        print_operation_menu();
        cin >> choice;
        terminate = perform_operation(choice, p_bst, gt_bst);
        break;

    case '3':
        int in_chromo, in_pos;char in_altbase;
        cout<<"Enter the CHROM POS and ALT BASE information with a space in between: ";
        cin>>in_chromo>>in_pos>>in_altbase;
        p_bst->add_node(in_chromo,in_pos,in_altbase);

        print_operation_menu();
        cin >> choice;
        terminate = perform_operation(choice, p_bst, gt_bst);
        break;

    case '4':
        int in_chromo, in_pos;char in_altbase;
        cout<<"Enter the CHROM POS and ALT BASE information with a space in between: ";
        cin>>in_chromo>>in_pos>>in_altbase;
        //p_bst->delete_node(in_chromo,in_pos,in_altbase);
        
        print_operation_menu();
        cin >> choice;
        terminate = perform_operation(choice, p_bst, gt_bst);
        break;

    case '5':
        BSTNode* temp = p_bst->get_root();
        while(temp->get_rightchild() != nullptr){
            temp = temp->get_rightchild();
        }
        p_bst->list(p_bst->get_root(),temp);
        
        print_operation_menu();
        cin >> choice;
        terminate = perform_operation(choice, p_bst, gt_bst);
        break;

    case '6':
        int in_chromo, in_pos;char in_altbase;
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
