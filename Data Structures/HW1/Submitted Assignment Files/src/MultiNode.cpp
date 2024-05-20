/*
Student Name: Mehmet Ali Balıkçı
Student ID: 150200059

*/

#include <iostream>
#include <string>
#include "MultiNode.h"

using namespace std;
University::University(string faculty, string uni, string discount, string city, string language, string score_last, string range_last, string score_first, string range_first, string range_average, string score_average){
    this->faculty = faculty;
    this->uniName = uni;
    this->discount = discount;
    this->city = city;
    this->lang = language;
    this->score_last = score_last;
    this->range_last = range_last;
    this->score_first = score_first;
    this->range_first = range_first;
    this->average_range = range_average;
    this->average_score = score_average;
}

string University::get_uni(){
    return uniName;
    
}

void University::set_up(University* next){
    this->next = next; 
}

University* University::getNext(){
    return next;
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

Department::Department(string department){
    this->department = department;
    this->numOfUniversity = 0;
}

void Department::set_up(University* under){
    this->under = under;
}

string Department::get_Department(){
    return department;
}

int Department::get_numOfUni(){
    return numOfUniversity;
}

Department* Department::getNext(){
    return next;
}

University* Department::getunder(){
    return under;
}

Department* Department::getPrev(){
    return prev;
}

void Department::set_next(Department *next){
    this->next = next;
}

void Department::increase(){ // increase the number of university
    numOfUniversity++;
}

void Department::set_prev(Department *prev){
    this->prev = prev;
}
