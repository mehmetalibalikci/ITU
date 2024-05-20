#pragma once

#include "MultiNode.h"
#include <string>
class MultiList{
private:
    Department* head;
    Department* tail;
public:
    MultiList();
    ~MultiList();
    void add_node(string, string, string, string, string, string, string, string, string, string, string, string);
    void add_uni_node(Department*,string, string, string, string, string, string, string, string, string, string, string);
    void add_dep_uni_node(Department*,string,string, string, string, string, string, string, string, string, string, string, string);    
    void select_department();
    void select_uni();
    void listDepartments();
};