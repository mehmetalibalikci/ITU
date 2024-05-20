/* @Author
Student Name: Mehmet Ali Balıkçı

Student ID : 150200059

Date: 06.06.2023*/

#include "LinkedList.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<chrono>
#include<vector>

// Constructor
LinkedList::LinkedList(){
    head = nullptr;
    tail = nullptr;
}
// Getter method for head
ListNode* LinkedList::getHead() const{
    return head;
}
// A method to read data from files and fill up the tree with this data
void LinkedList::fillUp(const std::string& file_name, const char& file_type){

    std::string line;               
    
    // To pass data in the txt files to the methods of the tree easily
    int chrom;
    int pos;
    char alt_base;

    std::ifstream input_file(file_name); // Opening the file
    
    if (!input_file) {
        std::cout << "Error opening the file." <<std::endl;
        return;
    }

    // Start the timer
    auto start_time = std::chrono::high_resolution_clock::now();

    getline(input_file, line); // Skip the header line
    
    while (getline(input_file, line)) { // Read the file line by line
            
            std::istringstream iss(line); // To read column by column 
            iss>>chrom>>pos>>alt_base; // Read the columns one by one            
            insert(chrom, pos, alt_base, false); // Add data in row one by one to BST
    }   
    // Stop the timer
    auto end_time = std::chrono::high_resolution_clock::now();
    
    // Calculate the duration
    std::chrono::duration<double, std::milli> duration = end_time - start_time;
    // Print the duration
    if(file_type =='g')
        std::cout<<"Ground truth data structure was created from file in "<<duration.count()<<" ms"<<std::endl;
    else
        std::cout<<"Prediction data structure was created in "<<duration.count()<<" ms"<<std::endl;    
}
// Insertion a node to the Linked List
void LinkedList::insert(const int& chrom, const int& pos, const char& alt_base, bool count_time){
    
    std::chrono::high_resolution_clock::time_point start; // start variable for timer

    // Start the timer
    if(count_time) 
        start = std::chrono::high_resolution_clock::now();   

    ListNode* new_node = new ListNode(chrom, pos, alt_base);
    
    // The list is empty
    if (head == nullptr) {
        head = new_node;
        tail = new_node;
    } 
    // The list is not empty
    else {
        tail->setNext(new_node);
        tail = new_node;
    }
    if(count_time){   
        // Stop the timer
        auto end = std::chrono::high_resolution_clock::now();
        // Calculate the duration
        std::chrono::duration<double, std::milli> duration = end - start;
        // Print the time
        std::cout<<""<<chrom<<" "<<pos<<" "<<alt_base<<" was added in "<<duration.count()<<" ms"<<std::endl;
    } 

}
// Deletion a node from the Linked List
void LinkedList::remove(const int& chrom, const int& pos, const char& alt_base){
    // Start the timer
    auto start = std::chrono::high_resolution_clock::now();
    
    ListNode* curr = head;
    ListNode* prev = nullptr;

    while (curr) {
        if (curr->getChrom() == chrom && curr->getPos() == pos && curr->getAltBase() == alt_base) {
            if (curr == head) {
                head = curr->getNext();
                if (head == nullptr) { // There was only one node in the list
                    tail = nullptr;
                }
            } 
            else {
                prev->setNext(curr->getNext());
                if (curr == tail) {
                    tail = prev;
                }
            }
            delete curr;
            
            // Stop the timer
            auto end = std::chrono::high_resolution_clock::now();
            // Calculate the duration
            std::chrono::duration<double, std::milli> duration = end - start;
            // Print the time
            std::cout<<""<<chrom<<" "<<pos<<" "<<alt_base<<" was deleted in "<<duration.count()<<" ms"<<std::endl;            
            
            return;
        }

        prev = curr;
        curr = curr->getNext();
    }
    // Stop the timer
    auto end = std::chrono::high_resolution_clock::now();
    // Calculate the duration
    std::chrono::duration<double, std::milli> duration = end - start;
    // Print the time
    
    std::cout<<""<<chrom<<" "<<pos<<" "<<alt_base<<" could not be deleted because it could not be found"<<std::endl;
}
// Traverse the list
void LinkedList::traverse(){
    ListNode* temp = head;
    while(temp->getNext()){
        std::cout<<""<<temp->getChrom()<<" "<<temp->getPos()<<" "<<temp-> getAltBase()<<",";
        temp=temp->getNext();
    }
    std::cout<<""<<temp->getChrom()<<" "<<temp->getPos()<<" "<<temp-> getAltBase();
}
// Searching for a data
void LinkedList::search(const int& chrom, const int& pos, const char& alt_base){
    // Start the timer
    auto start = std::chrono::high_resolution_clock::now();
    
    ListNode* temp = head;
    
    while(temp){
        if(temp->getChrom()==chrom && temp->getPos()==pos && temp-> getAltBase()==alt_base){
            // Stop the timer
            auto end = std::chrono::high_resolution_clock::now();
            // Calculate the duration
            std::chrono::duration<double, std::milli> duration = end - start;

            std::cout<<""<<chrom<<" "<<pos<<" "<<alt_base<<" was found in "<<duration.count()<<" ms"<<std::endl;
            
            return;
        }
        temp=temp->getNext();
    }
    std::cout<<""<<chrom<<" "<<pos<<" "<<alt_base<<" could not be found"<<std::endl;
}
// A utility method to fill up vectors with the nodes in the trees
void LinkedList::pushNodesToVector(std::vector<ListNode*>& nodes, ListNode* head_node){
    if (head_node == nullptr) {
        return;
    }
    while(head_node){
        nodes.push_back(head_node);
        head_node = head_node->getNext();
    }    
}
// A method to calculate True Positive Count through vectors
void LinkedList::calculateTruePositiveCount(const LinkedList* predict_ll){
    std::vector<ListNode*> gt_data;      // Store the nodes in GT Linked List to compare easily
    std::vector<ListNode*> predict_data; // Store the nodes in Predict Linked List to compare easily

    // Fill up the vectors with the nodes in the trees
    pushNodesToVector(gt_data,head);    
    pushNodesToVector(predict_data,predict_ll->getHead());

    int truePositiveCount = 0;

    // Start the timer
    auto start_time = std::chrono::high_resolution_clock::now();  
    
    // Iterate over each predicted node
    for (const auto& predictNode : predict_data) {
        // Search for the predicted node in the ground truth data
        for (const auto& gtNode : gt_data) {
            if (predictNode->getChrom() == gtNode->getChrom() &&
                predictNode->getPos() == gtNode->getPos() &&
                predictNode->getAltBase() == gtNode->getAltBase()) {
                // Found a true positive
                truePositiveCount++;
                break; // Move to the next predicted node
            }
        }
    }
    // Stop the timer
    auto end_time = std::chrono::high_resolution_clock::now();
    // Calculate the duration
    std::chrono::duration<double, std::milli> duration = end_time - start_time;

    std::cout << "True positive variant count is "<<truePositiveCount<<". "<<"It took "<<duration.count()<<" ms to calculate."<<std::endl;        
} 
// Destructor
LinkedList::~LinkedList(){
    ListNode* temp = head;

    // Deleting all the nodes in the list
    while(temp){
        head = head->getNext();
        delete temp;
        temp = head;
    }
    tail = nullptr;
}