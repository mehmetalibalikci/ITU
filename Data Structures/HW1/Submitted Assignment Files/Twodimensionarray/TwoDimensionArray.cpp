/*
Student Name: Mehmet Ali Balıkçı
Student ID: 150200059

*/

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>


using namespace std::chrono;

using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::ios;


unsigned int kNumberOfDepartments=0;
unsigned int kDepartmentCounter=0;  // Using not to change whenever the function called

string** depArr;    // To keep department and number of universities variables 

// To print department and the number of universities 

void PrintDepartmentAndUniversities(){
    cout<<"Number of Departments: "<<kNumberOfDepartments<<endl;
    
    for(int i=0;i<kDepartmentCounter;i++){
        cout<<""<<depArr[i][0]<<": "<<depArr[i][1]<<endl;
    }
    
}

// To print the data in the file which we keep in two dimensional array arr row by row 

void PrintData(string** newArr, int countRow, int countColumn){
    cout<<" ";
    for(int i=0;i<countRow;i++){
        for(int k=0;k<countColumn;k++){
            cout<<newArr[i][k]<<" ";
        }
    }
}

// To calculate how many universitis are there in each department

void FindNumberOfUniversities(string department, int fSame, int numberOfUniversities, int countRow){      
    if(fSame == 0){
        depArr[kDepartmentCounter][0] = department;
        depArr[kDepartmentCounter][1] = std::to_string(numberOfUniversities);
        kDepartmentCounter++;
    }
    else{
        for(int i=0;i<kDepartmentCounter;i++){
            if(depArr[i][0] == department){
                depArr[i][1] = std::to_string(numberOfUniversities);
            }
        }
    }
}

// To find how many different departments are there in our file

void FindNumberOfDepartments(string** newArr, int j, int countRow){
    int counter=0;
    int m=1;
    int same=0;
    int numberOfUniversities;

    if(j < countRow){
            numberOfUniversities=1;
            counter=0;
            for(int k=2;k<j+2;k++){
                if(j == countRow-1){
                    j--;
                    m=0;
                    k=1;
                }
                if(newArr[k][0] == newArr[m][0]){
                    numberOfUniversities++;
                    same=1;
                    counter=1;
                }
            }
            if(counter){
                FindNumberOfUniversities(newArr[m][0],same,numberOfUniversities,countRow);
            }
            if(!counter){
                same=0;
                FindNumberOfUniversities(newArr[m][0],same,numberOfUniversities,countRow);
                kNumberOfDepartments++;
            }
        }
}

// To move all data to next row each time we add new data to the array

void MoveData(string** newArr, int j, int countRow){
    if(j < countRow-1){
            for(int k=j;k>=0;k--){
                for(int m=0;m<12;m++){
                    newArr[k+1][m]=newArr[k][m];
                }
            }
        }
}

// To calculate the number of row and column in the file

void CalculateSize(ifstream& input_file, int& countRow, int& countColumn){
    string row;
    int control=0;
    countRow = 0;
    countColumn = 0;
    
    while (getline(input_file, row, '\n')) {
        ++countRow;
        if(!control){
            for (int i = 0; i < row.length(); i++) {
                if (row[i] == ';') {
                    ++countColumn;
                }
            }      
        }
        control++;
    }
    countRow--;
    countColumn++;
    
}

// To read the datas in the file row by row

void ReadData(string** newArr, ifstream& input_file, int countRow){

    input_file.clear();
    input_file.seekg(0, ios::beg); // To read the file which read before from the very beginning

    string depArray;
    string row;
    string delimiter = ";";
    string afterDelimiter;
    string averageScore;
    int j{};
    
    getline(input_file, row, '\n'); // To exclude the first row in our file

    while(getline(input_file, row, '\n')){
        int i = 0 ;
        size_t pos = 0;
        string token;

        while ((pos = row.find(delimiter)) != string::npos) {
            token = row.substr(0, pos);
            afterDelimiter = row.substr(row.find(";") + 1);
            if(token != " "){
                if(i == 0) newArr[0][i]=token;
                else if(i==1) newArr[0][i] = token;
                else if(i==2) newArr[0][i] = token;
                else if(i==3) newArr[0][i] = token;
                else if(i==4) newArr[0][i] = token;
                else if(i==5) newArr[0][i] = token;
                else if(i==6) newArr[0][i] = (token);
                else if(i==7) newArr[0][i] = (token);
                else if(i==8) newArr[0][i] = (token);
                else if(i==9) newArr[0][i] = (token);
                else if(i==10) {newArr[0][i] = (token);
                    newArr[0][i+1] = afterDelimiter;                
                }
            }
            row.erase(0, pos + delimiter.length());
            i++; 
        }
        MoveData(newArr,j,countRow);
        FindNumberOfDepartments(newArr, j, countRow);
        j++;
    }
    input_file.close();
}

// To delete the array which we create to store datas in the file 

void DeleteArr(string** newArr, int countRow){
    auto start = high_resolution_clock::now();

    for(int i=0;i<countRow;i++){
        delete[] newArr[i];
    }
    delete[] newArr;
    newArr = nullptr;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    
    for(int i=0;i<countRow;i++){
        delete[] depArr[i];
    }
    delete[] depArr;
    depArr = nullptr;

    cout << "\nTime taken by de-allocating all array operation: "<< duration.count() << " milliseconds\n" << endl;
    if(newArr == nullptr && depArr == nullptr) cout<<"Array was succesfully deleted."<<endl;
}

// To sort the array alphabetically according to department name and university name 

void SortByDepAndUni(string** newArr, int countRow, int countColumn){
    for(int i=0; i<countRow-1; i++){
        for(int j=i+1; j<countRow; j++){
            if(newArr[j][0] <= newArr[i][0]){
                if(newArr[j][0] == newArr[i][0]){
                    if(newArr[j][2]<newArr[i][2]){
                        string temp_arr[countColumn];
                        for(int k=0; k<countColumn; k++){
                            temp_arr[k] = newArr[i][k];
                            newArr[i][k] = newArr[j][k];
                            newArr[j][k] = temp_arr[k];
                        }
                    }
                }
                else{
                    string temp_arr[countColumn];
                    for(int k=0; k<countColumn; k++){
                        temp_arr[k] = newArr[i][k];
                        newArr[i][k] = newArr[j][k];
                        newArr[j][k] = temp_arr[k];
                    }
                }
            }
        }
    }
}

int main(){

    ifstream inFile;
    
    inFile.open("hw1.csv");
    if(!inFile.is_open()){
        cout << "ERROR: The File Cannot be Opened" << endl;
        return EXIT_FAILURE;
    }

    int number_of_row;
    int number_of_column;
    
    CalculateSize(inFile, number_of_row,number_of_column);

    depArr = new string* [number_of_row];
    for(int i=0;i<number_of_row;i++){
        depArr[i] = new string [2];
    }

    // Definition of a pointer array which has memory dynamically allocated
    
    string** arr = new string* [number_of_row];
    for(int i=0;i<number_of_row;i++){
        arr[i] = new string [number_of_column];
    }

    auto start = high_resolution_clock::now(); // Time counter starts to count

    ReadData(arr,inFile,number_of_row);

    auto stop = high_resolution_clock::now();  // The operation of filling the array with data ends and time counter stopped.
    
    auto duration = duration_cast<seconds>(stop - start);
    cout << "\nTime taken by filling the array operation: "<< duration.count() << " seconds\n" << endl;



    //PrintDepartmentAndUniversities();
    SortByDepAndUni(arr, number_of_row, number_of_column);
    PrintData(arr,number_of_row,number_of_column);
    
    
    DeleteArr(arr,number_of_row);
    return 0;
}
