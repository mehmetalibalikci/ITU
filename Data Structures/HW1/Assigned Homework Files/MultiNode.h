#pragma once
#include <string>

using namespace std;
class University{
private:
    string faculty;
    string discount;
    string city;
    string uniName;
    string lang;
    string score_last;
    string range_last;
    string score_first;
    string range_first;
    string average_range;
    string average_score;
    University* next;

public:
    
    University(string, string, string, string, string, string, string, string, string, string, string);
    University* getNext();
    void set_up(University*);
    string get_uni();
    void printDetails();
};

class Department{
private:
    string department;
    int numOfUniversity;
    Department* next;
    Department* prev;
    University* under;
public:

    Department(string);
    Department* getNext();
    Department* getPrev();
    string get_Department();
    int get_numOfUni();
    University* getunder();
    void increase();
    void set_next(Department* );
    void set_up(University*);
    void set_prev(Department*);
};
