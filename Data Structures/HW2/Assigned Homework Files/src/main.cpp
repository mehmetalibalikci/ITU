#include <iostream>
#include <vector>

using namespace std;

void print_ds_menu();
void print_operation_menu();
bool perform_operation(char);


int main()
{
    string file_gt = "../gt.txt";
    string file_predict = "../predict.txt";
    bool end = false;
    char choice_ds, choice_op;
    
    print_ds_menu();
    cin >> choice_ds;

    if (choice_ds == '1') //Binary Search Tree Selection
    {
        //BinSTree* bst = new BinSTree();

        while (!end)
        {
            print_operation_menu();
            cin >> choice_op;
            // Fill here according to the choice
        }
    }

    else if (choice_ds == '2') //AVL Tree Selection
    {
        //AVLTree* avt = new AVLTree();

        while (!end)
        {
            print_operation_menu();
            cin >> choice_op;
            // Fill here according to the choice
        }
    }

    else if (choice_ds == '3') //Linked List Selection
    {
        //LinkedList* ll = new LinkedList();

        while (!end)
        {
            print_operation_menu();
            cin >> choice_op;
            // Fill here according to the choice
        }
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


