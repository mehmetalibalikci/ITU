#include<iostream>
#include<cstdlib>
#include<ctime>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <math.h>
#include <float.h>

using namespace std;

// The code is designated as the index of the first node of the tree will be 0. 
// But, the user enters the data like in a heap, that is, the index of the first node will be 1.
// The code handles with this index setting.

// Find the index of parent node
int find_parent(int i, int no_child = 2){
    // This code works with the trees having different numbers of child's
    // no_child variable represents the number of childs
    if(i%no_child==0) 
        return (i/no_child) - 1;
    return i/no_child;
}
// Exchance two element of the heap
void exchange(std::vector<std::pair<std::string, int>>& data, int i, int j){
    string  string_temp;
    int int_temp;
    string_temp = data[i].first;
    int_temp =data[i].second;
    data[i].first = data[j].first;
    data[i].second= data[j].second;  
    data[j].first = string_temp;
    data[j].second = int_temp;

}
// Write the output to a file
void print_heap_to_file(const std::vector<std::pair<std::string, int>>& data, const std::string& file_name) {
    std::ofstream outputFile(file_name);

    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open the file " << file_name << std::endl;
        return;
    }

    for (const auto& element : data) {
        outputFile << element.first << ";" << element.second << std::endl;
    }

    outputFile << std::endl;
    outputFile.close();
}
// Provide the Max Heap property
void max_heapify(std::vector<std::pair<std::string, int>>& data, int i, int& heap_size, int no_child = 2){
    i--; // Given index decreased by one because the index of the first node is zero

    // No_child variable is added to use this function with both of d-ary heap and the heap constructed with complete binary
    int index_of_child[no_child]; //Create an array to keep indexes of a node
    int counter = 1;    // Counter increases by one for each of d children

        for(int j=0; j<no_child; j++){    // Iterates as many times as the value of no_child, that is, a constant
            index_of_child[j] = (no_child*i) + counter;  //Calculates the indexes of the children of ith node
            counter++;
        }
        int largest = i;

        for(int j=0; j<no_child; j++){    // Iterates as many times as the value of no_child, that is, a constant
            
            // Compare whether the value of child is smaller than that of parent node or not
            if(index_of_child[j] < heap_size && data[index_of_child[j]].second > data[largest].second) 
            largest = index_of_child[j]; // if so, change the value of largest with the index of child node
        }
        if(largest != i){
            exchange(data, i, largest); // Exchange parent node with child node
            largest++;  // Because the i will be decreased at the begin of this function
            max_heapify(data, largest, heap_size, no_child); // Repeat the same operations
        }
}
// Provide the array sorted in decreasing order using Max Heapify
void build_max_heap(std::vector<std::pair<std::string, int>>& data, int no_child = 2){
    // No_child varia is added to use this function with both of d-ary heap and the heap constructed with complete binary
    int heap_size = data.size();
    int start_point; // Represents from which number i starts
    // if heap_size is (n * no_child) + 1 then start point must be n/no_child
    // But if heap_size is (n * no_child) + (2,3,..n-1) then start point must be n/no child + 1
    if(heap_size % no_child == 1){
        start_point = (heap_size - 1) / no_child;
    }
    else if(heap_size % no_child == 0){
        start_point = (heap_size) / no_child;  
    }
    else{
        start_point = (heap_size / no_child) + 1;
    }
    for(int i=start_point; i>0; i--){  
            max_heapify(data, i, heap_size, no_child);
    }
}
// Provide the array sorted in increasing order
void heapsort(std::vector<std::pair<std::string, int>>& data){
    build_max_heap(data);    // Obtain a MAX-Heap
    int heap_size = data.size()-1; 
    for(int i=heap_size; i>=1; i--){ // i starts as size - 1 because the index of the first node is zero,
        exchange(data, i, 0);        // so the index of the last node will be size - 1
        max_heapify(data, 1, heap_size);
        heap_size --;
    }
}
// Increase a value of desired node
void heap_increase_key(std::vector<std::pair<std::string, int>>& data, int i, int value){
    /*
        Example of Heap Increase Key:

        Max-Heap: 30, 20, 25, 10, 15
        Increase 3, 40
        that is do 25 -> 40
        step 1 Max Heap: 30, 20, 40, 10, 15
        Final Max Heap: 40, 20, 30, 10 ,15
    */
    if(i > data.size()){
        cerr<< "Index number cannot be greater than the size of the heap"<<endl;
    }
    else{
        i--;   // Given index decreased by one because the index of the first node is zero
        if(value < data[i].second){
            cerr<< "new key is smaller than current key" <<endl;
            return;
        }
        
        data[i].second = value;
        while(i>0 && data[find_parent(i)].second < data[i].second){ //Exchange the child with the parent until the parent will greater than the child
            exchange(data, i, find_parent(i)); // Exchange parent with child
            i = find_parent(i);
        }
    }
}
// Insert a new node to the heap
void max_heap_insert(std::vector<std::pair<std::string, int>>& data, string key, int value){    
    /*
        Example of Heap Insert:

        Max-Heap: 30, 20, 25, 10, 15
        insert 35
        new Max-Heap: 35, 20, 30, 10, 15, 25
    */
    data.push_back(std::make_pair(key,value));
    int last_element = data.size()-1; // Because the index of the first element is zero, so the index of the last element is size -1 
    double neg_infinite = -1 * DBL_MAX; 
    data[last_element].second = neg_infinite;
    heap_increase_key(data, last_element + 1, value);
}
// Return the maximum element with the largest value
int heap_maximum(const std::vector<std::pair<std::string, int>> data){
    /*
        Example of Heap Maximum:

        Max-Heap: 30, 20, 25, 10, 15
        return 30
    */
    return data[0].second;
}
// Return and remove element with the largest value
int heap_extract_max(std::vector<std::pair<std::string, int>>& data){
    /*
        Example of Heap Extract Max:

        Max-Heap: 30, 20, 25, 10, 15
        -- Heap Extract Max Function
        step 1 Max Heap: 15, 20, 25, 10
        step 2 and final Max Heap: 25, 20, 15, 10
    */
    
    int heap_size = data.size();
    if(data.size() < 1){
        cerr<<"heap underflow"<<endl;
    }
    int max = data[0].second;
    exchange(data, 0, data.size()-1);  // Exchange the last node with the first node
    data.pop_back();    // Extract max node
    heap_size--;
    max_heapify(data, 1, heap_size);
    return max;
}
// Calculate the height 
int dary_calculate_height(int no_element, int degree){
    int height;
    height = (log((no_element * degree) - no_element + 1) / log(degree) ); // Implement a formula to find the height of the d-ary tree
    return height;
}
// Increase a value of desired node
void dary_increase_key(std::vector<std::pair<std::string, int>>& data, int i, int value, int no_child){
    if(i > data.size()){
        cerr<< "Index number cannot be greater than the size of the heap"<<endl;
    }
    else {
        i--;  // Given index decreased by one because the index of the first node is zero
        if(value < data[i].second){
            cerr<< "new key is smaller than current key" <<endl;
            return;
        }
        data[i].second = value;
        
        while(i>0 && data[find_parent(i, no_child)].second < data[i].second){ //Exchange the child with the parent until the parent will greater than the child
            exchange(data, i, find_parent(i, no_child)); // Exchange parent with child
            i = find_parent(i, no_child);
        }
    }

}
// Return and remove element with the largest value
int dary_extract_max(std::vector<std::pair<std::string, int>>& data, int no_child){
    int heap_size = data.size();
    if(data.size() < 1){
        cerr<<"heap underflow"<<endl;
    }
    int max = data[0].second;
    exchange(data, 0, data.size()-1); // Exchange the last node with the first node
    data.pop_back();  // Extract max node
    heap_size--;
    max_heapify(data, 1, heap_size, no_child);
    return max;
}
// Insert a new node to the d-ary heap
void dary_insert_element(std::vector<std::pair<std::string, int>>& data, string key, int value, int no_child){
    data.push_back(std::make_pair(key,value));
    int index_of_last_element = data.size()-1;
    double neg_infinite = -1 * DBL_MAX; 
    data[index_of_last_element].second = neg_infinite;
    dary_increase_key(data, index_of_last_element + 1, value, no_child);
}
// Provide the array sorted in increasing order
void dary_heapsort(std::vector<std::pair<std::string, int>>& data, int no_child){
    build_max_heap(data, no_child);    // Obtain a MAX-Heap
    int heap_size = data.size()-1; 
    for(int i=heap_size; i>=1; i--){ // i starts as size - 1 because the index of the first node is zero,
        exchange(data, i, 0);        // so the index of the last node will be size - 1
        max_heapify(data, 1, heap_size, no_child);
        heap_size --;
    }
}
// Read the data from file
std::vector<std::pair<std::string, int>> read_csv(const std::string& file_name){
    std::vector<std::pair<std::string, int>> data;
    std::ifstream file(file_name);
    
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << file_name << std::endl;
        return data;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string city_name;
        int city_population;
        if (std::getline(iss, city_name, ';') && iss >> city_population) {
            data.push_back(std::make_pair(city_name, city_population));
        }
    }

    file.close();
    return data;
}

int main(int argc, char** argv){
    // IMPORTANT
    // In insert operations, enter the city name as the first argument

    std::string input_file = argv[1];
    std::string function_name = argv[2];
    std::string output_file = argv[3];
    std::vector<std::pair<std::string, int>> data = read_csv(input_file);
    int heap_size = data.size();
    
    if(function_name == "max_heapify"){
        if(argv[4] == NULL){
            cerr<<"MISSING ARGUMENT!"<<endl;
            return 0;
        }
        //Takes the argument
        std::string index = argv[4];
        
        // Create two strings to separate letter and number
        std::string prefix;
        std::string numberPart;

        // Separate letter and number
        for (char c : index) {
            if (std::isdigit(c)) {
                numberPart += c;
            } else {
                prefix += c;
            }
        }
        if(prefix == "i"){ 
            // Convert the number to int
            std::istringstream iss(numberPart);
            int i;
            iss >> i;

            // Call the function
            max_heapify(data, i, heap_size);

            // Write the output to out.csv file
            print_heap_to_file(data, output_file);
        }
        else{
            cout<<"Wrong prefix!"<<endl;
        }

    }
    else if(function_name == "build_max_heap"){
        // Call the function
        build_max_heap(data, 3);
        // Write the output to out.csv file
        print_heap_to_file(data, output_file);
    }
    else if(function_name == "heapsort"){
        clock_t begin = clock(); // Start timer
        // Call the function
        heapsort(data);
        clock_t end = clock(); // End timer
        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC; // Calculate elapsed time
        cout<<"Time is: "<<elapsed_secs<<" ns."<<endl;
        // Write the output to out.csv file
        print_heap_to_file(data, output_file);        
    }
    else if(function_name == "heap_increase_key"){
        if(argv[4] == NULL || argv[5] == NULL){
            cerr<<"MISSING ARGUMENT!"<<endl;
            return 0;
        }
        //Takes the arguments
        std::string string_1 = argv[4];
        std::string string_2 = argv[5];
        // Create two strings to separate letter and number
        std::string prefix;
        std::string numberPart;            
        
        // Separate letter and number
        for (char c : string_1) {
            if (std::isdigit(c)) {
                numberPart += c;
            } else {
                prefix += c;
            }
        }
        
        if(prefix == "i"){
            // Convert the number to int
            std::istringstream iss(numberPart);
            int i;
            iss >> i;
            
            // Reset the argument keeper
            prefix = "";
            numberPart = "";
            // Separate letter and number
            for (char c : string_2) {
                if (std::isdigit(c)) {
                    numberPart += c;
                } else {
                    prefix += c;
                }
            }
            if(prefix == "k"){
                // Convert the number to int
                std::istringstream iss(numberPart);
                int k;
                iss >> k;
                
                //First build a Max-Heap
                build_max_heap(data); 
                // Call the function
                heap_increase_key(data, i, k);
                // Write the output to out.csv file
                print_heap_to_file(data, argv[3]);
            }
            else{
                cout<<"Wrong prefix!"<<endl;
            }
            

        }
        else if(prefix == "k"){
            // Convert the number to int
            std::istringstream iss(numberPart);
            int k;
            iss >> k;
            
            // Reset the argument keeper
            prefix = "";
            numberPart = "";

            // Separate letter and number
            for (char c : string_2) {
                if (std::isdigit(c)) {
                    numberPart += c;
                } else {
                    prefix += c;
                }
            }
            if(prefix == "i"){
                // Convert the number to int
                std::istringstream iss(numberPart);
                int i;
                iss >> i;

                //First build a Max-Heap
                build_max_heap(data);
                // Call the function
                heap_increase_key(data, i, k);
                // Write the output to out.csv fil
                print_heap_to_file(data, argv[3]);
            }
            else{
                cout<<"Wrong prefix!"<<endl;
            }
                            
        }
        else{
                cout<<"Wrong prefix!"<<endl;
            }
    }
    else if(function_name == "max_heap_insert"){
        if(argv[4] == NULL){
            cerr<<"MISSING ARGUMENT!"<<endl;
            return 0;
        }        
        // Key value that is the name of the city must be entered in 4th order
        std::string astring = argv[4];

        // Create two strings to separate letter and number
        std::string prefix;
        std::string numberPart;
        
        // Separate letter and number
        for (char c : astring) {
            if(c == '_')         // Takes only number and letters
                continue;
            if (std::isdigit(c)) {
                numberPart += c;
            } else {
                prefix += c;
            }
        }
        if(prefix[0] == 'k'){
            // Convert the number to int
            std::istringstream iss(numberPart);
            int k;
            iss >> k;
            
            string city_name = prefix.substr(1);

            // Run insert function and write the output to file
            std::ofstream outputFile(output_file);
            if (!outputFile.is_open()) {
                std::cerr << "Error: Unable to open the file " << output_file << std::endl;
            }
            else{
                build_max_heap(data); // First, create a Max-Heap

                // Write the all heap to file
                for (const auto& element : data) {
                    outputFile << element.first << ";" << element.second << std::endl;
                }
                outputFile<<endl;
                    
                max_heap_insert(data, city_name, k); // Insert the new node
                outputFile<<city_name<<" "<<k<<" is added."<<endl; // Inserting message
                outputFile << std::endl;
                // Write output to file
                for (const auto& element : data) { // New heap is writed to file
                    outputFile << element.first << ";" << element.second << std::endl;
                }
                outputFile << std::endl;
                outputFile.close();
            } 
        }
        else{
            cout<<"Wrong prefix!"<<endl;
        }
    }
    else if(function_name == "heap_maximum"){
        build_max_heap(data); // Create a max heap from the data  
        
        // Write the output to file
        std::ofstream outputFile(output_file);

        if (!outputFile.is_open()) {
            std::cerr << "Error: Unable to open the file " << output_file << std::endl;
        }
        else{
            // Run the function
            outputFile <<heap_maximum(data)<< std::endl;
            
            outputFile << std::endl;
            outputFile.close();
        }    
    }
    else if(function_name == "heap_extract_max"){
        build_max_heap(data); // Create a Max-Heap

        // Write output to file
        std::ofstream outputFile(output_file);
        if (!outputFile.is_open()) {
            std::cerr << "Error: Unable to open the file " << output_file << std::endl;
        }
        else{
            // First, write the first version of the heap
            for (const auto& element : data) {
                outputFile << element.first << ";" << element.second << std::endl;
            }
            outputFile<<endl;
            outputFile <<"Max element is: "<<heap_extract_max(data)<< std::endl; // Run the extract function
            outputFile<<endl;

            // Write the Max-Heap whose max element is removed
            for (const auto& element : data) {
                outputFile << element.first << ";" << element.second << std::endl;
            }
            outputFile << std::endl;
            outputFile.close();
        }

    }
    else if(function_name == "dary_calculate_height"){
        if(argv[4] == NULL){
            cerr<<"MISSING ARGUMENT!"<<endl;
            return 0;
        }        
        std::string astring = argv[4];
        // Create two strings to separate letter and number
        std::string prefix;
        std::string numberPart;            
            
        // Separate letter and number
        for (char c : astring) {
            if (std::isdigit(c)) {
                numberPart += c;
            } else {
                prefix += c;
            }
        }
        if(prefix == "d"){
            
            // Convert the number to int
            std::istringstream iss(numberPart);
            int d;
            iss >> d;
            
            std::ofstream outputFile(output_file);

            if (!outputFile.is_open()) {
                std::cerr << "Error: Unable to open the file " << input_file << std::endl;
            }
            else{
                outputFile <<dary_calculate_height(data.size(), d) << std::endl; // Write the height

                outputFile << std::endl;
                outputFile.close();
            }


        }
        else{
            cout<<"Wrong prefix!"<<endl;
        }
               
    }
    else if(function_name == "dary_increase_key"){
        if(argv[4] == NULL || argv[5] == NULL || argv[6] == NULL){
            cerr<<"MISSING ARGUMENT!"<<endl;
            return 0;
        }        
        //Takes the arguments
        std::string string_1 = argv[4];
        std::string string_2 = argv[5];
        std::string string_3 = argv[6];
        // Create two strings to separate letter and number
        std::string prefix;
        std::string numberPart;            
        
        // Separate letter and number
        for (char c : string_1) {
            if (std::isdigit(c)) {
                numberPart += c;
            } else {
                prefix += c;
            }
        }

        // Guarantee that the code will work no matter what order input is entered.
    
        if(prefix == "i"){
            // Convert the number to int
            std::istringstream iss(numberPart);
            int i;
            iss >> i;
            
            //Reset the argument keeper
            prefix="";
            numberPart="";

            // Separate letter and number
            for (char c : string_2) {
                if (std::isdigit(c)) {
                    numberPart += c;
                } else {
                    prefix += c;
                }
            }
            if(prefix == "k"){
                // Convert the number to int
                std::istringstream iss(numberPart);
                int k;
                iss >> k;
                
                //Reset the argument keeper
                prefix="";
                numberPart="";

                // Separate letter and number
                for (char c : string_3) {
                    if (std::isdigit(c)) {
                        numberPart += c;
                    } else {
                        prefix += c;
                    }
                }
                if(prefix == "d"){
                    // Convert the number to int
                    std::istringstream iss(numberPart);
                    int d;
                    iss >> d;
                    
                    //First build a Max-Heap
                    build_max_heap(data, d); 
                    // Call the function
                    dary_increase_key(data, i, k, d);
                    // Write the output to out.csv file
                    print_heap_to_file(data, argv[3]);
                }
                else{
                    cout<<"Wrong prefix!"<<endl;
                }

            }
            else if(prefix == "d"){
                //Convert the number to int
                std::istringstream iss(numberPart);
                int d;
                iss >> d;
                
                //Reset the argument keeper
                prefix="";
                numberPart="";

                // Separate letter and number
                for (char c : string_3) {
                    if (std::isdigit(c)) {
                        numberPart += c;
                    } else {
                        prefix += c;
                    }
                }

                if(prefix == "k"){
                    std::istringstream iss(numberPart);
                    int k;
                    iss >> k;
                    
                    //First build a Max-Heap
                    build_max_heap(data, d); 
                    // Call the function
                    dary_increase_key(data, i, k, d);
                    // Write the output to out.csv file
                    print_heap_to_file(data, argv[3]);
                }
                else{
                    cout<<"Wrong prefix!"<<endl;
                }
            }
            else{
                cout<<"Wrong prefix!"<<endl;
            }
        }
        else if(prefix == "d"){
            // Convert the number to int
            std::istringstream iss(numberPart);
            int d;
            iss >> d;
            
            //Reset the argument keeper
            prefix="";
            numberPart="";

            // Separate letter and number
            for (char c : string_2) {
                if (std::isdigit(c)) {
                    numberPart += c;
                } else {
                    prefix += c;
                }
            }
            if(prefix == "k"){
                // Convert the number to int
                std::istringstream iss(numberPart);
                int k;
                iss >> k;
                
                //Reset the argument keeper
                prefix="";
                numberPart="";

                // Separate letter and number
                for (char c : string_3) {
                    if (std::isdigit(c)) {
                        numberPart += c;
                    } else {
                        prefix += c;
                    }
                }
                if(prefix == "i"){
                    // Conveert the number to int
                    std::istringstream iss(numberPart);
                    int i;
                    iss >> i;
                    
                    //First build a Max-Heap
                    build_max_heap(data, d);                     
                    // Call the function
                    dary_increase_key(data, i, k, d);
                    // Write the output to out.csv file
                    print_heap_to_file(data, argv[3]);
                }
                else{
                    cout<<"Wrong prefix!"<<endl;
                }

            }
            else if(prefix == "i"){
                // Convert the number to int
                std::istringstream iss(numberPart);
                int i;
                iss >> i;

                //Reset the argument keeper
                prefix="";
                numberPart="";

                // Separate letter and number
                for (char c : string_3) {
                    if (std::isdigit(c)) {
                        numberPart += c;
                    } else {
                        prefix += c;
                    }
                }

                if(prefix == "k"){
                    // Convert the number to int
                    std::istringstream iss(numberPart);
                    int k;
                    iss >> k;

                    //First build a Max-Heap
                    build_max_heap(data, d); 
                    // Call the function
                    dary_increase_key(data, i, k, d);
                    // Write the output to out.csv file
                    print_heap_to_file(data, argv[3]);
                }
                else{
                    cout<<"Wrong prefix!"<<endl;
                }
            }
            else{
                cout<<"Wrong prefix!"<<endl;
            }
        } 
        else if(prefix == "k"){
            // Convert the number to int
            std::istringstream iss(numberPart);
            int k;
            iss >> k;
            
            //Reset the argument keeper
            prefix="";
            numberPart="";

            // Separate letter and number
            for (char c : string_2) {
                if (std::isdigit(c)) {
                    numberPart += c;
                } else {
                    prefix += c;
                }
            }
            if(prefix == "i"){
                // Convert the number to int
                std::istringstream iss(numberPart);
                int i;
                iss >> i;
                
                //Reset the argument keeper
                prefix="";
                numberPart="";

                // Separate letter and number
                for (char c : string_3) {
                    if (std::isdigit(c)) {
                        numberPart += c;
                    } else {
                        prefix += c;
                    }
                }
                if(prefix == "d"){
                    // Convert the number to int
                    std::istringstream iss(numberPart);
                    int d;
                    iss >> d;
                    
                    //First build a Max-Heap
                    build_max_heap(data, d); 
                    // Call the function
                    dary_increase_key(data, i, k, d);
                    // Write the output to out.csv file
                    print_heap_to_file(data, argv[3]);
                }
                else{
                    cout<<"Wrong prefix!"<<endl;
                }

            }
            else if(prefix == "d"){
                // Convert the number to int
                std::istringstream iss(numberPart);
                int d;
                iss >> d;

                //Reset the argument keeper
                prefix="";
                numberPart="";

                // Separate letter and number
                for (char c : string_3) {
                    if (std::isdigit(c)) {
                        numberPart += c;
                    } else {
                        prefix += c;
                    }
                }

                if(prefix == "i"){
                    // Convert the number to int
                    std::istringstream iss(numberPart);
                    int i;
                    iss >> i;
                    
                    //First build a Max-Heap
                    build_max_heap(data, d); 
                    // Call the function
                    dary_increase_key(data, i, k, d);
                    // Write the output to out.csv file
                    print_heap_to_file(data, argv[3]);
                }
                else{
                    cout<<"Wrong prefix!"<<endl;
                }
            }
            else{
                cout<<"Wrong prefix!"<<endl;
            }
        }
        else{
            cout<<"Wrong prefix!"<<endl;
        }
    }
    else if(function_name == "dary_extract_max"){
        if(argv[4] == NULL){
            cerr<<"MISSING ARGUMENT!"<<endl;
            return 0;
        }
        std::string astring = argv[4];
        // Create two strings to separate letter and number
        std::string prefix;
        std::string numberPart;
        
        // Separate letter and number
        for (char c : astring) {
            if (std::isdigit(c)) {
                numberPart += c;
            } else {
                prefix += c;
            }
        }
        if(prefix == "d"){
            // Convert the number to int
            std::istringstream iss(numberPart);
            int d;
            iss >> d;

            build_max_heap(data, d); // Create a d-ary Max-Heap
            
            // Open the file
            std::ofstream outputFile(output_file);
            if (!outputFile.is_open()) {
                std::cerr << "Error: Unable to open the file " << output_file << std::endl;
            }
            else{
                // First, write the d-ary Max-heap before extracting
                for (const auto& element : data) {
                    outputFile << element.first << ";" << element.second << std::endl;
                }
                outputFile<<endl;
                
                // Run the function and write the output
                outputFile <<"Max element is: "<<dary_extract_max(data, d)<< std::endl;
                outputFile<<endl;
                
                // First, write the d-ary Max-heap after extracting
                for (const auto& element : data) {
                    outputFile << element.first << ";" << element.second << std::endl;
                }
                outputFile << std::endl;
                outputFile.close();
            }    
        }
        else{
            cout<<"Wrong prefix!"<<endl;
        }        
    }
    else if(function_name == "dary_insert_element"){
        if(argv[4] == NULL || argv[5] == NULL){
            cerr<<"MISSING ARGUMENT!"<<endl;
            return 0;
        }        
        

        std::string string_1 = argv[4];
        std::string string_2 = argv[5];

        // Create two strings to separate letter and number
        std::string prefix;
        std::string numberPart;
        
        // Separate letter and number
        for (char c : string_1) {
            if(c == '_')
                continue;
            if (std::isdigit(c)) {
                numberPart += c;
            } else {
                prefix += c;
            }
        }
        if(prefix[0] == 'd'){
            // Convert the number to int
            std::istringstream iss(numberPart);
            int d;
            iss >> d;

            //Reset the argument keeper
            prefix="";
            numberPart="";

            // Separate letter and number
            for (char c : string_2) {
                if(c == '_')
                    continue;
                if (std::isdigit(c)) {
                    numberPart += c;
                } else {
                    prefix += c;
                }
            }
            if(prefix[0] == 'k'){
                // Convert the number to int
                std::istringstream iss(numberPart);
                int k;
                iss >> k;
                
                string city_name = prefix.substr(1);

                build_max_heap(data, d); // First, create a d-ary Max-Heap

                // Run insert function and write the output to file
                std::ofstream outputFile(output_file);
                if (!outputFile.is_open()) {
                    std::cerr << "Error: Unable to open the file " << output_file << std::endl;
                }
                else{
                    // First, write the Max-Heap before inserting
                    for (const auto& element : data) {
                        outputFile << element.first << ";" << element.second << std::endl;
                    }
                    outputFile<<endl;
                    
                    dary_insert_element(data, city_name, k, d);
                    outputFile<<city_name<<" "<<k<<" is added."<<endl;
                    outputFile<<endl;
                    // Write the Max-Heap after inserting
                    for (const auto& element : data) {
                        outputFile << element.first << ";" << element.second << std::endl;
                    }
                    outputFile << std::endl;
                    outputFile.close();
                } 
            }
            else{
                cout<<"Wrong prefix!"<<endl;
            }
        }
        else if(prefix[0] == 'k'){
            // Convert the number to int
            std::istringstream iss(numberPart);
            int k;
            iss >> k;

            string city_name = prefix.substr(1);

            prefix="";
            numberPart="";
            // Separate letter and number
            for (char c : string_2) {
                if (std::isdigit(c)) {
                    numberPart += c;
                } else {
                    prefix += c;
                }
            }
            
            if(prefix == "d"){
                // Convert the number to int
                std::istringstream iss(numberPart);
                int d;
                iss >> d;
                
                build_max_heap(data, d); // First, create a d-ary Max-Heap
                
                // Run insert function and write the output to file
                std::ofstream outputFile(output_file);
                if (!outputFile.is_open()) {
                    std::cerr << "Error: Unable to open the file " << output_file << std::endl;
                }
                else{
                    // Write the d-ary Max-Heap before inserting
                    for (const auto& element : data) {
                        outputFile << element.first << ";" << element.second << std::endl;
                    }
                    outputFile<<endl;
                    
                    dary_insert_element(data, city_name, k, d); // Insert the element
                    outputFile<<city_name<<" "<<k<<" is added."<<endl;
                    outputFile<<endl;
                    // // Write the d-ary Max-Heap after inserting
                    for (const auto& element : data) {
                        outputFile << element.first << ";" << element.second << std::endl;
                    }
                    outputFile << std::endl;
                    outputFile.close();
                } 
            }
            else{
                cout<<"Wrong prefix!"<<endl;
            }
        }
        else{
            cout<<"Wrong prefix!"<<endl;
        }
    }
    else if(function_name == "dary_heapsort"){
        if(argv[4] == NULL){
            cerr<<"MISSING ARGUMENT!"<<endl;
            return 0;
        }
        std::string astring = argv[4];
        // Create two strings to separate letter and number
        std::string prefix;
        std::string numberPart;
        
        // Separate letter and number
        for (char c : astring) {
            if (std::isdigit(c)) {
                numberPart += c;
            } else {
                prefix += c;
            }
        }
        if(prefix == "d"){
            // Convert the number to int
            std::istringstream iss(numberPart);
            int d;
            iss >> d;

            clock_t begin = clock(); // Start timer
            // Call the function
            dary_heapsort(data, d);
            clock_t end = clock(); // End timer
            double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC; // Calculate elapsed time
            cout<<"Time is: "<<elapsed_secs<<" ns."<<endl;
            // Write the output to out.csv file
            print_heap_to_file(data, output_file);    
        }
        else{
            cout<<"Wrong prefix!"<<endl;
        } 
        
             
    }
    else{
        cerr<<"Wrong Function Name!"<<endl;
    }
}