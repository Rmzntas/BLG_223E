/* @Author
Name: Ramazan Taş
Date: 23.04.2023 */


#include <iostream>
#include <string>
#include "MultiNode.h"

using namespace std;
University::University(string in_faculty, string in_uni, string in_discount, string in_city, string in_language, string in_score_last, string in_range_last, string in_score_first, string in_range_first, string in_range_average, string in_score_average){
    faculty = in_faculty;
    uniName = in_uni;
    discount = in_discount;
    city = in_city;
    lang = in_language;
    score_last = in_score_last;
    score_first = in_score_first;
    range_last = in_range_last;
    range_first = in_range_first;
    average_score = in_score_average;
    average_range = in_range_average;
}

string University::get_uni() {
    return uniName;
}

void University::set_up(University* in_up){
    up = in_up;
}
University* University::get_up() {
    return up;
}

void University::printDetails(){
    cout << "Faculty: " << this->faculty << endl;
    cout << "Discount: " << this->discount << endl;
    cout << "City: " << this->city << endl;
    cout << "Language: " << this->lang << endl;
    cout << "Score Last: " << this->score_last << endl;
    cout << "Range Last: " << this->range_last << endl;
    cout << "Score First: " << this->score_first << endl;
    cout << "Range First: " << this->range_first << endl;
    cout << "Score Average: " << this->average_score << endl;
    cout << "Range Average: " << this->average_range << endl;
    cout << "----------------" << endl;

}


Department::Department(string in_department){
    department = in_department;
}

void Department::set_upp(University* in_up){
    upp = in_up;
}

string Department::get_Department() {
    return department;
}

int Department::get_numOfUni() {
    return numOfUniversity;
}

Department* Department::get_next(){
    return next;
}

Department* Department::get_prev() {
    return prev;
}

University* Department::get_upp(){
    return upp;
}

void Department::set_next(Department *in_next){
    next = in_next;
}

void Department::increase(){ // increase the number of university
    numOfUniversity++;
}

void Department::set_prev(Department *in_prev){
    prev = in_prev;
}

Department::~Department() {
    University* curr = upp;
    while (curr != NULL) {
        University* temp = curr;
        curr = curr->get_up();
        delete temp;
    }
}
