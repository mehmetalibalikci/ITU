#include <iostream>
#include <string>
#include "MultiNode.h"

using namespace std;
University::University(string faculty, string uni, string discount, string city, string language, string score_last, string range_last, string score_first, string range_first, string range_average, string score_average){
    
}

string University::get_uni()
{

}

void University::set_up(University* next){

}
University* University::getNext(){

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

}

void Department::set_up(University* under){

}

string Department::get_Department(){

}

int Department::get_numOfUni(){

}

Department* Department::getNext(){

}

Department* Department::getPrev(){

}

void Department::set_next(Department *next){

}

void Department::increase(){ // increase the number of university

}

void Department::set_prev(Department *prev){

}
