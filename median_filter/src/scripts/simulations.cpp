#include <iostream>
#include <random>
#include <chrono>
#include <fstream>
#include <vector>
#include <string>
#include "../code/median_filter.cpp"
#include "../code/quicksort.cpp"

using namespace std;

struct One_Sim_Result {
    int windowsize;
    int inputsize;
    double runtime;
};

int main() { 
    // ***** Two Heap Median Filter Simulation ***** //

    // initializes median filter with window size option
    int window_size = 200; // note: the window size is fixed!
    int input_size = 500; // start at 500
    vector<One_Sim_Result> sim_readings;

    for (int i = 0; i < 9; i++) { 
        median_filter filter(window_size);

        // boiler plate for gamma distributed number generation
        random_device rd;
        mt19937 gen(rd());
        double shape = 2.0;
        double scale = 2.0;
        std::gamma_distribution<double> gamma_dist(shape, scale);

        // generates doubles equal to input size and stores them in a vector
        vector<double> numbers;
        for (int i = 0; i < input_size; ++i) {
            double val = gamma_dist(gen);
            numbers.push_back(val);
        }

        // starts timer
        auto start = chrono::high_resolution_clock::now(); 

        // stores the median of the first window 
        for (int i = 0; i < window_size; ++i) {
            filter.add_value(numbers[i]);
        }
        
        vector<double> results = {filter.find_median()};

        // slide the window through the rest of the vector
        for (int i = window_size; i < numbers.size(); ++i) {
            // Add new element entering the window
            filter.add_value(numbers[i]);
            // Remove element leaving the window
            filter.remove_value(numbers[i - window_size]);
            // Calculate and store median of current window
            results.push_back(filter.find_median());
        }

        // ends timer
        auto end = chrono::high_resolution_clock::now();
        // calculates duration of median filter
        chrono::duration<double> duration = end - start;

        sim_readings.push_back(One_Sim_Result{window_size, input_size, duration.count()});

        input_size = input_size * 2; // doubles input size each time for a total of 9 times
    }

    // opens csv file and writes column names
    ofstream outputFile("twoheap_sim_results.csv", ios::out);
    outputFile << "WindowSize,InputSize,RunTime\n";

    // Write the results to the csv file
    for (const auto& sim_result : sim_readings) {
        outputFile << sim_result.windowsize << ","
                   << sim_result.inputsize << ","
                   << sim_result.runtime << "\n";
    }

    outputFile.close();

    // ***** QuickSort Median Filter Simulation ***** //

    // initializes median filter with window size option
    int window_size2 = 200; // note: the window size is fixed!
    int input_size2 = 500; // start at 500
    vector<One_Sim_Result> sim_readings2;

    for (int i = 0; i < 9; i++) { 
        // boiler plate for gamma distributed number generation
        random_device rd;
        mt19937 gen(rd());
        double shape = 2.0;
        double scale = 2.0;
        std::gamma_distribution<double> gamma_dist(shape, scale);

        // generates doubles equal to input size and stores them in a vector
        vector<double> numbers;
        for (int i = 0; i < input_size2; ++i) {
            double val = gamma_dist(gen);
            numbers.push_back(val);
        }

        // starts timer
        auto start = chrono::high_resolution_clock::now(); 

        // iterates through numbers based on window size, pushes numbers to vector, then sorts
        for (int i = 0; i < numbers.size() - window_size2 + 1; ++i) {
            // initializes vector
            vector<double> vec; 
            // pushes values within window to vector
            for (int j = 0; j < window_size2; j++) {
                vec.push_back(numbers[i + j]);
            }

            // sorts vector
            quicksort(vec, 0, vec.size()-1);

            vector<double> results;            
            // finds median on condition that window is even or odd
            
            if (vec.size() % 2 == 0) {
                int middle_i_1 = vec.size() / 2 - 1;
                int middle_i_2 = vec.size() / 2;
                results.push_back((vec[middle_i_1] + vec[middle_i_2] ) / 2);
            } else {
                int middle_i = vec.size() / 2;
                results.push_back(vec[middle_i]);
            }
            // note: nothing is being done with the result since this script is after the runtime
        }

        // ends timer
        auto end = chrono::high_resolution_clock::now();
        // calculates duration of median filter
        chrono::duration<double> duration = end - start;

        sim_readings2.push_back(One_Sim_Result{window_size2, input_size2, duration.count()});

        input_size2 = input_size2 * 2; // doubles input size each time for a total of 9 times
    }

    // opens csv file and writes column names
    ofstream outputFile2("quicksort_sim_results.csv", ios::out);
    outputFile2 << "WindowSize,InputSize,RunTime\n";

    // Write the results to the csv file
    for (const auto& sim_result : sim_readings2) {
        outputFile2 << sim_result.windowsize << ","
                   << sim_result.inputsize << ","
                   << sim_result.runtime << "\n";
    }

    outputFile2.close();

    return 0;
}
