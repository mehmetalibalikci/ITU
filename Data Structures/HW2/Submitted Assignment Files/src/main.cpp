/* @Author
Student Name: Mehmet Ali Balıkçı

Student ID : 150200059

Date: 06.06.2023*/

#include <iostream>
#include "../include/AVLTree.h"
#include "../include/BSTree.h"
#include "../include/LinkedList.h"
#include <chrono>

using namespace std;

void print_ds_menu();
void print_operation_menu();

bool perform_operation(char, BSTree* bst_gt, BSTree* bst_prediction);
bool perform_operation(char, AVLTree* avt_gt, AVLTree* avt_prediction);
bool perform_operation(char, LinkedList* ll_gt, LinkedList* ll_prediction);

int main()
{      
    string file_gt = "gt.txt";
    string file_predict = "predict.txt";    
    bool end = false;
    char choice_ds, choice_op;

    print_ds_menu();
    cin >> choice_ds;
    
    if (choice_ds == '1') //Binary Search Tree Selection
    {
        BSTree* bst_gt = new BSTree();          // For ground truth BST data structure
        BSTree* bst_prediction = new BSTree();  // For prediction BST data structure
        
        while (!end)
        {       
            print_operation_menu();
            cin >> choice_op;
            end=perform_operation(choice_op, bst_gt, bst_prediction);
        }    
        delete bst_gt;
        delete bst_prediction;
    }

    else if (choice_ds == '2') //AVL Tree Selection
    {
        AVLTree* avt_gt = new AVLTree();          // For ground truth AVT data structure
        AVLTree* avt_prediction = new AVLTree();  // For prediction AVT data structure

        while (!end)
        {   
            print_operation_menu();
            cin >> choice_op;
            end=perform_operation(choice_op, avt_gt, avt_prediction);
        }
        delete avt_gt;
        delete avt_prediction;
    }

    else if (choice_ds == '3') //Linked List Selection
    {
        LinkedList* ll_gt = new LinkedList();       // For ground truth Linked List data structure
        LinkedList* ll_prediction = new LinkedList();  // For prediction Linked List data structure

        while (!end)
        {   
            print_operation_menu();
            cin >> choice_op;   
            end=perform_operation(choice_op, ll_gt, ll_prediction);
        }
        delete ll_gt;
        delete ll_prediction;
    }

    else
    {
        cout << "Error: You have entered an invalid choice" << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

void print_ds_menu()
{
    cout << "Choose a data structure" << endl;
    cout << "1: Binary Search Tree" << endl;
    cout << "2: AVL Tree"<< endl;
    cout << "3: Unsorted Singly Linked List"<< endl;
    cout << "Enter a choice {1,2,3}:";
}

void print_operation_menu()
{
    cout << "Choose an operation" << endl;
    cout << "1: Create ground truth data structure from file" << endl;
    cout << "2: Create prediction data structure from file"<< endl;
    cout << "3: Add a variant prediction"<< endl;
    cout << "4: Delete a variant prediction"<< endl;
    cout << "5: List predictions"<< endl;
    cout << "6: Search a prediction variant from predictions"<< endl;
    cout << "7: Calculate true positive variant count"<< endl;
    cout << "0: Exit" << endl;
    cout << "Enter a choice {1,2,3,4,5,6,7,0}:";
}
// This function controls the user's choice and performs the operation according to the choice on BSTree data structure
bool perform_operation(char choice_op, BSTree* bst_gt, BSTree* bst_prediction)
{
    string file_gt = "gt.txt";
    string file_predict = "predict.txt";
    int chrom;  
    int pos;
    char alt_base;
    

    switch (choice_op)
    {
    case '1': //Create ground truth data structure from file
        bst_gt->fillUp(file_gt,'g');
        return false;
    case '2': //Create prediction data structure from file
        bst_prediction->fillUp(file_predict,'p');
        return false;
    case '3'://Add a variant prediction
        cout<<"Enter the CHROM POS and ALT BASE information with a space in between: ";                    
        // Controls whether the values entered by user is correct or not
        while (!(cin >> chrom >> pos >> alt_base))
        {
            cout << "Error: Invalid input. Please enter valid integers for CHROM and POS, and a valid character for ALT BASE." << endl;
            cin.clear(); // Clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        }                
        bst_prediction->insert(chrom,pos,alt_base);
        return false;
    case '4'://Delete a variant prediction
        cout<<"Enter the CHROM POS and ALT BASE information with a space in between: ";                    
        // Controls whether the values entered by user is correct or not
        while (!(cin >> chrom >> pos >> alt_base))
        {
            cout << "Error: Invalid input. Please enter valid integers for CHROM and POS, and a valid character for ALT BASE." << endl;
            cin.clear(); // Clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        }                  
        bst_prediction->remove(chrom,pos,alt_base);
        return false;
    case '5'://List predictions
        bst_prediction->inOrderTraversal();
        cout<<endl;
        return false;
    case '6'://Search a prediction variant from predictions
        cout<<"Enter the CHROM POS and ALT BASE information with a space in between: ";                    
        // Controls whether the values entered by user is correct or not
        while (!(cin >> chrom >> pos >> alt_base))
        {
            cout << "Error: Invalid input. Please enter valid integers for CHROM and POS, and a valid character for ALT BASE." << endl;
            cin.clear(); // Clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        }                   
        bst_prediction->search(chrom,pos,alt_base);
        return false;
    case '7'://Calculate true positive variant count
        bst_gt->calculateTruePositiveCount(bst_prediction);
        return false;
    case '0': //Exit
        return true;
    default:
        cout << "Error: You have entered an invalid choice" << endl;
        return false;
    }
}
// This overloading function controls the user's choice and performs the operation according to the choice on AVLTree data structure
bool perform_operation(char choice_op, AVLTree* avt_gt, AVLTree* avt_prediction)
{
    string file_gt = "gt.txt";
    string file_predict = "predict.txt";
    int chrom;  
    int pos;
    char alt_base;

    switch (choice_op)
    {
    case '1'://Create ground truth data structure from file
        avt_gt->fillUp(file_gt,'g');
        return false;
    case '2'://Create prediction data structure from file
        avt_prediction->fillUp(file_predict,'p');
        return false;
    case '3'://Add a variant prediction
        cout<<"Enter the CHROM POS and ALT BASE information with a space in between: ";
        // Controls whether the values entered by user is correct or not
        while (!(cin >> chrom >> pos >> alt_base))
        {
            cout << "Error: Invalid input. Please enter valid integers for CHROM and POS, and a valid character for ALT BASE." << endl;
            cin.clear(); // Clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        }                    
        avt_prediction->insert(chrom,pos,alt_base);
        return false;
    case '4'://Delete a variant prediction
        cout<<"Enter the CHROM POS and ALT BASE information with a space in between: ";
        // Controls whether the values entered by user is correct or not
        while (!(cin >> chrom >> pos >> alt_base))
        {
            cout << "Error: Invalid input. Please enter valid integers for CHROM and POS, and a valid character for ALT BASE." << endl;
            cin.clear(); // Clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        }                    
        avt_prediction->remove(chrom,pos,alt_base);
        return false;
    case '5'://List predictions
        avt_prediction->inOrderTraversal();
        cout<<endl;
        return false;
    case '6'://Search a prediction variant from predictions
        cout<<"Enter the CHROM POS and ALT BASE information with a space in between: ";
        // Controls whether the values entered by user is correct or not
        while (!(cin >> chrom >> pos >> alt_base))
        {
            cout << "Error: Invalid input. Please enter valid integers for CHROM and POS, and a valid character for ALT BASE." << endl;
            cin.clear(); // Clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        }                    
        avt_prediction->search(chrom,pos,alt_base);
        return false;
    case '7'://Calculate true positive variant count
        avt_gt->calculateTruePositiveCount(avt_prediction);
        return false;
    case '0': //Exit
        return true;
    default:
        cout << "Error: You have entered an invalid choice" << endl;
        return false;
    }
}
// This overloading function controls the user's choice and performs the operation according to the choice on LinkedList data structure
bool perform_operation(char choice_op, LinkedList* ll_gt, LinkedList* ll_prediction)
{
    string file_gt = "gt.txt";
    string file_predict = "predict.txt";
    int chrom;  
    int pos;
    char alt_base;

    switch (choice_op)
    {
    case '1': //Create ground truth data structure from file
        ll_gt->fillUp(file_gt,'g');
        return false;
    case '2': //Create prediction data structure from file
        ll_prediction->fillUp(file_predict,'p');
        return false;
    case '3': //Add a variant prediction
        cout<<"Enter the CHROM POS and ALT BASE information with a space in between: ";
        // Controls whether the values entered by user is correct or not
        while (!(cin >> chrom >> pos >> alt_base))
        {
            cout << "Error: Invalid input. Please enter valid integers for CHROM and POS, and a valid character for ALT BASE." << endl;
            cin.clear(); // Clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        }                    
        ll_prediction->insert(chrom,pos,alt_base);
        return false;
    case '4': //Delete a variant prediction
        cout<<"Enter the CHROM POS and ALT BASE information with a space in between: ";
        // Controls whether the values entered by user is correct or not
        while (!(cin >> chrom >> pos >> alt_base))
        {
            cout << "Error: Invalid input. Please enter valid integers for CHROM and POS, and a valid character for ALT BASE." << endl;
            cin.clear(); // Clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        }                    
        ll_prediction->remove(chrom,pos,alt_base);
        return false;
    case '5': //List predictions
        ll_prediction->traverse();
        cout<<endl;
        return false;
    case '6': //Search a prediction variant from predictions
        cout<<"Enter the CHROM POS and ALT BASE information with a space in between: ";
        // Controls whether the values entered by user is correct or not
        while (!(cin >> chrom >> pos >> alt_base))
        {
            cout << "Error: Invalid input. Please enter valid integers for CHROM and POS, and a valid character for ALT BASE." << endl;
            cin.clear(); // Clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        }                    
        ll_prediction->search(chrom,pos,alt_base);
        return false;
    case '7':   //Calculate true positive variant count
        ll_gt->calculateTruePositiveCount(ll_prediction);
        return false;
    case '0': //Exit
        return true;
    default:
        cout << "Error: You have entered an invalid choice" << endl;
        return false;
    }
}