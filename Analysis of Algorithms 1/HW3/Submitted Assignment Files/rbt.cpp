// EB
// Implementing Red-Black Tree in C++

#include <iostream>
#include <string>
namespace RBT {
  struct Node {
    int data;
    std::string name;
    Node *parent;
    Node *left;
    Node *right;
    int color;
  };
}

class RedBlackTree {
private:
  RBT::Node* root;
  RBT::Node* TNULL;
public:
  RedBlackTree() {
    TNULL = new RBT::Node;
    TNULL->color = 0;
    TNULL->left = NULL;
    TNULL->right = NULL;
    root = TNULL;
  }
  // Utility function to call the main preorder method
  void preorder(std::pair<std::string, int>* array, int index) {
    preorderSorting(root, array, index);
  }
  // To make preorder algorithm recursive way
  void preorderSorting(RBT::Node* root, std::pair<std::string, int>* array, int& index) {
    if (root != TNULL) {
      array[index++] = std::make_pair(root->name, root->data);
      preorderSorting(root->left, array, index);
      preorderSorting(root->right, array, index);
    }
  }
  // Utility function to call the main inorder method
  void inorder(std::pair<std::string, int>* array, int index) {
    inorderSorting(root, array, index); 
  }
  // To make inorder algorithm recursive way
  void inorderSorting(RBT::Node* root, std::pair<std::string, int>* array, int& index) {
    if (root != TNULL) {
      inorderSorting(root->left, array, index);
      array[index++] = std::make_pair(root->name, root->data);      
      inorderSorting(root->right, array, index);
    }
  }
  // Utility function to call the main postorder method 
  void postorder(std::pair<std::string, int>* array, int index) {   
    postOrderSorting(root, array, index); // Call the main method
  }
  // To make postorder algorithm recursive way
  void postOrderSorting(RBT::Node* root, std::pair<std::string, int>* array, int& index){
    if(root != TNULL){
      postOrderSorting(root->left, array, index); // Traverse left 
      postOrderSorting(root->right, array, index); // Traverse right 
      array[index++] = std::make_pair(root->name, root->data); // Add city information to array
    }
  }
  // Search a value
  RBT::Node* searchTree(int cityPopulation) {
    RBT::Node* temp = root;
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
  RBT::Node* successor(RBT::Node* keyNode) {
    // Find the minimum value of subtree of the keynode
    if (keyNode->right != TNULL)
        return findMinimum(keyNode->right);

    // Scan the parent nodes
    RBT::Node* parentNode = keyNode->parent;
    while (parentNode != TNULL && keyNode == parentNode->right) {
        keyNode = parentNode;
        parentNode = parentNode->parent;
    }
    return parentNode;
  }
  // Find the successor node of keynode
  RBT::Node* predecessor(RBT::Node* keyNode) {
    // Find the maksimum value of subtree of the keynode
    if (keyNode->left != TNULL)
        return findMaksimum(keyNode->left);

    // Scan the parent nodes
    RBT::Node* parentNode = keyNode->parent;
    while (parentNode != TNULL && keyNode == parentNode->left) {
        keyNode = parentNode;
        parentNode = parentNode->parent;
    }
    return parentNode;
  }
  // Inserting a node
  void insert(std::string cityName, int cityPopulation) {
    RBT::Node* child = newNode(cityName, cityPopulation);
    RBT::Node* y = NULL;
    RBT::Node* x = this->root;

    while (x != TNULL) {
      y = x;
      if (child->data < x->data) {
        x = x->left;
      } else {
        x = x->right;
      }
    }

    child->parent = y;
    if (y == nullptr) {
      root = child;
    } else if (child->data < y->data) {
      y->left = child;
    } else {
      y->right = child;
    }

    if (child->parent == nullptr) {
      child->color = 0;
      return;
    }

    if (child->parent->parent == nullptr) {
      return;
    }

    insertFix(child);
  }
  // For balancing the tree after insertion
  void insertFix(RBT::Node* k) {
    RBT::Node* u;
    while (k->parent->color == 1) {
      if (k->parent == k->parent->parent->right) {
        u = k->parent->parent->left;
        if (u->color == 1) {
          u->color = 0;
          k->parent->color = 0;
          k->parent->parent->color = 1;
          k = k->parent->parent;
        } else {
          if (k == k->parent->left) {
            k = k->parent;
            rightRotate(k);
          }
          k->parent->color = 0;
          k->parent->parent->color = 1;
          leftRotate(k->parent->parent);
        }
      } else {
        u = k->parent->parent->right;

        if (u->color == 1) {
          u->color = 0;
          k->parent->color = 0;
          k->parent->parent->color = 1;
          k = k->parent->parent;
        } else {
          if (k == k->parent->right) {
            k = k->parent;
            leftRotate(k);
          }
          k->parent->color = 0;
          k->parent->parent->color = 1;
          rightRotate(k->parent->parent);
        }
      }
      if (k == root) {
        break;
      }
    }
    root->color = 0;
  }
  // Utility function to delete a node from the tree 
  void deleteNode(int cityPopulation) {
    deleteNodeFromTree(this->root, cityPopulation);
  }
  // Delete a node from the tree
  void deleteNodeFromTree(RBT::Node* node, int cityPopulation) {
    RBT::Node* z;
    RBT::Node* x;
    RBT::Node* y;
    z = TNULL;
    while (node != TNULL) {
      if (node->data == cityPopulation) {
        z = node;
      }

      if (node->data <= cityPopulation) {
        node = node->right;
      } else {
        node = node->left;
      }
    }

    if (z == TNULL) {
      std::cout << "Key not found in the tree" << std::endl;
      return;
    }

    y = z;
    int y_original_color = y->color;
    if (z->left == TNULL) {
      x = z->right;
      rbTransplant(z, z->right);
    } else if (z->right == TNULL) {
      x = z->left;
      rbTransplant(z, z->left);
    } else {
      y = findMinimum(z->right);
      y_original_color = y->color;
      x = y->right;
      if (y->parent == z) {
        x->parent = y;
      } else {
        rbTransplant(y, y->right);
        y->right = z->right;
        y->right->parent = y;
      }

      rbTransplant(z, y);
      y->left = z->left;
      y->left->parent = y;
      y->color = z->color;
    }
    delete z;
    if (y_original_color == 0) {
      deleteFix(x);
    }
  }
  // For balancing the tree after deletion
  void deleteFix(RBT::Node* x) {
    RBT::Node* s;
    while (x != root && x->color == 0) {
      if (x == x->parent->left) {
        s = x->parent->right;
        if (s->color == 1) {
          s->color = 0;
          x->parent->color = 1;
          leftRotate(x->parent);
          s = x->parent->right;
        }

        if (s->left->color == 0 && s->right->color == 0) {
          s->color = 1;
          x = x->parent;
        } else {
          if (s->right->color == 0) {
            s->left->color = 0;
            s->color = 1;
            rightRotate(s);
            s = x->parent->right;
          }

          s->color = x->parent->color;
          x->parent->color = 0;
          s->right->color = 0;
          leftRotate(x->parent);
          x = root;
        }
      } else {
        s = x->parent->left;
        if (s->color == 1) {
          s->color = 0;
          x->parent->color = 1;
          rightRotate(x->parent);
          s = x->parent->left;
        }

        if (s->right->color == 0 && s->right->color == 0) {
          s->color = 1;
          x = x->parent;
        } else {
          if (s->left->color == 0) {
            s->right->color = 0;
            s->color = 1;
            leftRotate(s);
            s = x->parent->left;
          }

          s->color = x->parent->color;
          x->parent->color = 0;
          s->left->color = 0;
          rightRotate(x->parent);
          x = root;
        }
      }
    }
    x->color = 0;
  }
  // Function to replace two nodes with each others
  void rbTransplant(RBT::Node* u, RBT::Node* v) {
    if (u->parent == nullptr) {
      root = v;
    } else if (u == u->parent->left) {
      u->parent->left = v;
    } else {
      u->parent->right = v;
    }
    v->parent = u->parent;
  }
  // Calculate the height of the tree recursively
  int calculateHeight(RBT::Node* node){  
    if (node == NULL || node == TNULL)
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
  RBT::Node* findMaksimum(RBT::Node* node){
    RBT::Node* temp = node;
    
    // Go right subtree to find maximum value
    while(temp->right != TNULL){
      temp = temp->right;
    }
    return temp; 
  }
  // Find the node having maximum value in the tree
  RBT::Node* getMaximum() {
    return findMaksimum(root);
  }
  // Find the node having minimum value to use in other methods
  RBT::Node* findMinimum(RBT::Node* node){
    RBT::Node* temp = node;
    // Go right subtree to find maximum value
    while(temp->left != TNULL){
      temp = temp->left;
    }
    return temp;  
  }
  // Find the node having minimum value in the tree
  RBT::Node* getMinimum() {
    return findMinimum(root);
  }
  // Calculate the total number of nodes recursively
  int calculateTotalNodes(RBT::Node* node){
    if (node == NULL || node == TNULL)
      return 0;
 
    int left = calculateTotalNodes(node->left);
    int right = calculateTotalNodes(node->right);
 
    return 1 + left + right;
  }
  // Utility method to call main method
  int getTotalNodes() {
    return calculateTotalNodes(root);
  }
  // Left rotation
  void leftRotate(RBT::Node* child) {
    RBT::Node* grandChild = child->right;
    child->right = grandChild->left;
    if (grandChild->left != TNULL) {
      grandChild->left->parent = child;
    }
    grandChild->parent = child->parent;
    if (child->parent == nullptr) {
      this->root = grandChild;
    } else if (child == child->parent->left) {
      child->parent->left = grandChild;
    } else {
      child->parent->right = grandChild;
    }
    grandChild->left = child;
    child->parent = grandChild;
  }
  // Right rotation
  void rightRotate(RBT::Node* child) {
    RBT::Node* grandChild = child->left;
    child->left = grandChild->right;
    if (grandChild->right != TNULL) {
      grandChild->right->parent = child;
    }
    grandChild->parent = child->parent;
    if (child->parent == nullptr) {
      this->root = grandChild;
    } else if (child == child->parent->right) {
      child->parent->right = grandChild;
    } else {
      child->parent->left = grandChild;
    }
    grandChild->right = child;
    child->parent = grandChild;
  }
  // Utility function to print the tree
  void printTree() {
    if (root) {
      printHelper(this->root, "", true);
    }
  }
  // Print the tree
  void printHelper(RBT::Node* root, std::string indent, bool last) {
    if (root != TNULL) {
      std::cout << indent;
      if (last) {
        std::cout << "R----";
        indent += "   ";
      } else {
        std::cout << "L----";
        indent += "|  ";
      }

      std::string sColor = root->color ? "RED" : "BLACK";
      std::cout << root->data << "(" << sColor << ")" << std::endl;
      printHelper(root->left, indent, false);
      printHelper(root->right, indent, true);
    }
  }
  // Create a new node
  RBT::Node* newNode(std::string cityName, int cityPopulation){
      RBT::Node* child = new RBT::Node;
      child->parent = NULL;
      child->name = cityName;
      child->data = cityPopulation;
      child->left = TNULL;
      child->right = TNULL;
      child->color = 1;
      return child;
  }
};  