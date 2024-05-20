/*
    Mehmet Ali Balıkçı
    150200059
*/

#include<iostream>
#include<cstdlib>
     
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

// Insertion Sort function
void insertion_sort(std::vector<std::pair<std::string, int>>& data, int low, int high) {

    for (int i = low+1; i <= high; i++) {
        int key2 = data[i].second;
        std::string key1 = data[i].first;
        int j = i - 1;
        while (j >= 0 && data[j].second > key2) {
            data[j + 1] = data[j];
            j--;
        }
        data[j + 1].first = key1;
        data[j + 1].second = key2;
    }
}

// Partition function 
int partition(std::vector<std::pair<std::string, int>>& data, int low, int high, bool is_verbose_output){
    // Create a log file if it is wanted    
    if (is_verbose_output == true){
        
        std::ofstream log_file("log.txt", std::ios_base::app);
        
        if (!log_file.is_open()){
            std::cerr << "Error: file open failed." << std::endl;
            return 1;
        }
        
        log_file <<"Pivot: "<< data[high].second << " Array: [";
        
        for (int i = low; i < high-1; i++) {
            log_file << data[i].second << ", ";
        }
        
        log_file << data[high-1].second << "]" << std::endl;
        log_file.close();
    }

    int pivot = data[high].second;
    int i = low - 1;

    for(int j = low; j <= high-1; j++){
        if(data[j].second <= pivot){
            i++;
            std::swap(data[i], data[j]);
        }
    }
    std::swap(data[i+1], data[high]);
    return i + 1;

}

// Randomized Partition Function to use a random element as pivot
int randomized_partition_with_random_element(std::vector<std::pair<std::string, int>>& data, int low, int high, bool is_verbose_output){
    srand(time(NULL)); // Seed for random number generator
    int i = low + rand() % (high - low);
    std::swap(data[i], data[high]); // swap the random element with the last element
    return partition(data, low, high, is_verbose_output);
}

// Randomized Partition Function to use the median of three random elements as pivot
int randomized_partition_with_median_of_three_random_elements(std::vector<std::pair<std::string, int>>& data, int low, int high, bool is_verbose_output){
    srand(time(NULL));  // Seed for random number generator

    // Select three random elements
    int i = low + rand() % (high - low);
    int j = low + rand() % (high - low);
    int k = low + rand() % (high - low);

    // Find the median of the three elements
    int min_value = std::min(std::min(data[i].second, data[j].second), data[k].second);
    int max_value = std::max(std::max(data[i].second, data[j].second), data[k].second);

    int median[3];
    median[0] = data[i].second;
    median[1] = data[j].second;
    median[2] = data[k].second;

    int median_value = median[0];
    for(int i=0; i<3; i++){
        if(median[i] > min_value && median[i] < max_value){
            median_value = median[i];
        }
    }

    int median_index;
    for(int i=0; i<3; i++){
        if(median[i] == median_value){
            median_index = i;
        }
    }

    int pivot_index;
    if(median_index == 0){
        pivot_index = i;
    }
    else if(median_index == 1){
        pivot_index = j;
    }
    else{
        pivot_index = k;
    }

    std::swap(data[pivot_index], data[high]); // swap the random element with the last element
    return partition(data, low, high, is_verbose_output);
}

// QuickSort function to use the last element as pivot
void quicksort_last_pivot(std::vector<std::pair<std::string, int>>& data, int low, int high, int threshold, bool is_verbose_output){
    
    int data_size = high - low + 1;

    if(data_size <= threshold && threshold != 1){
        insertion_sort(data, low, high);
    }
    
    else if(low< high){
        int pivot_index = partition(data, low, high, is_verbose_output);
        quicksort_last_pivot(data, low, pivot_index - 1, threshold, is_verbose_output);
        quicksort_last_pivot(data, pivot_index + 1, high, threshold, is_verbose_output);
    }
}

// QuickSort function using a random element as pivot
void quicksort_random_pivot(std::vector<std::pair<std::string, int>>& data, int low, int high, int threshold, bool is_verbose_output){
    
    int data_size = high - low + 1;

    if(data_size <= threshold && threshold != 1){
        insertion_sort(data, low, high);
    }
    
    else if(low< high){
        int pivot_index = randomized_partition_with_random_element(data, low, high, is_verbose_output);
        quicksort_random_pivot(data, low, pivot_index - 1, threshold, is_verbose_output);
        quicksort_random_pivot(data, pivot_index + 1, high, threshold, is_verbose_output);
    }
}

// QuickSort function using the median of three random elements as pivot
void quicksort_median_of_three_element_pivot(std::vector<std::pair<std::string, int>>& data, int low, int high, int threshold, bool is_verbose_output){
    
    int data_size = high - low + 1;

    if(data_size <= threshold && threshold != 1){
        insertion_sort(data, low, high);
    }
    
    else if(low< high){
        int pivot_index = randomized_partition_with_median_of_three_random_elements(data, low, high, is_verbose_output);
        quicksort_median_of_three_element_pivot(data, low, pivot_index - 1, threshold, is_verbose_output);
        quicksort_median_of_three_element_pivot(data, pivot_index + 1, high, threshold, is_verbose_output);
    }
}

// Function to read data from CSV file and store it in a vector
std::vector<std::pair<std::string, int>> read_csv(const std::string& file_name) {
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

// Function to write data to CSV file from a vector
void write_csv(const std::string& file_name, const std::vector<std::pair<std::string, int>>& data) {
    std::ofstream file(file_name);
    
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << file_name << std::endl;
        return;
    }

    for (const auto& entry : data) {
        file << entry.first << ";" << entry.second << "\n";
    }

    file.close();
}

// Driver function
int main(int argc, char **argv){
    
    //Input and output file names
    std::string input_file = argv[1];
    std::string output_file = argv[4];
    std::string pivot_type = argv[2];
    std::string verbose_output ="";
    bool is_verbose_output = false;
    int threshold = std::stoi(argv[3]);

    if (argc == 6){
        verbose_output = argv[5];
    }
    if(verbose_output == "v"){
        is_verbose_output = true;    
    }
    
    // Read data from CSV file
    std::vector<std::pair<std::string, int>> data = read_csv(input_file);
    
    // If data is read successfully
    if(data.size() > 0){ 
        
        clock_t begin = clock(); // Start timer

        // Implement Naive Quicksort 
        if (threshold == 1){
            quicksort_last_pivot(data, 0, data.size() - 1, threshold, is_verbose_output);}

        // Implement Quicksort with threshold
        else{
            if (pivot_type == "l"){
                quicksort_last_pivot(data, 0, data.size() - 1, threshold, is_verbose_output);}
            
            else if (pivot_type == "r"){
                quicksort_random_pivot(data, 0, data.size() - 1, threshold, is_verbose_output);}
            
            else if (pivot_type == "m"){
                quicksort_median_of_three_element_pivot(data, 0,  data.size() - 1, threshold, is_verbose_output);}
            else{
                std::cerr << "Error: pivot type not found." << std::endl; 
                return 1;
            }
        }
        
        clock_t end = clock(); // End timer
        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC; // Calculate elapsed time
        
        if(threshold != 1)
            std::cout << "Time taken by QuickSort with pivot strategy '" << pivot_type <<"'"<< " and threshold " << threshold << ": " << elapsed_secs << " ns." << std::endl;
        else
            std::cout << "Time taken by naive QuickSort algorithm " << ": " << elapsed_secs << " ns." << std::endl;
        
        // Write sorted data to a new CSV file
        write_csv(output_file, data);

        std::cout << "Sorted data is written to " << output_file << std::endl;
    }    
    return 0;
}





