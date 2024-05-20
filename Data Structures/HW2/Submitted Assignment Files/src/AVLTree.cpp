/* @Author
Student Name: Mehmet Ali Balıkçı

Student ID : 150200059

Date: 06.06.2023*/

#include "AVLTree.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<chrono>
#include<vector>

// constructor
AVLTree::AVLTree(){
    root = nullptr;
}
// Getter method for root
AVLNode* AVLTree::getRoot() const {
    return root;
}
// A utility method to calculate the height of a node
int AVLTree::calculateHeight(AVLNode* node){
    if (node == nullptr) {
        return 0;
    }

    int leftHeight = calculateHeight(node->getLeft());
    int rightHeight = calculateHeight(node->getRight());

    return std::max(leftHeight, rightHeight) + 1;
}
// A utility method to calculate the balance factor, that is, height of left subtree - height of right subtree
int AVLTree::calculateDifference(AVLNode* node){
    int left_height = calculateHeight(node->getLeft());
    int right_height = calculateHeight(node->getRight());
    int balance_factor = left_height - right_height;
    return balance_factor;
}
// A utility method to eliminate RR imbalance
AVLNode* AVLTree::RrRotation(AVLNode* parent_node){
    AVLNode* temp;
    temp = parent_node->getRight();
    parent_node->setRight(temp->getLeft());
    temp->setLeft(parent_node);
    return temp;
}
// A utility method to eliminate LL imbalance
AVLNode* AVLTree::LlRotation(AVLNode* parent_node){
    AVLNode* temp;
    temp = parent_node->getLeft();
    parent_node->setLeft(temp->getRight());
    temp->setRight(parent_node);
    return temp;
}
// A utility method to eliminate LR imbalance
AVLNode* AVLTree::LrRotation(AVLNode* parent_node){
    AVLNode* temp;
    // First part: RR rotation
    temp = parent_node->getLeft();
    parent_node->setLeft(RrRotation(temp));
    //Second part: LL rotation
    return LlRotation(parent_node);
}
// A utility method to eliminate RL imbalance
AVLNode* AVLTree::RlRotation(AVLNode* parent_node){
    AVLNode* temp;
    // First part: LL rotation
    temp = parent_node->getRight();
    parent_node->setRight(LlRotation(temp));
    //Second part: RR rotation
    return RrRotation(parent_node);    
}
// A utility method to call balance method
void AVLTree::balance(){
    root = balance(root);
}
// A method to make the binary tree balanced binary tree
AVLNode* AVLTree::balance(AVLNode* node){
    int balance_factor = calculateDifference(node);
    // LL or LR imbalance
    if(balance_factor > 1){
        // LL imbalance
        if( calculateDifference(node->getLeft()) > 0)
            node = LlRotation(node);
        // LR imbalance
        else
            node = LrRotation(node);
    }
    // RR or RL imbalance
    else if(balance_factor < -1){
        // RL imbalance
        if( calculateDifference(node->getRight()) > 0)
            node = RlRotation(node);
        // RR imbalance
        else 
            node = RrRotation(node);
    }
    return node;
}
// A method to read data from files and fill up the tree with this data
void AVLTree::fillUp(std::string file_name, char file_type){

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
    bool check = true; // To control if the node to be added was added or not
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
void AVLTree::insert(int chrom, int pos, char alt_base){
    bool check = true; // To control if the node to be added was added or not
    // Start the timer
    auto start = std::chrono::high_resolution_clock::now();    
        
        root = insert(root, chrom, pos, alt_base, check);
    
    // Stop the timer
    auto end = std::chrono::high_resolution_clock::now();
    // Calculate the duration
    std::chrono::duration<double, std::milli> duration = end - start;
    // Print the time
    if (check)
        std::cout<<""<<chrom<<" "<<pos<<" "<<alt_base<<" was added in "<<duration.count()<<" ms"<<std::endl;    
}
// A method to insert a node to AVL Tree
AVLNode* AVLTree::insert(AVLNode* node, int chrom, int pos, char alt_base, bool& check){
    // Base Case; Tree is empty
    if(node==nullptr){
        AVLNode* newNode = new AVLNode(chrom, pos, alt_base);
        return newNode;
    }
    // Comparison according to the numbers of chroms
    if(chrom < node->getChrom()) node->setLeft( insert(node->getLeft(), chrom, pos, alt_base, check) );
    else if(chrom> node->getChrom()) node->setRight( insert(node->getRight(), chrom, pos, alt_base, check));
    // Comparison according to the numbers of pos when the numbers of chroms equal
    else if(pos < node->getPos()) node->setLeft( insert(node->getLeft(), chrom, pos, alt_base, check) );
    else if(pos > node->getPos()) node->setRight( insert(node->getRight(), chrom, pos, alt_base, check));    
    else if(node->getAltBase()==alt_base){ 
        check = false;
        std::cout<<"The node to be added already exists"<<std::endl;
        return node;
    }   
    else 
        return node;  
    return node;  
    // Update the height of the current node
    node->setHeight(1 + std::max(calculateHeight(node->getLeft()), calculateHeight(node->getRight())));
    
    // Perform AVL tree balancing
    node = balance(node);
    
    // Return the updated node
    return node; 
}
// A utility method to call search method
void AVLTree::search(int chrom, int pos, char alt_base){
    //Base Case; Tree is empty
    if(root==nullptr){
        std::cout<<"There is no node in the tree"<<std::endl;
        return;    
    }
    
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
AVLNode* AVLTree::search(AVLNode* node, int chrom, int pos, char alt_base){
    // Base Case; Tree is empty
    if(node==nullptr){
        return node;
    }
    // Comparison according to the numbers of chroms
    if(chrom < node->getChrom()) return search(node->getLeft(), chrom, pos, alt_base);
    else if(chrom> node->getChrom()) return search(node->getRight(), chrom, pos, alt_base);
    
    // Comparison according to the numbers of pos when the numbers of chroms equal
    else{
        if(pos < node->getPos()) return search(node->getLeft(), chrom, pos, alt_base);
        else if(pos > node->getPos()) return search(node->getRight(), chrom, pos, alt_base);
    }
    if(node->getChrom()==chrom && node->getPos()==pos && node->getAltBase()==alt_base){
        return node;
    }
    return nullptr;
}
// A utility method to fill up vectors with the nodes in the trees
void AVLTree::pushNodesToVector(std::vector<AVLNode*>& nodes, AVLNode* node){     
    if (node == nullptr) {
        return;
    }
    
    pushNodesToVector(nodes, node->getLeft()); // Traverse left subtree
    nodes.push_back(node); // Push current node to vector
    pushNodesToVector(nodes, node->getRight()); // Traverse right subtree
}
// A method to calculate True Positive Count through vectors
void AVLTree::calculateTruePositiveCount(AVLTree* predict_tree){

    std::vector<AVLNode*> predict_data; // Store the nodes in Predict Tree to compare easily
    std::vector<AVLNode*> gt_data;      // Store the nodes in GT Tree to compare easily

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
// A utility method to find the minumum node
AVLNode* AVLTree::findmin(AVLNode* node){
    AVLNode* temp = node;
    // loop down to find the leftmost leaf
    while (temp && temp->getLeft() != nullptr)
        temp = temp->getLeft();
    return temp;
}
// A utility method to call remove method
void AVLTree::remove(int chrom, int pos, char alt_base){
    // Base Case; The tree is empty
    if(root==nullptr){
        std::cout<<"There is no node in the the tree to remove"<<std::endl;
        return;
    }
    
    bool check = true; // To control if there is the node to be deleted
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
AVLNode* AVLTree::remove(AVLNode* node, int chrom, int pos, char alt_base, bool& check){
    if(node==nullptr){
        check = false;
        return node;
    }
    // Searching to find the place of node to be deleted
    // Comparison according to the numbers of chroms
    if(chrom < node->getChrom()) node->setLeft(remove(node->getLeft(), chrom, pos, alt_base, check) ); 
    else if(chrom> node->getChrom()) node->setRight(remove(node->getRight(), chrom, pos, alt_base, check) );
    
    // Comparison according to the numbers of pos when the numbers of chroms equal
    else if(pos < node->getPos()) node->setLeft(remove(node->getLeft(), chrom, pos, alt_base, check) ); 
    else if(pos > node->getPos()) node->setRight(remove(node->getRight(), chrom, pos, alt_base, check) );  
    
    // The node to be deleted was found    
    else if(node->getChrom()==chrom && node->getPos()==pos && node->getAltBase()==alt_base){
        // There is 3 condition for the node to be deleted
        // No child of the node to remove
        // One child of the node to remove
        // Two child of the node to remove
        
        // No child
        if(node->getLeft()==nullptr && node->getRight()==nullptr){
            delete node;
            node = nullptr;
            return node;
        }
        // one child 
        else if(node->getLeft()==nullptr){
            AVLNode* temp = node;
            node = node->getRight();
            delete temp;
            return node;
        }
        // one child 
        else if(node->getRight()==nullptr){
            AVLNode* temp = node;
            node = node->getLeft();
            delete temp;
            return node;
        }
        // Two child
        else{  
            AVLNode* temp = findmin(node->getRight());
            node->setChrom(temp->getChrom());
            node->setPos(temp->getPos());
            node->setAltBase(temp->getAltBase());
            node->setRight( remove(node->getRight(),temp->getChrom(),temp->getPos(),temp->getAltBase(), check) );
        }                    
    }
    // There is no node like the node given
    else{
        check = false;
        return node;
    }
    
    // Update the height of the current node
    node->setHeight(1 + std::max(calculateHeight(node->getLeft()), calculateHeight(node->getRight())));
    
    // Perform AVL tree balancing
    node = balance(node);
    
    // Return the updated node
    return node; 
}
// A utility method to call inordertraversal method
void AVLTree::inOrderTraversal(){
    // Base Case; Tree is empty
    if(root==nullptr){
        std::cout<<"The tree is empty"<<std::endl;
        return;
    }
    inOrderTraversal(root);
}
// A method to show the tree inorder traversal
void AVLTree::inOrderTraversal(AVLNode *node){
    //Base Case
    if(node==nullptr){
        return;
    }
    inOrderTraversal(node->getLeft());
    std::cout<<""<<node->getChrom()<<" "<<node->getPos()<<" "<<node->getAltBase()<<",";
    inOrderTraversal(node->getRight());
}
// A utility method to destroy all of the tree
void AVLTree::destroyTree(AVLNode* node){
    // Base Case; The tree is empty
    if(node==nullptr)
        return;
    // The tree is not empty
    destroyTree(node->getLeft());
    destroyTree(node->getRight());
    delete node;
    node = nullptr;
}
// Destructor
AVLTree::~AVLTree(){
    destroyTree(root);
}
