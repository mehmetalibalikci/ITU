/*
Student Name: Mehmet Ali Balıkçı
Student ID: 150200059

*/

#include <iostream>
#include <string>
#include "MultiList.h"
#include <fstream>
#include <chrono>

using namespace std::chrono;
using namespace std;

MultiList::MultiList()
{
    head = NULL;
    tail = NULL;
}

void MultiList::add_uni_node(Department *depPTR, string faculty, string uni, string discount, string city, string language, string score_last, string range_last, string score_first, string range_first, string range_average, string score_average){
    // we don't add a new department node if it exists from the same department name
    // we just add a new university node to the existing department node.
    
    University* newUni = new University(faculty,uni,discount,city,language,score_last,range_last,score_first,range_first,range_average,score_average);
    newUni->set_up(NULL);

    
    if(newUni->get_uni() < depPTR->getunder()->get_uni()){// if the new university name precedes the name of the university in the department node                                        
        newUni->set_up(depPTR->getunder());
        depPTR->set_up(newUni);
        depPTR->increase();
    }

    else{
        University* tempUni = depPTR->getunder();
        while(tempUni->getNext() != nullptr && tempUni->getNext()->get_uni() < newUni->get_uni()){
            tempUni = tempUni->getNext();
        }
        newUni->set_up(tempUni->getNext());
        tempUni->set_up(newUni);
        depPTR->increase();
    }
}
void MultiList::add_dep_uni_node(Department *preve, string department, string faculty, string uni, string discount, string city, string language, string score_last, string range_last, string score_first, string range_first, string range_average, string score_average){
    // If the department is not created before, we create this deparment and add the first university node.
    University* newUni = new University(faculty,uni,discount,city,language,score_last,range_last,score_first,range_first,range_average,score_average);
    newUni->set_up(NULL);
    preve->set_up(newUni);
    preve->increase();

}
void MultiList::add_node(string department, string faculty, string uni, string discount, string city, string language, string score_last, string range_last, string score_first, string range_first, string range_average, string score_average){
    
    int control = 0;
    Department* newDep = new Department(department);
    newDep->set_next(NULL);
    newDep->set_prev(NULL);
    newDep->set_up(NULL);

    if(head == nullptr){  // If there is no department node, we create it
        head = newDep;
        tail = newDep;
        add_dep_uni_node(newDep,department,faculty,uni,discount,city,language,score_last,range_last,score_first,range_first,range_average,score_average);
    }
    else{
        // We do not create a department from the department name that comes as an argument, if it already exists.

        if(!control){ 
            Department* tempDep = head;
            while(!control){  
                if(newDep->get_Department() == tempDep->get_Department()){
                    add_uni_node(tempDep,faculty,uni,discount,city,language,score_last,range_last,score_first,range_first,range_average,score_average);
                    control++;
                    break;
                }
                if( tempDep->getNext()==NULL && newDep->get_Department() != tempDep->get_Department() ){
                    break;
                }
                tempDep = tempDep->getNext();
            }
        }
        // If the department name that comes as an argument is not in the list and comes before the first department name alphabetically, 
        // we add it to the beginning.

        if(newDep->get_Department() < head->get_Department() && !control){
            newDep->set_next(head);                                            
            head->set_prev(newDep);
            head = newDep;
            add_dep_uni_node(newDep,department,faculty,uni,discount,city,language,score_last,range_last,score_first,range_first,range_average,score_average);
            control++; 
        }
        // If the department name that comes as an argument is not among the department nodes 
        // and comes after the first department name alphabetically

        else if(!control){ //  
            Department* tempDep = head;
            
            //Searching for suitable location to add and new node is added the list.
            
            while (tempDep->getNext() != nullptr && tempDep->getNext()->get_Department() < newDep->get_Department()) {
                tempDep = tempDep->getNext();
            }   
            newDep->set_next(tempDep->getNext());
            if(tempDep->getNext() != NULL){
                tempDep->getNext()->set_prev(newDep);
            } 
            tempDep->set_next(newDep);
            newDep->set_prev(tempDep);
            
            //If the new node will come last, the new tail will be this node.
            
            if(newDep->getNext() == NULL) tail = newDep;
            add_dep_uni_node(newDep,department,faculty,uni,discount,city,language,score_last,range_last,score_first,range_first,range_average,score_average);
        }
    }    

}   
void MultiList::listDepartments(){
    unsigned int kNumberOfDepartments=0;

    auto start = high_resolution_clock::now();

    Department* tempDep = head;
    
    while(tempDep != NULL){
        cout<<"Department: "<<tempDep->get_Department()<<endl;
        cout<<"Number of Universities of Department: "<<tempDep->get_numOfUni()<<endl;
        cout<<"-----------------"<<endl;
        tempDep = tempDep-> getNext();
        kNumberOfDepartments++;
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "\nTime taken by listing all departments operation: "<< duration.count() << " milliseconds\n" << endl;
    cout <<"The total number of departments: "<<kNumberOfDepartments<<endl;

}
void MultiList::select_department(){
    unsigned int kNumberOfDepartments=0;

    auto start = high_resolution_clock::now();

    int option;
    Department* tempDep = head;

    while(tempDep != NULL){
        tempDep = tempDep-> getNext();
        kNumberOfDepartments++;
    }

    cout<<"To review a department, enter a number between 0 and the department number: ";
    cin>>option;

    while(option > kNumberOfDepartments || option<=0){
        cout<<"ERROR: You have entered an invalid number"<<endl<<endl;
        cout<<"To review a department, enter a number between 0 and the department number: ";
        cin>>option;
    } 

    tempDep = head;
    
    for(int i=1;i<option;i++){
        tempDep = tempDep-> getNext();
    }
    University* tempUni = tempDep->getunder();


    cout<<"Department: "<<tempDep->get_Department()<<endl;

    for(int i=1;;i++){
        cout<<""<<i<<": ";
        cout<<tempUni->get_uni()<<endl;
        tempUni->printDetails();
        tempUni = tempUni->getNext();
        if(tempUni == NULL) break;
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "\nTime taken by Listing All Universities operation: "<< duration.count() << " milliseconds\n" << endl;
}
void MultiList::select_uni(){
    unsigned int kNumberOfDepartments=0;

    auto start = high_resolution_clock::now();

    int option;
    int number_of_universities=0;
    Department* tempDep = head;
    
    while(tempDep != NULL){
        tempDep = tempDep-> getNext();
        kNumberOfDepartments++;
    }

    cout<<"To review a department, enter a number between 0 and the department number: ";
    cin>>option;

    while(option > kNumberOfDepartments || option<=0){
        cout<<"ERROR: You have entered an invalid number"<<endl<<endl;
        cout<<"To review a department, enter a number between 0 and the department number: ";
        cin>>option;
    } 

    tempDep = head;

    for(int i=1;i<option;i++){
        tempDep = tempDep->getNext();
    }
    
    cout<<"Department: "<<tempDep->get_Department()<<endl;
    cout<<"\n";

    University* tempUni = tempDep->getunder();
    
    while(tempUni != NULL){
        tempUni = tempUni-> getNext();
        number_of_universities++;
    }
    cout<<"The total number of Universities: "<<number_of_universities<<endl;

    
    cout<<"To review a university of selected department, enter a number between 0 and the university number: ";
    cin>>option;

    while(option > number_of_universities || option<=0){
        cout<<"ERROR: You have entered an invalid number"<<endl<<endl;
        cout<<"To review a university of selected department, enter a number between 0 and the university number: ";
        cin>>option;
    }

    tempUni = tempDep->getunder();

    for(int i=1;i<option;i++){
       tempUni = tempUni->getNext();
    }

    cout<<tempUni->get_uni()<<endl;
    tempUni->printDetails();
    
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "\nTime taken by selecting a department and university operation: "<< duration.count() << " milliseconds\n" << endl;
}

MultiList::~MultiList(){
    auto start = high_resolution_clock::now();
   
    Department* tempDep = head;
    University* tempUni = head->getunder();
    University* delUni = tempUni;

    while(tempUni != NULL){
        delUni = tempUni;
        tempUni = tempUni->getNext();
        delete delUni;
        
    }
    while(head != NULL){
        tempDep = head;
        head = head->getNext();
        delete tempDep;
    }
    head = nullptr;
    tail = nullptr;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    
    if(head == nullptr and tail == nullptr){
        cout<<"Multilist was succesfully deleted"<<endl;
    }

    cout << "\nTime taken by de-allocation operation: "<< duration.count() << " microseconds\n" << endl;
}
