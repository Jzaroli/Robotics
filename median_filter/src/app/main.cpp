#include <iostream>
#include <random>
#include <chrono>
#include "../code/median_filter.cpp"
#include "../code/quicksort.cpp"

using namespace std;

int main(){

    // Welcome statement
    cout << endl;
    cout << "**** Sensor Noise Reduction using a Two Heap Median Filter ****" << endl; 
    cout << "**** Demo Application ****" << endl;
    cout << endl;
    cout << "WELCOME!" << endl;
    cout << endl;

    bool is_menu_active = true; // value for menu while loop 

    while (is_menu_active) {
        cout << "This program demos using a two heap, rolling median filter for sensor noise reduction and several associated tests!" << endl;

        string chosen_option = "";
        cout << endl << "Enter menu selection: " << endl;
        cout << endl;
        cout << "    C to Continue to Median Filter Tests" << endl;
        cout << "    Q to Quit" << endl;
        cin >> chosen_option;

        if (chosen_option == "Q")
        {
            is_menu_active = false;
            cout << "Quitting the application..." << endl;
        } else if (chosen_option == "C") {
            cout << endl;

            bool is_option_active = true; // value for tests while loop 

            while (is_option_active) {
                cout << "The program will randomly generate 30 gamma distributed numbers with a shape of 2 and a scale of 2." << endl;
                cout << "Then, it will slide a median filter window across the numbers to return the median at each step and a total time for the algorithm." << endl;
                cout << endl;

                int window_option = 0;
                cout << endl << "What size sliding window do you want to use (pick an integer between 2 and 10)?" << endl;
                cin >> window_option;

                if (window_option >= 2 && window_option <= 10) {
                    // initializes median filter with window size option
                    median_filter filter(window_option);

                    // boiler plate for gamma distributed number generation
                    random_device rd;
                    mt19937 gen(rd());
                    double shape = 2.0;
                    double scale = 2.0;
                    std::gamma_distribution<double> gamma_dist(shape, scale);

                    // generates 30 doubles and stores them in a vector
                    vector<double> numbers;
                    for (int i = 0; i < 30; ++i) {
                        double val = gamma_dist(gen);
                        numbers.push_back(val);
                    }

                    // starts timer
                    auto start = chrono::high_resolution_clock::now(); 

                    // stores the median of the first window 
                    for (int i = 0; i < window_option; ++i) {
                        filter.add_value(numbers[i]);
                    }
                    
                    vector<double> results = {filter.find_median()};
                    cout << endl;

                    // Slide the window through the rest of the vector
                    for (int i = window_option; i < numbers.size(); ++i) {
                        // Add new element entering the window
                        filter.add_value(numbers[i]);
                        // Remove element leaving the window
                        filter.remove_value(numbers[i - window_option]);
                        // Calculate and store median of current window
                        results.push_back(filter.find_median());
                    }

                    // ends timer
                    auto end = chrono::high_resolution_clock::now();
                    // calculates duration of median filter
                    chrono::duration<double> duration = end - start;

                    cout << "Using the two heap median filter, your median values are: " << endl;
                    for (int i = 0; i < results.size(); ++i) {
                        cout << results[i] << endl;
                    }
                    cout << endl;
                    
                    // report the duration of the calculation
                    cout << "Two heap median filter time taken: " << duration.count() << " seconds" << endl;
                    
                    cout << endl;
                    cout << "End of two heap median filter results read out." << endl;
                    cout << endl;

                    bool is_sub_option_active = true; // value for sub menu while loop 

                    while (is_sub_option_active) {
                        cout << "Menu:" << endl;
                        cout << endl;
                        cout << "1) Review your randomly generated input values." << endl;
                        cout << "2) Run an average filter on the input values." << endl;
                        cout << "3) Run a naive, quicksort median fitler algorithm on the input values and review its runtime." << endl;

                        string sub_menu_option = "";
                        cout << endl << "Enter menu selection (Q to Main Menu): " << endl;
                        cin >> sub_menu_option;

                        if (sub_menu_option == "1") {
                            cout << endl;
                            cout << "Your randomly generated numbers are:" << endl;
                            // iterates and prints randomly generated numbers
                            for (int i = 0; i < numbers.size(); ++i) {
                                cout << numbers[i] << endl;
                            }
                            cout << endl;
                            cout << "End of randomly generate numbers read out." << endl;
                        } else if (sub_menu_option == "2") {
                            cout << endl;
                            cout << "Your averages are: " << endl;
                            // iterates through numbers based on window size to calculate sum
                            for (int i = 0; i < numbers.size() - window_option + 1; ++i) {
                                double sum = 0;
                                for (int j = 0; j < window_option; j++) {
                                    sum = sum + numbers[i + j];
                                }
                                double result = sum / window_option;
                                cout << result << endl;
                            }
                            cout << endl;
                            cout << "End of average results read out." << endl;
                            cout << endl;
                        } else if (sub_menu_option == "3") {
                            cout << endl;
                            // starts timer
                            auto start2 = chrono::high_resolution_clock::now(); 

                            cout << "Your quicksort medians are: " << endl;
                            vector<double> results2; 

                            // iterates through numbers based on window size, pushes numbers to vector, then sorts
                            for (int i = 0; i < numbers.size() - window_option + 1; ++i) {
                                // initializes vector
                                vector<double> vec; 
                                // pushes values within window to vector
                                for (int j = 0; j < window_option; j++) {
                                    vec.push_back(numbers[i + j]);
                                }

                                // sorts vector
                                quicksort(vec, 0, vec.size()-1);
           
                                // finds median on condition that window is even or odd
                                if (vec.size() % 2 == 0) {
                                    int middle_i_1 = vec.size() / 2 - 1;
                                    int middle_i_2 = vec.size() / 2;
                                    results2.push_back((vec[middle_i_1] + vec[middle_i_2] ) / 2);
                                } else {
                                    int middle_i = vec.size() / 2;
                                    results2.push_back(vec[middle_i]);
                                }
                            }

                            // ends timer
                            auto end2 = chrono::high_resolution_clock::now();
                            // calculates duration of median filter
                            chrono::duration<double> duration2 = end2 - start2;

                            cout << "Using the quick sort median filter, your median values are: " << endl;
                            for (int i = 0; i < results2.size(); ++i) {
                                cout << results2[i] << endl;
                            }
    
                            cout << endl;
                            cout << "Quicksort median filter time taken: " << duration2.count() << " seconds" << endl;
                            cout << endl;
                            cout << "End of quicksort median results read out." << endl;
                            cout << endl;
                        } else if (sub_menu_option == "Q") {
                            is_sub_option_active = false;
                            is_option_active = false;
                        }
                    }
                }
            }
        }
    }

    return 0;
}
