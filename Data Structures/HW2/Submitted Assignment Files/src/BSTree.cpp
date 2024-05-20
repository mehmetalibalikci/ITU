/* @Author
Student Name: Mehmet Ali Balıkçı

Student ID : 150200059

Date: 06.06.2023*/

#include "BSTree.h"
#include <chrono>
#include <vector>
#include <fstream>
#include <sstream>


// Constructor
BSTree::BSTree(){
    root = nullptr;
}
// Getter method for root
BSTNode* BSTree::getRoot() const {
    return root;
}
// A method to read data from files and fill up the tree with this data 
void BSTree::fillUp(const std::string& file_name, const char& file_type){ // file type: 'g' for gt.txt, 'p' for predict.txt

    std::string line;               
    
    // To pass data in the txt files to the methods of the tree easily
    int chrom;
    int pos;
    char alt_base;
    bool check = true; // Insert method needs it because if a node with the same chrom and pos as those of the node will be inserted
                         // then control becomes false and printing a text explaining it 
    
    std::ifstream input_file(file_name); // Opening the file
     
    if (!input_file) {
        std::cout << "Error opening the file." <<std::endl;
        return;
    }

    // Start the timer
    auto start_time = std::chrono::high_resolution_clock::now();

    getline(input_file, line); // Skip the header line
    
    while (getline(input_file, line)) {
            
            std::istringstream iss(line); // To read column by column 
            iss>>chrom>>pos>>alt_base; // Read the columns one by one      
            root = insert(root, chrom, pos, alt_base, check); // Add data in row one by one to BST
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
// A utility method to call insert method
void BSTree::insert(const int& chrom, const int& pos, const char& alt_base){
   
   // Start the timer
   auto start = std::chrono::high_resolution_clock::now();
   
   bool check = true; // Insert method needs it because if a node with the same chrom and pos as those of the node will be inserted
                        // then control becomes false and printing a text explaining it 

   root = insert(root, chrom, pos, alt_base, check);
   
   // Stop the timer
   auto end = std::chrono::high_resolution_clock::now();
   // Calculate the duration
   std::chrono::duration<double, std::milli> duration = end - start;
   // Print the time
   if (check) std::cout<<""<<chrom<<" "<<pos<<" "<<alt_base<<" was added in "<<duration.count()<<" ms"<<std::endl;
}
// A method to insert a node to BST
BSTNode* BSTree::insert(BSTNode* node, const int& chrom, const int& pos, const char& alt_base, bool& check) {
    BSTNode* newNode = new BSTNode(chrom, pos, alt_base);
    
    if (node == nullptr) {
        return newNode;
    }
    
    BSTNode* current = node;
    BSTNode* parent = nullptr;
    
    while (current != nullptr) {
        parent = current;
        
        if (chrom < current->getChrom()) {
            current = current->getLeft();
        }
        else if (chrom > current->getChrom()) {
            current = current->getRight();
        }
        else {
            if (pos < current->getPos()) {
                current = current->getLeft();
            }
            else if (pos > current->getPos()) {
                current = current->getRight();
            }
            else {
                // Node with same chrom and pos already exists
                std::cout<<"The node to be added already exists"<<std::endl;
                check = false;
                delete newNode; // No need for newNode
                return node; // Returning the same tree
            }
        }
    }
    
    if (chrom < parent->getChrom()) {
        parent->setLeft(newNode);
    }
    else if (chrom > parent->getChrom()) {
        parent->setRight(newNode);
    }
    else {
        if (pos < parent->getPos()) {
            parent->setLeft(newNode);
        }
        else if (pos > parent->getPos()) {
            parent->setRight(newNode);
        }
    }
    
    return node;
}
// A utility method to call remove method
void BSTree::remove(const int& chrom, const int& pos, const char& alt_base){

    bool check = true; // To control if there is the node to be deleted

    // Base Case; The tree is empty
    if(root==nullptr){
        std::cout<<"There is no node in the the tree to remove"<<std::endl;
        return;
    }
    // Start the timer
    auto start = std::chrono::high_resolution_clock::now();

    root = remove(root, chrom, pos, alt_base, check);

    // Stop the timer
    auto end = std::chrono::high_resolution_clock::now();
    // Calculate the duration
    std::chrono::duration<double, std::milli> duration = end - start;
    // Print the time
    if(check)
        std::cout<<""<<chrom<<" "<<pos<<" "<<alt_base<<" was deleted in "<<duration.count()<<" ms"<<std::endl;
    else
        std::cout<<""<<chrom<<" "<<pos<<" "<<alt_base<<" could not be deleted because it could not be found"<<std::endl;
}
// A method to remove a node specified
BSTNode* BSTree::remove(BSTNode* node, const int& chrom, const int& pos, const char& alt_base, bool& check) {
    // The node to be deleted could not be found
    if (node == nullptr) {
        check = false;
        return node;
    }

    BSTNode* current = node;
    BSTNode* parent = nullptr;

    while (current != nullptr) {
        // Comparison according to the numbers of chroms
        if (chrom < current->getChrom()) {
            parent = current;
            current = current->getLeft();
        } 
        else if (chrom > current->getChrom()) {
            parent = current;
            current = current->getRight();
        } 
        else {
            // Comparison according to the numbers of pos when the numbers of chroms equal
            if (pos < current->getPos()) {
                parent = current;
                current = current->getLeft();
            } 
            else if (pos > current->getPos()) {
                parent = current;
                current = current->getRight();
            } 
            else {
                // The node to be deleted was found
                if (chrom == current->getChrom() && pos == current->getPos() && alt_base == current->getAltBase()) {
                    check = true;
                    BSTNode* temp;

                    // No child
                    if (current->getLeft() == nullptr && current->getRight() == nullptr) {
                        if (parent == nullptr) {
                            delete current;
                            return nullptr;
                        }

                        if (parent->getLeft() == current) {
                            parent->setLeft(nullptr);
                        } 
                        else {
                            parent->setRight(nullptr);
                        }
                        delete current;
                        return node;
                    }
                    // One child
                    else if (current->getLeft() == nullptr) {
                        temp = current->getRight();
                        current->setChrom( temp->getChrom() );
                        current->setPos(temp->getPos());
                        current->setAltBase(temp->getAltBase());
                        current->setLeft(temp->getLeft());
                        current->setRight(temp->getRight());
                        delete temp;
                    } 
                    else if (current->getRight() == nullptr) {
                        temp = current->getLeft();
                        current->setChrom( temp->getChrom() );
                        current->setPos(temp->getPos());
                        current->setAltBase(temp->getAltBase());
                        current->setLeft(temp->getLeft());
                        current->setRight(temp->getRight());
                        delete temp;
                    }
                    // Two children
                    else {
                        BSTNode* successor = current->getRight();
                        parent = current;
                        while (successor->getLeft() != nullptr) {
                            parent = successor;
                            successor = successor->getLeft();
                        }
                        current->setChrom( successor->getChrom() );
                        current->setPos(successor->getPos());
                        current->setAltBase(successor->getAltBase());
                        current->setLeft(successor->getLeft());
                        current->setRight(successor->getRight());
                        temp = successor;

                        if (parent->getLeft() == successor) {
                            parent->setLeft(successor->getRight());
                        } 
                        else {
                            parent->setRight(successor->getRight());
                        }
                        delete temp;
                    }
                    return node;
                }
                // There is no node like the node given
                else {
                    check = false;
                    return node;
                }
            }
        }
    }
    check = false;
    return node;
}
// A utility method to find the minumum node
BSTNode* BSTree::findmin(BSTNode* node){

    BSTNode* temp = node;
 
    // loop down to find the leftmost leaf
    while (temp && temp->getLeft() != nullptr)
        temp = temp->getLeft();
    return temp;
}
// A utility method to call inordertraversal method
void BSTree::inOrderTraversal() const {
    inOrderTraversal(root);
}
// A method to show the tree inorder traversal
void BSTree::inOrderTraversal(const BSTNode* node) const {
    if(node==nullptr){
        return;
    }
    inOrderTraversal(node->getLeft());
    std::cout<<""<<node->getChrom()<<" "<<node->getPos()<<" "<<node->getAltBase()<<",";
    inOrderTraversal(node->getRight());
}
// A utility method to call search method
void BSTree::search(const int& chrom, const int& pos, const char& alt_base){

    bool check;  // To control if the node to be searched for was found or not

    // Start the timer
    auto start = std::chrono::high_resolution_clock::now();

    check = search(root, chrom, pos, alt_base);

    // Stop the timer
    auto end = std::chrono::high_resolution_clock::now();
    // Calculate the duration
    std::chrono::duration<double, std::milli> duration = end - start;
    
    // Print the time
    if(check)
        std::cout<<""<<chrom<<" "<<pos<<" "<<alt_base<<" was found in "<<duration.count()<<" ms"<<std::endl;
    else
        std::cout<<""<<chrom<<" "<<pos<<" "<<alt_base<<" could not be found"<<std::endl;
}
// A method to search a node given
BSTNode* BSTree::search(BSTNode* node, const int& chrom, const int& pos, const char& alt_base) {
    if (node == nullptr) {
        return nullptr;
    }

    BSTNode* current = node;

    while (current != nullptr) {
        if (chrom == current->getChrom() && pos == current->getPos() && alt_base == current->getAltBase()) {
            return current;
        }

        // Comparison according to the numbers of chroms
        if (chrom < current->getChrom()) {
            current = current->getLeft();
        } 
        else if (chrom > current->getChrom()) {
            current = current->getRight();
        } 
        else {
            // Comparison according to the numbers of pos when the numbers of chroms equal
            if (pos < current->getPos()) {
                current = current->getLeft();
            } 
            else if (pos > current->getPos()) {
                current = current->getRight();
            } 
            else {
                return current;
            }
        }
    }

    // Node not found
    return nullptr;
}
// A utility method to fill up vectors with the nodes in the trees
void BSTree::pushNodesToVector(std::vector<BSTNode*>& nodes, BSTNode* node) {
    
    if (node == nullptr) {
        return;
    }
    
    pushNodesToVector(nodes, node->getLeft()); // Traverse left subtree
    nodes.push_back(node); // Push current node to vector
    pushNodesToVector(nodes, node->getRight()); // Traverse right subtree
}
// A method to calculate True Positive Count through vectors
void BSTree::calculateTruePositiveCount(BSTree* predict_tree){

    std::vector<BSTNode*> predict_data; // Store the nodes in Predict Tree to compare easily
    std::vector<BSTNode*> gt_data;      // Store the nodes in GT Tree to compare easily

    // Fill up the vectors with the nodes in the trees
    pushNodesToVector(gt_data,root);    
    pushNodesToVector(predict_data,predict_tree->getRoot());
    
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
// A utility method to destroy all of the tree
void BSTree::destroyTree(BSTNode* node) {
    if (node != nullptr) {
        destroyTree(node->getLeft());
        destroyTree(node->getRight());
        delete node;
        node = nullptr;
    }
}
// Destructor
BSTree::~BSTree(){
    // Base Case; Tree is empty
    if(root==nullptr){
        return;
    }
    destroyTree(root);
    root = nullptr;
}