/* @Author
Student Name: Mehmet Ali Balıkçı

Student ID : 150200059

Date: 06.06.2023*/

#pragma once

#include "ListNode.h"
#include <vector>
#include <string>

class LinkedList{
    private:
        ListNode* head;
        ListNode* tail;
    public:
        LinkedList(); //constructor
        ListNode* getHead() const; // Getter method for head
        void fillUp(const std::string& file_name, const char& file_type); // A method to read data from files and fill up the tree with this data 
        void insert(const int& chrom, const int& pos, const char& alt_base, bool count_time=true); // a method to insert a node to the tree
        void remove(const int& chrom, const int& pos, const char& alt_base); // a method to remove a node from the tree
        void traverse(); // a method to traverse all of the nodes in the tree
        void search(const int& chrom, const int& pos, const char& alt_base); // a method to search for a node in the tree
        void pushNodesToVector(std::vector<ListNode*>& nodes, ListNode* node); // A utility method to fill up vectors with the nodes in the trees
        void calculateTruePositiveCount(const LinkedList* predict_ll); // A method to calculate True Positive Count through vectors        
        ~LinkedList(); // destructor
};
