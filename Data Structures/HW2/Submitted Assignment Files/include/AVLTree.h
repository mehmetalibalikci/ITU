/* @Author
Student Name: Mehmet Ali Balıkçı

Student ID : 150200059

Date: 06.06.2023*/

#pragma once

#include "AVLNode.h"
#include <string>
#include <vector>

class AVLTree{
    private:
        AVLNode* root;
    public:
        AVLTree(); //constructor
        AVLNode* getRoot() const; // Getter method for root
        int calculateHeight(AVLNode* node); // A utility method to calculate the height of a node
        int calculateDifference(AVLNode* node); // A utility method to calculate the balance factor, that is, height of left subtree - height of right subtree
        AVLNode* RrRotation(AVLNode* parent_node); // A utility method to eliminate RR imbalance
        AVLNode* LlRotation(AVLNode* parent_node); // A utility method to eliminate LL imbalance
        AVLNode* LrRotation(AVLNode* parent_node); // A utility method to eliminate LR imbalance
        AVLNode* RlRotation(AVLNode* parent_node); // A utility method to eliminate RL imbalance
        void balance(); // A utility method to call balance method
        AVLNode* balance(AVLNode* node); // A method to make the binary tree balanced binary tree
        void fillUp(std::string file_name, char file_type); // A method to read data from files and fill up the tree with this data 
        void insert(int chrom, int pos, char alt_base); // A utility method to call insert method
        AVLNode* insert(AVLNode* node, int chrom, int pos, char alt_base, bool& check); // A method to insert a node to AVL Tree
        void search(int chrom, int pos, char alt_base); // A utility method to call search method
        AVLNode* search(AVLNode* node, int chrom, int pos, char alt_base); // A method to search a node given
        void pushNodesToVector(std::vector<AVLNode*>& nodes, AVLNode* node); // A utility method to fill up vectors with the nodes in the trees
        void calculateTruePositiveCount(AVLTree* predict_tree); // A method to calculate True Positive Count through vectors            
        AVLNode* findmin(AVLNode* root); // A utility method to find the minumum node
        void remove(int chrom, int pos, char alt_base); // A utility method to call remove method
        AVLNode* remove(AVLNode* node, int chrom, int pos, char alt_base, bool& check); // A method to remove a node specified
        void inOrderTraversal(); // A utility method to call inordertraversal method
        void inOrderTraversal(AVLNode* node); // A method to show the tree inorder traversal
        void destroyTree(AVLNode* node); // A utility method to destroy all of the tree
        ~AVLTree(); // destructor
};