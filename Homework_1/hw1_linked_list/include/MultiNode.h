/* @Author
Name: Ramazan Taş
Date: 23.04.2023 */

#pragma once
#include <string>

using namespace std;

class University{
private:
    University* up = NULL;
    
    string faculty {};
    string discount {};
    string city{};
    string uniName{};
    string lang{};
    string score_last{};
    string range_last{};
    string score_first{};
    string range_first{};
    string average_range{};
    string average_score{};
    
public:

    University(string, string, string, string, string, string, string, string, string, string, string);
    ~University(){};
    University* get_up() ;
    void set_up(University*);
    string get_uni();
    void printDetails();
};

class Department{
private:
    string department="";
    int numOfUniversity {};
    Department* next = NULL;
    Department* prev = NULL;
    University* upp = NULL;
    
public:

    Department(string);
    ~Department();

    Department* get_next() ;
    Department* get_prev() ;
    string get_Department() ;
    int get_numOfUni() ;
    University* get_upp() ;
    void increase();
    void set_next(Department* );
    void set_upp(University*);
    void set_prev(Department*);
};
