// EB
// Implementing Binary Search Tree in C++

#include <iostream>

namespace BST {
  struct Node {
    int data;
    std::string name;
    Node *parent;
    Node *left;
    Node *right;
  };
}

class BinarySearchTree {
private:
  BST::Node* root;
public:
  BinarySearchTree() : root(nullptr){  // Initialize root node
  }
  // Utility function to call the main preorder method
  void preorder(std::pair<std::string, int>* array, int index) {
    preorderSorting(root, array, index);  // Call the main method
  }
  // To make preorder algorithm recursive way
  void preorderSorting(BST::Node* root, std::pair<std::string, int>* array, int& index){
    if(root != NULL){
      array[index++] = std::make_pair(root->name, root->data); // Add city information to array
      preorderSorting(root->left, array, index);  // Traverse left 
      preorderSorting(root->right, array, index); // Traverse right   
    }
  }
  // Utility function to call the main inorder method
  void inorder(std::pair<std::string, int>* array, int index) {   
    inorderSorting(root, array, index);  // Call the main method
  }
  // To make inorder algorithm recursive way
  void inorderSorting(BST::Node* root, std::pair<std::string, int>* array, int& index) {
    if(root != NULL){
      inorderSorting(root->left, array, index);  // Traverse left 
      array[index++] = std::make_pair(root->name, root->data); // Add city information to array
      inorderSorting(root->right, array, index); // Traverse right 
    }
  }
  // Utility function to call the main postorder method 
  void postorder(std::pair<std::string, int>* array, int index) {   
    postOrderSorting(root, array, index); // Call the main method
  }
  // To make postorder algorithm recursive way
  void postOrderSorting(BST::Node* root, std::pair<std::string, int>* array, int& index){
    if(root != NULL){
      postOrderSorting(root->left, array, index); // Traverse left 
      postOrderSorting(root->right, array, index); // Traverse right 
      array[index++] = std::make_pair(root->name, root->data); // Add city information to array
    }
  }
  // Search a value
  BST::Node* searchTree(int cityPopulation) {
    BST::Node* temp = root;
    while (temp != NULL){
      if(cityPopulation > temp->data)
        temp = temp->right; // Go right subtree due to searching bigger value
      else if(cityPopulation < temp->data)
        temp = temp->left;  // Go left subtree due to searching smaller value
      else 
        return temp;  // Found the value searched for
    }
    return temp;
  }
  // Find the successor node of keynode
  BST::Node* successor(BST::Node* keyNode) {
    // Find the minimum value of subtree of the keynode
    if (keyNode->right != NULL)
        return findMinimum(keyNode->right);

    // Scan the parent nodes
    BST::Node* parentNode = keyNode->parent;
    while (parentNode != NULL && keyNode == parentNode->right) {
        keyNode = parentNode;
        parentNode = parentNode->parent;
    }
    return parentNode;
  }
  // Find the successor node of keynode
  BST::Node* predecessor(BST::Node* keyNode) {
    // Find the maksimum value of subtree of the keynode
    if (keyNode->left != NULL)
        return findMaksimum(keyNode->left);

    // Scan the parent nodes
    BST::Node* parentNode = keyNode->parent;
    while (parentNode != NULL && keyNode == parentNode->left) {
        keyNode = parentNode;
        parentNode = parentNode->parent;
    }
    return parentNode;
  }
  // Insert a node to the tree
  void insert(std::string cityName, int cityPopulation) {
      // If the tree is empty, then create the root node
      if(root == NULL){
        root = newNode(cityName, cityPopulation);  
        return;
      }
      
      BST::Node* child = newNode(cityName, cityPopulation); // Create child node
      BST::Node* temp = root; // Create a temp node to find the place where the child node will be added

      while (temp != NULL){ 
        // Go right subtree if child value is equal or bigger than the that of parent
        if(child->data >= temp->data){
          // Place the child node if the right place of parent node is empty
          if(temp->right == NULL){
            temp->right = child;
            child->parent = temp;
            break;
          }
          // Else continue to go right subtree
          else{
            temp = temp->right;
          }
        }
          // Go left subtree if child value is smaller than the that of parent
        else{
          // Place the child node if the left place of parent node is empty
          if(temp->left == NULL){
            temp->left = child;
            child->parent = temp;
            break;
            }
          // Else continue to go left subtree
          else{
            temp = temp->left;
          }
        }
      }
  }
  // Delete a node from the tree
  void deleteNode(int cityPopulation) {
    if(root == NULL)
      return;
    deleteNodeFromTree(root, cityPopulation);      
  }
  // Delete a node
  BST::Node* deleteNodeFromTree(BST::Node* root, int cityPopulation){
    if (root == NULL) return root;
    if (cityPopulation < root->data)
        root->left = deleteNodeFromTree(root->left, cityPopulation);
    else if (cityPopulation > root->data)
        root->right = deleteNodeFromTree(root->right, cityPopulation);
    else {
        if (root->left == NULL) {
            BST::Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == NULL) {
            BST::Node* temp = root->left;
            delete root;
            return temp;
        }
        BST::Node* temp = findMinimum(root->right);
        root->data = temp->data;
        root->right = deleteNodeFromTree(root->right, temp->data);
    }
    return root; 
    }
  // Calculate the height of the tree recursively
  int calculateHeight(BST::Node* node){  
    if (node == NULL)
        return 0;
    else {
        int leftHeight = calculateHeight(node->left); //Calculate the high of left subtree
        int rightHeight = calculateHeight(node->right); //Calculate the high of right subtree
        
        // Choose the bigger one
        if (leftHeight > rightHeight)  
            return (leftHeight + 1);
        else
            return (rightHeight + 1);
    }
  }
  // Utility method to call main method 
  int getHeight() {
      return calculateHeight(root) - 1; // height is calculated 1 more in main method, subtract it here 
    }
  // Find the node having maximum value to use in other methods
  BST::Node* findMaksimum(BST::Node* node){
    BST::Node* temp = node;
    
    // Go right subtree to find maximum value
    while(temp->right != NULL){
      temp = temp->right;
    }
    return temp; 
  }
  // Find the node having maximum value in the tree
  BST::Node* getMaximum() {
    return findMaksimum(root);
  }
  // Find the node having minimum value to use in other methods
  BST::Node* findMinimum(BST::Node* node){
    BST::Node* temp = node;

    // Go right subtree to find maximum value
    while(temp->left != NULL){
      temp = temp->left;
    }
    return temp;  
  }
  // Find the node having minimum value in the tree
  BST::Node* getMinimum() {
    return findMinimum(root);
  }
  // Calculate the total number of nodes recursively
  int calculateTotalNodes(BST::Node* node){
    if (node == NULL)
      return 0;
 
    int left = calculateTotalNodes(node->left);
    int right = calculateTotalNodes(node->right);
 
    return 1 + left + right;
  }
  // Utility method to call main method
  int getTotalNodes() {
    return calculateTotalNodes(root);
  }
  // Create a node with the information provided
  BST::Node* newNode(std::string cityName, int cityPopulation){
      BST::Node* child = new BST::Node;
      child->name = cityName;
      child->data = cityPopulation;
      child->right = NULL;
      child->left = NULL;
      child->parent = NULL;
      return child;
  }
};