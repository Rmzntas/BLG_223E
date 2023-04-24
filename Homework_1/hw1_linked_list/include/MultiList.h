/* @Author
Name: Ramazan Taş
Date: 23.04.2023 */

#pragma once

#include <chrono>
#include "MultiNode.h"
#include <string>

class MultiList{
private:
    Department* head = NULL;
    Department* tail = NULL;
    int num_of_departmant{}; // will increase each time new departmant added;
public:
    MultiList(); 
    ~MultiList();
    void add_node(string, string, string, string, string, string, string, string, string, string, string, string);
    void add_uni_node(Department*,string, string, string, string, string, string, string, string, string, string, string);
    void add_dep_uni_node(Department*,string,string, string, string, string, string, string, string, string, string, string, string);    
    void select_department();
    void select_uni();
    void listDepartments();
    int get_num_of_dep(){return num_of_departmant;};
};