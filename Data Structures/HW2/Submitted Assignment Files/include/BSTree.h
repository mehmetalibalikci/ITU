/* @Author
Student Name: Mehmet Ali Balıkçı

Student ID : 150200059

Date: 06.06.2023*/

#pragma once

#include "BSTNode.h"
#include <iostream>
#include <vector>

class BSTree{
    private:
        BSTNode* root;

    public:
        BSTree(); // constructor
        BSTNode* getRoot() const; // Getter method for root
        void fillUp(const std::string& file_name, const char& file_type); // A method to read data from files and fill up the tree with this data          
        void insert(const int& chrom, const int& pos, const char& alt_base); // a utility method to call the insert method
        BSTNode* insert(BSTNode* root, const int& chrom, const int& pos, const char& alt_base, bool& check); // a method for insertion of a node
        void remove(const int& chrom, const int& pos, const char& alt_base); // a utility method to call the remove method
        BSTNode* remove(BSTNode* root, const int& chrom, const int& pos, const char& alt_base, bool& check); // a method for removing of a node
        BSTNode* findmin(BSTNode* root); // a utility method to find the smallest node
        void inOrderTraversal() const; // a utility method to call the inordertraversal method
        void inOrderTraversal(const BSTNode* root) const ;  // a method for traversing of the tree
        void search(const int& chrom, const int& pos, const char& alt_base); // a utility method to call the search method
        BSTNode* search(BSTNode* root, const int& chrom, const int& pos, const char& alt_base); // a method for searching for a node
        void pushNodesToVector(std::vector<BSTNode*>& nodes, BSTNode* node); // A utility method to fill up vectors with the nodes in the trees
        void calculateTruePositiveCount(BSTree* predict_tree); // A method to calculate True Positive Count through vectors
        void destroyTree(BSTNode* root);    // a utility method to remove all of the nodes in the tree
        ~BSTree(); // destructor
};
    